/***************************************************************************
 *   Copyright (C) 2007 by Rick L. Vinyard, Jr.                            *
 *   rvinyard@cs.nmsu.edu                                                  *
 *                                                                         *
 *   This file is part of the papyrus library.                             *
 *                                                                         *
 *   papyrus is free software; you can redistribute it and/or modify       *
 *   it under the terms of the GNU Lesser General Public License           *
 *   version 3.0 as published by the Free Software Foundation.             *
 *                                                                         *
 *   papyrus is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License version 3.0 for more details.       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with the papyrus library. If not, see                   *
 *   <http://www.gnu.org/licenses/>.                                       *
 ***************************************************************************/
#include "matrix.h"

#include <iostream>
#include <sstream>

#define REGEX_exponent "(?:[eE][-+]?\\d+)"
#define REGEX_fractional_constant "\\d*[.]\\d+|\\d+[.]"
#define REGEX_floating_point_constant "(?:" REGEX_fractional_constant REGEX_exponent "?|\\d+" REGEX_exponent ")"
#define REGEX_comma_wsp "(?:\\s+[,]?\\s*|[,]\\s*)"
#define REGEX_number "([-+]?\\d+|[-+]?" REGEX_floating_point_constant ")"
#define REGEX_skewY "(?:(skewY)\\s*\\(\\s*" REGEX_number "\\s*\\))"
#define REGEX_skewX "(?:(skewX)\\s*\\(\\s*" REGEX_number "\\s*\\))"
#define REGEX_rotate "(?:(rotate)\\s*\\(\\s*" REGEX_number "(?:" REGEX_comma_wsp REGEX_number REGEX_comma_wsp REGEX_number ")?" "\\s*\\))"
#define REGEX_scale "(?:(scale)\\s*\\(\\s*" REGEX_number "(?:" REGEX_comma_wsp REGEX_number ")?" "\\s*\\))"
#define REGEX_translate "(?:(translate)\\s*\\(\\s*" REGEX_number "(?:" REGEX_comma_wsp REGEX_number ")?" "\\s*\\))"
#define REGEX_matrix "(?:(matrix)\\s*\\(\\s*" REGEX_number REGEX_comma_wsp REGEX_number REGEX_comma_wsp REGEX_number REGEX_comma_wsp REGEX_number REGEX_comma_wsp REGEX_number REGEX_comma_wsp REGEX_number "\\s*\\))"
#define REGEX_transform REGEX_matrix "|" REGEX_translate "|" REGEX_scale "|" REGEX_rotate "|" REGEX_skewX "|" REGEX_skewY
#define REGEX_transforms REGEX_transform "(?:" REGEX_comma_wsp "+" REGEX_transform ")*"
#define REGEX_transform_list "\\s*" REGEX_transforms "\\s*"

namespace Papyrus
{

  Matrix Matrix::Identity = Matrix();

  Matrix::Matrix()
  {
    cairo_matrix_init_identity ( &m_matrix );
  }

  Matrix::Matrix ( double tx, double ty, double sx, double sy, double r )
  {
    cairo_matrix_init_translate ( &m_matrix, tx, ty );
    cairo_matrix_scale ( &m_matrix, sx, sy );
    cairo_matrix_rotate ( &m_matrix, r );
  }

  Matrix::Matrix ( double xx, double yx, double xy, double yy, double x0, double y0 )
  {
    cairo_matrix_init ( &m_matrix, xx, yx, xy, yy, x0, y0 );
  }

  Matrix::Matrix ( const Cairo::Matrix & matrix ) : m_matrix ( matrix )
  {}

  Matrix::Matrix ( const Matrix & other ) : m_matrix ( other.m_matrix )
  {}

  Matrix::Matrix(const char * svg_transform)
  {
    this->set( svg_transform );
  }

  Matrix::Matrix(const Glib::ustring & svg_transform)
  {
    this->set( svg_transform );
  }

  Matrix::pointer Matrix::create()
  {
    return pointer ( new Matrix() );
  }

  Matrix::pointer Matrix::create ( double tx, double ty, double sx, double sy, double r )
  {
    return pointer ( new Matrix ( tx, ty, sx, sy, r ) );
  }

  Matrix::pointer Matrix::create ( double xx, double yx, double xy, double yy, double x0, double y0 )
  {
    return pointer ( new Matrix ( xx, yx, xy, yy, x0, y0 ) );
  }

  Matrix::pointer Matrix::create ( const Cairo::Matrix& matrix )
  {
    return pointer ( new Matrix ( matrix ) );
  }

  Matrix::pointer Matrix::create ( const Matrix& other )
  {
    return pointer ( new Matrix ( other ) );
  }

