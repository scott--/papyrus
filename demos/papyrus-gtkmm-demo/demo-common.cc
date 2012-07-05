#include "demo-common.h"
#include <glibmm/fileutils.h>
#include <glibmm/miscutils.h> //For Glib::build_filename().
#include <iostream>

/**
 * demo_find_file:
 * @base: base filename
 * @err:  location to store error, or %NULL.
 *
 * Looks for @base first in the current directory, then in the
 * location GTK+ where it will be installed on make install,
 * returns the first file found.
 *
 * Return value: the filename, if found or %NULL
 **/
Glib::ustring demo_find_file(const Glib::ustring& base)
{
  if(Glib::file_test("papyrus-icon.png", Glib::FILE_TEST_EXISTS) &&
      Glib::file_test (base, Glib::FILE_TEST_EXISTS))
  {
		std::cout << "base found at " << base << std::endl;
    return base;
  }
  else
  {
		std::cout << "base not found" << std::endl;

    Glib::ustring filename = Glib::build_filename(DEMOCODEDIR, base);
    if(!Glib::file_test(filename, Glib::FILE_TEST_EXISTS))
    {
      Glib::ustring msg = "Cannot find demo data file " + base;

      #ifdef GLIBMM_EXCEPTIONS_ENABLED
      throw Glib::FileError(Glib::FileError::NO_SUCH_ENTITY, msg);
      #else
      std::cerr << "File Error: " << msg << std::endl;
      #endif //GLIBMM_EXCEPTIONS_ENABLED
      return Glib::ustring();
    }

    return filename;
  }
}
