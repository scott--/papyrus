/***************************************************************************
 *   Copyright (C) 2004 by Rick L. Vinyard, Jr.                            *
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
#include "animator.h"

#include <cmath>

namespace Papyrus
{

  Animator::Animator(const Glib::ustring& id):
      Controller(id),
      m_interval ( 0 ),
      m_bounce_frames ( 0 ),
      m_bounce_direction ( 0 ),
      m_bounce_position ( 0 ),
      m_timeout_source_id ( 0 )
  {
  }

  Animator::~Animator()
  {
    if ( m_timeout_source_id )
      this->stop();
  }

  int Animator::advance ( int n )
  {
    int advanced;

    if ( n == 0 )
      return 0;

    // No bounce
    if ( m_bounce_frames == 0 )
    {
      // just pass the value to animate
      return this->animate ( n );
    }

    // Bounce is advance then reverse, and we need to advance */
    if ( m_bounce_frames > 0 && m_bounce_position <= 0 )
      m_bounce_direction = 1;
    // Bounce is advance then reverse, and it's time to reverse */
    else if ( m_bounce_frames > 0 && m_bounce_position >= m_bounce_frames )
      m_bounce_direction = -1;
    // Bounce is reverse then advance, and we need to reverse */
    else if ( m_bounce_frames < 0 && m_bounce_position >= 0 )
      m_bounce_direction = -1;
    // Bounce is reverse then advance, and it's time to advance
    else if ( m_bounce_frames < 0 && m_bounce_position <= m_bounce_frames )
      m_bounce_direction = 1;
    /* If we reached here, we have one of two cases:
    *   Case 1:  1 <= position < bounce frames and bounce frames > 0
    *      In this case we'll leave direction alone and head down to 0 or up to bounce frames
    *   Case 2:  bounce frames < position <= -1 and bounce frames < 0
    *      Again, in this case we'll leave direction alone and head up to 0 or down to bounce frames
    * Either way, we leave direction alone.
    */
    advanced = this->animate ( n * m_bounce_direction );
    if ( advanced != 0 )
      m_bounce_position += n * m_bounce_direction;

    m_signal_advanced.emit ( advanced );

    return advanced;
  }

  int Animator::reverse ( int n )
  {
    return this->advance ( -n );
  }

  void Animator::set_interval ( unsigned int interval_ms )
  {
    m_interval = interval_ms;
    if ( m_timeout_source_id )
    {
      this->stop();
      this->start();
    }
  }

  unsigned int Animator::interval( )
  {
    return m_interval;
  }

  double Animator::frame_rate( )
  {
    return 1000.0 / m_interval;
  }

  void Animator::set_frame_rate ( unsigned int frames_per_second )
  {
    this->set_interval ( ( unsigned int ) round ( 1000.0/frames_per_second ) );
  }

  void Animator::start ( unsigned int interval_ms )
  {
    m_interval = interval_ms;
    this->start();
  }

  void Animator::start( )
  {
    if ( m_timeout_source_id )
      this->stop();

    m_timeout_source_id = g_timeout_add ( m_interval, &Animator::timeout_handler_proxy, this );
  }

  void Animator::stop( )
  {
    if ( m_timeout_source_id )
    {
      g_source_remove ( m_timeout_source_id );
      m_timeout_source_id = 0;
    }
  }

  bool Animator::is_started()
  {
    return m_timeout_source_id;
  }

  sigc::signal< void, int > Animator::signal_advanced( )
  {
    return m_signal_advanced;
  }

  bool Animator::timeout_handler( )
  {
    this->advance();
    return true;
  }

  int Animator::bounce_frames( )
  {
    return m_bounce_frames;
  }

  int Animator::bounce_direction( )
  {
    return m_bounce_direction;
  }

  void Animator::set_bounce_frames ( int frames )
  {
    m_bounce_frames = 0;
    this->advance ( - m_bounce_position );
    m_bounce_frames = frames;
    m_bounce_direction = 0;
    m_bounce_position = 0;
  }

  gboolean Animator::timeout_handler_proxy ( gpointer data )
  {
    Animator* animator = static_cast<Animator*> ( data );
    return animator->timeout_handler();
  }

}