  Matrix::pointer Matrix::create(const char * svg_string)
  {
    return pointer( new Matrix( svg_string ) );
  }

  Matrix::pointer Matrix::create(const Glib::ustring & svg_string)
  {
    return pointer( new Matrix( svg_string ) );
  }

  Matrix::~Matrix()
  {}

  void Matrix::translate ( double tx, double ty )
  {
    if ( tx == 0.0 && ty == 0.0 ) return;
    cairo_matrix_translate ( &m_matrix, tx, ty );
    m_signal_changed.emit();
  }

  void Matrix::scale ( double s )
  {
    if ( s == 1.0 ) return;
    cairo_matrix_scale ( &m_matrix, s, s );
    m_signal_changed.emit();
  }

  void Matrix::scale ( double sx, double sy )
  {
    if ( sx == 1.0 && sy == 1.0 ) return;
    cairo_matrix_scale ( &m_matrix, sx, sy );
    m_signal_changed.emit();
  }

  void Matrix::rotate ( double r, DegRad degrad )
  {
    if ( r == 0.0 ) return;
    if ( degrad == DEGREES ) r = r / 180.0 * M_PI;
    cairo_matrix_rotate ( &m_matrix, r );
    m_signal_changed.emit();
  }

  void Matrix::rotate(double r, double cx, double cy, DegRad degrad)
  {
    if ( r == 0.0 ) return;
    if ( degrad == DEGREES ) r = r / 180.0 * M_PI;
    cairo_matrix_translate ( &m_matrix, cx, cy );
    cairo_matrix_rotate ( &m_matrix, r );
    cairo_matrix_translate ( &m_matrix, -cx, -cy );
    m_signal_changed.emit();
  }

  void Matrix::skew ( double s, DegRad degrad )
  {
    if ( s == 0.0 ) return;
    double skew_val = tan(s);
    Cairo::Matrix skew_matrix;
    cairo_matrix_init(&skew_matrix, 1.0, skew_val, skew_val, 1.0, 0.0, 0.0);
    cairo_matrix_multiply ( &m_matrix, &m_matrix, &skew_matrix );
    m_signal_changed.emit();
  }

  void Matrix::skew ( double skewx, double skewy, DegRad degrad )
  {
    if ( skewx == 0.0 && skewy == 0.0 ) return;
    if ( degrad == DEGREES )
    {
      skewx = skewx / 180.0 * M_PI;
      skewy = skewy / 180.0 * M_PI;
    }
    double x_skew_val = tan(skewx);
    double y_skew_val = tan(skewy);
    Cairo::Matrix skew_matrix;
    cairo_matrix_init(&skew_matrix, 1.0, y_skew_val, x_skew_val, 1.0, 0.0, 0.0);
    cairo_matrix_multiply ( &m_matrix, &m_matrix, &skew_matrix );
    m_signal_changed.emit();
  }

  void Matrix::skew_x( double s, DegRad degrad )
  {
    if ( s == 0.0 ) return;
    if ( degrad == DEGREES ) s = s / 180.0 * M_PI;
    double x_skew_val = tan(s);
    Cairo::Matrix skew_matrix;
    cairo_matrix_init(&skew_matrix, 1.0, 0.0, x_skew_val, 1.0, 0.0, 0.0);
    cairo_matrix_multiply ( &m_matrix, &m_matrix, &skew_matrix );
    m_signal_changed.emit();
  }

  void Matrix::skew_y( double s, DegRad degrad )
  {
    if ( s == 0.0 ) return;
    if ( degrad == DEGREES ) s = s / 180.0 * M_PI;
    double y_skew_val = tan(s);
    Cairo::Matrix skew_matrix;
    cairo_matrix_init(&skew_matrix, 1.0, y_skew_val, 0.0, 1.0, 0.0, 0.0);
    cairo_matrix_multiply ( &m_matrix, &m_matrix, &skew_matrix );
    m_signal_changed.emit();
  }

  void Matrix::invert( )
  {
    cairo_matrix_invert ( &m_matrix );
    m_signal_changed.emit();
  }
  
  Matrix Matrix::inverse() const
  {
    Matrix inv = *this;
    inv.invert();
    return inv;
  }

  void Matrix::transform_distance ( double & dx, double & dy ) const
  {
    cairo_matrix_transform_distance ( &m_matrix, &dx, &dy );
  }

  void Matrix::transform_distance_inverse( double & dx, double & dy ) const
  {
    this->inverse().transform_distance(dx, dy);
  }

  void Matrix::transform_point ( double & x, double & y ) const
  {
    cairo_matrix_transform_point ( &m_matrix, &x, &y );
  }

  void Matrix::transform_point_inverse( double & x, double & y ) const
  {
    this->inverse().transform_point(x, y);
  }

