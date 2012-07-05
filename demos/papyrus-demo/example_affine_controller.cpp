/* This example demonstrates the affine controller.
 *
 * The affine controller maintains translation, rotation, scaling and skewing
 * values and applies the resulting affine transformation matrix to all
 * drawing objects under the control of the affine controller.
 *
 * DrawableContainerInterface is an ancestor of Selector. Therefore an owning
 * Papyrus::Group object may be set as well as a drawing Papyrus::Group object.
 *
 */

#include "gtkmm.h"

#include <papyrus-extras.h>
#include <papyrus-gtkmm/viewport.h>

typedef enum Scale {
  TRANSLATE_X,
  TRANSLATE_Y,
  SCALE_X,
  SCALE_Y,
  ROTATE,
  SKEW_X,
  SKEW_Y,
  CENTROID_X,
  CENTROID_Y,
  SCALES
} Scale;

const char* label_string[] = {
  "Translation - X",
  "Translation - Y",
  "Scaling - X",
  "Scaling - Y",
  "Rotation",
  "Skewing - X",
  "Skewing - Y",
  "Centroid - X",
  "Centroid - Y",
};

const double adjustments[][5] =
{
  {-100.0, 101.0, 1, 0.0}, // Translation X
  {-100.0, 101.0, 1, 0.0}, // Translation Y
  {0.0, 3.5, 0.5, 1.0}, // Scaling X
  {0.0, 3.5, 0.5, 1.0}, // Scaling Y
  {-M_PI, M_PI+M_PI/4, M_PI/4, 0.0}, // Rotation
  {-1.0, 1.1, 0.1, 0.0}, // Skewing X
  {-1.0, 1.1, 0.1, 0.0}, // Skewing Y
  {-100.0, 101.0, 1, 0.0}, // Centroid X
  {-100.0, 101.0, 1, 0.0}, // Centroid Y
};

class Example_AffineController : public Gtk::Window
{
  public:
    Example_AffineController();
    virtual ~Example_AffineController();

  protected:
  //Member widgets:
    Papyrus::Gtk::Viewport m_Viewport;
    Papyrus::AffineController::pointer m_AffineController;

    Gtk::HScale* m_scale[SCALES];

    void on_scale_changed( Scale s );

    void on_reset( Scale s );
};

//Called by DemoWindow;
Gtk::Window* do_AffineController()
{
  return new Example_AffineController();
}

Example_AffineController::Example_AffineController()
{
  set_title("Selector Example");
  set_border_width(10);

  Gtk::Table* table = Gtk::manage( new Gtk::Table() );

  // Create the selector
  m_AffineController = Papyrus::AffineController::create();
  m_AffineController->add( m_Viewport.canvas() );

  m_Viewport.canvas()->set_size( 300, 200 );

  // Create some shapes to add to the group
  Papyrus::Rectangle::pointer rectangle = Papyrus::example_rectangle( );
  Papyrus::Circle::pointer circle = Papyrus::example_circle( );
  Papyrus::Arc::pointer arc = Papyrus::example_arc( );
  Papyrus::Circle::pointer center_dot = Papyrus::Circle::create( 2.0, Papyrus::RGBA(0.0, 0.0, 0.0) );

  // Add the shapes to the group
  m_Viewport.canvas()->add( rectangle );
  m_Viewport.canvas()->add( circle );
  m_Viewport.canvas()->add( arc );
  m_Viewport.canvas()->add( center_dot );

  // Translate the shapes so they don't necessarily overlap
  rectangle->set_xywh(0, -60, 50, 30);
  circle->translate(40, 20);
  circle->set_radius(25);
  arc->translate(0, 20);

  table->attach( m_Viewport, 0, 3, 0, 1 );

  // Put Gtk labels and spin buttons for the various matrix effects in the table
  Gtk::Label* label;
  Gtk::Button* reset;
  for ( unsigned i=0; i < SCALES; i++ )
  {
    label = Gtk::manage( new Gtk::Label( label_string[i], Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER ) );
    table->attach( *label, 0, 1, i+1, i+2, Gtk::FILL );
    reset = Gtk::manage( new Gtk::Button("Reset") );
    reset->signal_clicked().connect( sigc::bind(sigc::mem_fun(*this, &Example_AffineController::on_reset), (Scale)i));
    table->attach( *reset, 2, 3, i+1, i+2, Gtk::SHRINK, Gtk::SHRINK );
    m_scale[i] = Gtk::manage( new Gtk::HScale(adjustments[i][0], adjustments[i][1], adjustments[i][2] ) );
    m_scale[i]->set_value( adjustments[i][3] );
    m_scale[i]->signal_value_changed().connect( sigc::bind( sigc::mem_fun(*this, &Example_AffineController::on_scale_changed), (Scale)i ));
    table->attach( *(m_scale[i]), 1, 2, i+1, i+2 );
  }

  this->add( *table );

  show_all();
}

Example_AffineController::~Example_AffineController()
{
}

void Example_AffineController::on_scale_changed( Scale s )
{
  double value = m_scale[s]->get_value();

  switch (s) {
    case TRANSLATE_X:
      m_AffineController->set_translate_x( value );
      break;
    case TRANSLATE_Y:
      m_AffineController->set_translate_y( value );
      break;
    case SCALE_X:
      m_AffineController->set_scale_x( value );
      break;
    case SCALE_Y:
      m_AffineController->set_scale_y( value );
      break;
    case ROTATE:
      m_AffineController->set_rotation( value );
      break;
    case SKEW_X:
      m_AffineController->set_skew_x( value );
      break;
    case SKEW_Y:
      m_AffineController->set_skew_y( value );
      break;
    case CENTROID_X:
      m_AffineController->set_centroid_x( value );
      break;
    case CENTROID_Y:
      m_AffineController->set_centroid_y( value );
      break;
  }
}

void Example_AffineController::on_reset( Scale s )
{
  m_scale[s]->set_value( adjustments[s][3] );
}

/***************************************************************************
 *   Copyright (C) 2009 by Rick L. Vinyard, Jr.                            *
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
