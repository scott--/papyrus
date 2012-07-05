//$Id: main.cc,v 1.1.1.1 2005/11/20 02:00:45 rvinyard Exp $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <gtkmm/main.h>
#include "pick_simple.h"

int main (int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  Simple win;
  Gtk::Main::run(win); //Shows the window and returns when it is closed.

  return 0;
}