  Matrix& Matrix::operator = ( const Cairo::Matrix & other )
  {
    m_matrix = other;
    m_signal_changed.emit();
    return *this;
  }

  Matrix& Matrix::operator = ( const Matrix & other )
  {
    m_matrix = other.m_matrix;
    m_signal_changed.emit();
    return *this;
  }

  Matrix& Matrix::operator = ( const Matrix::pointer other )
  {
    if ( not other ) return *this;
    m_matrix = other->m_matrix;
    m_signal_changed.emit();
    return *this;
  }

  Matrix & Matrix::operator =(const char * svg_transform)
  {
    this->set( svg_transform );
    return *this;
  }

  Matrix & Matrix::operator =(const Glib::ustring & svg_transform)
  {
    this->set( svg_transform );
    return *this;
  }

  Matrix Matrix::operator * ( const Matrix & other ) const
  {
    Matrix result;
    cairo_matrix_multiply ( & ( result.m_matrix ), &m_matrix, & ( other.m_matrix ) );
    return result;
  }

  Matrix Matrix::operator * ( const Matrix::pointer other ) const
  {
    if ( other ) return this->operator *( *other );
    return Matrix();
  }  
    
  Matrix Matrix::operator *(const char * svg_transform) const
  {
    return this->operator *( Matrix(svg_transform) );
  }

  Matrix Matrix::operator *(const Glib::ustring & svg_transform) const
  {
    return this->operator *( Matrix(svg_transform) );
  }

  Matrix& Matrix::operator *= ( const Matrix & other )
  {
    cairo_matrix_multiply ( &m_matrix, &m_matrix, & ( other.m_matrix ) );
    m_signal_changed.emit();
    return *this;
  }

  Matrix& Matrix::operator *= ( const Matrix::pointer other )
  {
    if ( other ) return *this *= *other;
    return *this;
  }

  Matrix & Matrix::operator *=(const char * svg_transform)
  {
    return *this *= Matrix(svg_transform);
  }

  Matrix & Matrix::operator *=(const Glib::ustring & svg_transform)
  {
    return *this *= Matrix(svg_transform);
  }

  bool Matrix::operator ==(const Matrix & other) const
  {
    return ( m_matrix.xx == other.m_matrix.xx and
             m_matrix.xy == other.m_matrix.xy and
             m_matrix.x0 == other.m_matrix.x0 and
             m_matrix.yx == other.m_matrix.yx and
             m_matrix.yy == other.m_matrix.yy and
             m_matrix.y0 == other.m_matrix.y0
           );
  }

  bool Matrix::operator !=(const Matrix & other) const
  {
    return not (*this == other);
  }

  bool Matrix::operator ==(const pointer other) const
  {
    if ( other ) return *this == *other;
    return false;
  }

  bool Matrix::operator !=(const pointer other) const
  {
    if ( other ) return *this != *other;
    return false;
  }

  Matrix::operator const Cairo::Matrix&() const
  {
    return m_matrix;
  }

  void Matrix::set_identity( )
  {
    cairo_matrix_init_identity ( &m_matrix );
    m_signal_changed.emit();
  }

  Glib::ustring Matrix::svg() const
  {
    std::ostringstream s;

    if ( m_matrix.xx == 1.0 && m_matrix.xy == 0.0 && m_matrix.yx == 0.0 && m_matrix.yy == 1.0 && m_matrix.x0 == 0.0 && m_matrix.y0 == 0.0 )
      return Glib::ustring();

    if ( m_matrix.xx == 1.0 && m_matrix.xy == 0.0 && m_matrix.yx == 0.0 && m_matrix.yy == 1.0 && ( m_matrix.x0 != 0.0 || m_matrix.y0 != 0.0 ) )
    {
      s << "translate( " << m_matrix.x0 << ", " << m_matrix.y0 << ")";
    }
    else if ( m_matrix.xy == 0.0 && m_matrix.x0 == 0.0 && m_matrix.yx == 0.0 && m_matrix.y0 == 0.0 && ( m_matrix.xx != 1.0 || m_matrix.yy != 1.0 ) )
    {
      s << "scale(";
      if ( m_matrix.xx == m_matrix.yy )
        s << m_matrix.xx;
      else
        s << m_matrix.xx << ", " << m_matrix.yy;
      s << ")";
    }
    else
    {
    
      s << "matrix(" << m_matrix.xx
          << " " << m_matrix.xy
          << " " << m_matrix.x0
          << " " << m_matrix.yx
          << " " << m_matrix.yy
          << " " << m_matrix.y0 << ")";
    }
    
    return s.str();
  }

  sigc::signal<void> Matrix::signal_changed()
  {
    return m_signal_changed;
  }

