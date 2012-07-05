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
#ifndef PAPYRUSANIMATOR_H
#define PAPYRUSANIMATOR_H

#include <glib.h>

#include <papyrus/controller.h>

namespace Papyrus
{

  /**
   * \todo TODO Change bounce frames to bounce limits
   * @author Rick L Vinyard Jr <rvinyard@cs.nmsu.edu>
   */
  class Animator : public Controller
  {
    protected:
      Animator(const Glib::ustring& id);

    public:
      typedef PapyrusPointer<Animator> pointer;

      virtual ~Animator();

      /** Advance the animation by n frames */
      virtual int advance ( int n=1 );

      /** Reverse the animation by n frames */
      virtual int reverse ( int n=1 );

      virtual void set_interval ( unsigned int interval_ms );

      virtual unsigned int interval( );

      virtual double frame_rate( );

      /**
       * Sets the number of frames per second.
       *
       * Since the interval is an integer is in milliseconds, and the set frames per
       * second may not evenly divide 1000, the rounded result of 1000/frames_per_second is
       * used.
       *
       * For example, setting the frame rate to 30 would result in an interval of
       * 33.333333. Therefore, an interval of 33 is used, yielding a frame rate of 33 frames
       * per second.
       *
       */
      virtual void set_frame_rate ( unsigned int frames_per_second );

      virtual void start();

      virtual void start ( unsigned int interval_ms );

      virtual void stop();

      virtual bool is_started();

      /** Returns the bounce frame setting */
      int bounce_frames();

      /**
       * Returns the current bounce direction
       * \return bounce direction
       *  - < 0 - reversing
       *  - = 0 - bounce disabled
       *  - > 0 - advancing
       */
      int bounce_direction();

      /**
       * Sets the number of 'bounce' frames. When set, the animation will
       * proceed in a given direction and then reverse back to the original
       * position creating a bounce effect. This allows a single callback
       * point, such as \c advance() to effectively work as a series of
       * calls to \c advance() followed by a series of calls to \c reverse() .
       *
       * The advantage of using the bounce effect is that you don't need
       * to keep track of when to call \c advance() and when to call
       * \c reverse() .
       *
       * \param frames Sets the number of bounce frames
       *   - > 0 - Advances the specified number of frames, then reverses, then advances...
       *   - = 0 - Disables bounce
       *   - < 0 - Reverses the specified number of frames, then advances, then reverses...
       */
      void set_bounce_frames ( int frames );

      sigc::signal<void, int> signal_advanced();

    protected:
      unsigned int m_interval;
      int m_bounce_frames;
      int m_bounce_direction;
      int m_bounce_position;
      guint m_timeout_source_id;

      sigc::signal<void, int> m_signal_advanced;

      bool timeout_handler();

      /**
       * Pure virtual method that children should implement to perform actual animation.
       * \param n The number of animation frames to perform
       *  - > 0 - Advance \c n frames
       *  - = 0 - Do nothing
       *  - < 0 - Reverse \c n frames
       * \return Zero if animation couldn't occur, non-zero otherwise. If possible, a child
       * should also return the number of frames animated. Also, if possible, a child should
       * return a positive number when frames are advanced and a negative when frames are
       * reversed.
       */
      virtual int animate ( int n ) = 0;

    private:
      static gboolean timeout_handler_proxy ( gpointer data );
  };

}

#endif
