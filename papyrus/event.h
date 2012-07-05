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
#ifndef PAPYRUSEVENT_H
#define PAPYRUSEVENT_H

namespace Papyrus {

namespace Event {

  typedef enum Type {
    BUTTON_PRESS,
    BUTTON_RELEASE,
    BUTTON_DOUBLE_PRESS,
    BUTTON_TRIPLE_PRESS,
    SCROLL,
    MOTION,
    KEY_PRESS,
    KEY_RELEASE,
  } Type;

  typedef enum ScrollDirection {
    SCROLL_UP,
    SCROLL_DOWN,
    SCROLL_LEFT,
    SCROLL_RIGHT,
  } ScrollDirection;

  typedef enum ButtonID {
    BUTTON_NONE       = 0x00,
    BUTTON_1          = 0x01 << 0,
    BUTTON_2          = 0x01 << 1,
    BUTTON_3          = 0x01 << 2,
    BUTTON_4          = 0x01 << 3,
    BUTTON_5          = 0x01 << 4,
    BUTTON_6          = 0x01 << 5,
    BUTTON_7          = 0x01 << 6,
    BUTTON_8          = 0x01 << 7,
    BUTTON_9          = 0x01 << 8,
    BUTTON_10         = 0x01 << 9,
    BUTTON_11         = 0x01 << 10,
    BUTTON_12         = 0x01 << 11,
    BUTTONS_1_3       = 0x01 << 12,
    BUTTONS_4_5       = 0x01 << 13,
    BUTTONS_6_7       = 0x01 << 14,
    BUTTONS_8_9       = 0x01 << 15,
    BUTTONS_11_12     = 0x01 << 16,
    BUTTONS_1_3_INV   = 0x01 << 17,
    BUTTONS_4_5_INV   = 0x01 << 18,
    BUTTONS_6_7_INV   = 0x01 << 19,
    BUTTONS_8_9_INV   = 0x01 << 20,
    BUTTONS_11_12_INV = 0x01 << 21,
  } ButtonID;

  // These are taken straight from GDK
  typedef enum ModifierType
  {
    SHIFT_MASK    = 1 << 0,
    LOCK_MASK     = 1 << 1,
    CONTROL_MASK  = 1 << 2,
    MOD1_MASK     = 1 << 3,
    MOD2_MASK     = 1 << 4,
    MOD3_MASK     = 1 << 5,
    MOD4_MASK     = 1 << 6,
    MOD5_MASK     = 1 << 7,
    BUTTON1_MASK  = 1 << 8,
    BUTTON2_MASK  = 1 << 9,
    BUTTON3_MASK  = 1 << 10,
    BUTTON4_MASK  = 1 << 11,
    BUTTON5_MASK  = 1 << 12,

    /* The next few modifiers are used by XKB, so we skip to the end.
     * Bits 15 - 25 are currently unused. Bit 29 is used internally.
     */

    SUPER_MASK    = 1 << 26,
    HYPER_MASK    = 1 << 27,
    META_MASK     = 1 << 28,

    RELEASE_MASK  = 1 << 30,

    MODIFIER_MASK = 0x5c001fff
  } ModifierType;

  struct Event {
  Event( uint32_t t=0, unsigned s=0 ): time(t), state(s) { }
    virtual ~Event() { }

    uint32_t time;
    unsigned state;

    virtual Type type() const = 0;
  };

  struct InterruptMarshaller {
      typedef bool result_type;

      template <typename T_iterator>
      result_type operator()(T_iterator first, T_iterator last) const
      {
        while ( first != last )
        {
          if ( *first ) return true;
          ++first;
        }
        return false;
      }
  };

  typedef sigc::signal1<bool, const Event&, InterruptMarshaller> signal;

  struct Button: public Event {
  Button( uint32_t t=0, unsigned s=0, unsigned b=0, double nx=0.0, double ny=0.0 ):
    Event( t, s ), button(b), x(nx), y(ny) { }
    virtual ~Button() { }

    unsigned button;
    double x;
    double y;
  };

  struct ButtonPress: public Button {
  ButtonPress( uint32_t t=0, unsigned s=0, unsigned b=0, double nx=0.0, double ny=0.0 ):
        Button( t, s, b, nx, ny) { }
    virtual ~ButtonPress() { }

    virtual Type type() const { return BUTTON_PRESS; }
  };

  struct ButtonRelease: public Button {
  ButtonRelease( uint32_t t=0, unsigned s=0, unsigned b=0, double nx=0.0, double ny=0.0 ):
        Button( t, s, b, nx, ny) { }
    virtual ~ButtonRelease() { }

    virtual Type type() const { return BUTTON_RELEASE; }
  };

  struct ButtonDoublePress: public Button {
  ButtonDoublePress( uint32_t t=0, unsigned s=0, unsigned b=0, double nx=0.0, double ny=0.0 ):
        Button( t, s, b, nx, ny) { }

    virtual ~ButtonDoublePress() { }

    virtual Type type() const { return BUTTON_DOUBLE_PRESS; }
  };

  struct ButtonTriplePress: public Button {
  ButtonTriplePress( uint32_t t=0, unsigned s=0, unsigned b=0, double nx=0.0, double ny=0.0 ):
        Button( t, s, b, nx, ny) { }

    virtual ~ButtonTriplePress() { }

    virtual Type type() const { return BUTTON_TRIPLE_PRESS; }
  };

  struct Scroll: public Event {
  Scroll( uint32_t t=0, unsigned s=0, ScrollDirection d=SCROLL_UP, double nx=0, double ny=0 ):
    Event(t, s), direction(d), x(nx), y(ny) { }

    virtual ~Scroll() { }

    ScrollDirection direction;
    double x;
    double y;

    virtual Type type() const { return SCROLL; }
  };

  struct Motion: public Event {
  Motion( uint32_t t=0, unsigned s=0, double nx=0.0, double ny=0.0 ):
    Event(t, s), x(nx), y(ny) { }

    virtual ~Motion() { }

    double x;
    double y;

    virtual Type type() const { return MOTION; }
  };

  struct Key: public Event {
  Key( uint32_t t=0, unsigned s=0, unsigned k=0, uint16_t hc=0, uint8_t kg=0 ):
        Event(t, s), key(k), hardware_code(hc), keyboard_group(kg) { }

    virtual ~Key() { }

    unsigned key;
    uint16_t hardware_code;
    uint8_t keyboard_group;
  };

  struct KeyPress: public Key {
  KeyPress( uint32_t t=0, unsigned s=0, unsigned k=0, uint16_t hc=0, uint8_t kg=0 ):
        Key( t, s, k, hc, kg) { }

    virtual ~KeyPress() { }

    virtual Type type() const { return KEY_PRESS; }
  };

  struct KeyRelease: public Key {
  KeyRelease( uint32_t t=0, unsigned s=0, unsigned k=0, uint16_t hc=0, uint8_t kg=0 ):
        Key( t, s, k, hc, kg) { }

    virtual ~KeyRelease() { }

    virtual Type type() const { return KEY_RELEASE; }
  };

}

}

#endif