  bool has_digit( const Glib::ustring& s )
  {
    for ( size_t i = 0; i < s.size(); i++ )
      if ( isdigit(s[i]) ) return true;
    return false;
  }

  typedef enum Xform {
    XFORM_NONE = 0,
    XFORM_MATRIX,
    XFORM_TRANSLATE,
    XFORM_SCALE,
    XFORM_ROTATE,
    XFORM_SKEWX,
    XFORM_SKEWY
  } Xform;

  Xform which_transform( const Glib::ustring& s )
  {
    Glib::ustring lc = s.lowercase();
    
    if ( lc == "matrix" ) return XFORM_MATRIX;
    if ( lc == "translate" ) return XFORM_TRANSLATE;
    if ( lc == "scale" ) return XFORM_SCALE;
    if ( lc == "rotate" ) return XFORM_ROTATE;
    if ( lc == "skewx" ) return XFORM_SKEWX;
    if ( lc == "skewy" ) return XFORM_SKEWY;
    return XFORM_NONE;
  }

  bool Matrix::set(const Glib::ustring & s)
  {
    // Make initialization threadsafe
    static Glib::StaticMutex mutex;
    static Glib::RefPtr<Glib::Regex> transform_regex;

    double params[6];
    std::vector<Glib::ustring> split_results;

    mutex.lock();
    
    if ( not transform_regex )
    {
      Glib::ustring pattern = REGEX_transform_list;
      transform_regex = Glib::Regex::create(pattern, Glib::REGEX_CASELESS|Glib::REGEX_MULTILINE|Glib::REGEX_OPTIMIZE);
    }

    mutex.unlock();

    this->set_identity();

    split_results = transform_regex->split(s);
    if ( split_results.size() == 1 ) return false;
    
    for ( size_t i=0; i < split_results.size(); i++)
    {
//       std::cout << "Split results " << i << " [" << split_results[i].size() << "]{" << has_digit(split_results[i]) << "}(" << which_transform(split_results[i]) << "): " << split_results[i] << std::endl;
      switch ( which_transform(split_results[i]) )
      {
        case XFORM_NONE:
          break;
        case XFORM_MATRIX:
          if ( i+7 >= split_results.size() ) throw(-1);
          for ( int k=0; k < 6; k++ )
            params[k] = atof( split_results[i+1+k].c_str() );
          this->operator *=(Matrix(params[0], params[1], params[2], params[3], params[4], params[5]));
          i += 6;
          break;
        case XFORM_TRANSLATE:
          if ( i+2 >= split_results.size() ) throw(-1);
          params[0] = atof( split_results[i+1].c_str() );
          if ( has_digit(split_results[i+2] ) )
          {
            params[1] = atof( split_results[i+2].c_str() );
            this->translate( params[0], params[1] );
            i += 2;
          }
          else
          {
            this->translate( params[0], 0.0 );
            i += 1;
          }
          break;
        case XFORM_SCALE:
          if ( i+2 >= split_results.size() ) throw(-1);
          params[0] = atof( split_results[i+1].c_str() );
          if ( has_digit(split_results[i+2] ) )
          {
            params[1] = atof( split_results[i+2].c_str() );
            this->scale( params[0], params[1] );
            i += 2;
          }
          else
          {
            this->scale( params[0] );
            i += 1;
          }
          break;
        case XFORM_ROTATE:
          if ( i+2 >= split_results.size() ) throw(-1);
          params[0] = atof( split_results[i+1].c_str() );
          if ( has_digit(split_results[i+2] ) )
          {
            if ( i+3 >= split_results.size() ) throw(-1);
            params[1] = atof( split_results[i+2].c_str() );
            params[2] = atof( split_results[i+3].c_str() );
            this->rotate( params[0], params[1], params[2], DEGREES );
            i += 3;
          }
          else
          {
            this->rotate( params[0], DEGREES );
            i += 1;
          }
          break;
        case XFORM_SKEWX:
          if ( i+1 >= split_results.size() ) throw(-1);
          params[0] = atof( split_results[i+1].c_str() );
          this->skew_x( params[0], DEGREES );
          i += 1;
          break;
        case XFORM_SKEWY:
          if ( i+1 >= split_results.size() ) throw(-1);
          params[0] = atof( split_results[i+1].c_str() );
          this->skew_y( params[0], DEGREES );
          i += 1;
          break;
      }
    }
    return true;
  }

}

bool operator ==(const Papyrus::Matrix::pointer m1, const Papyrus::Matrix & m2)
{
  return m2 == m1;
}

bool operator !=(const Papyrus::Matrix::pointer m1, const Papyrus::Matrix & m2)
{
  return m2 != m1;
}
