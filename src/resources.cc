#include "resources.h"
#include <glibmm.h>
#include <exception>


static std::string src_data_path;
static std::string ins_data_path;

class file_not_found
	: public std::exception
{
public:
	file_not_found (const std::string & filename) throw ()
		: _message("could not find " + filename)
	{}

	file_not_found (const file_not_found & other) throw ()
		: _message(other._message)
	{}

	virtual ~file_not_found() throw ()
	{}

	virtual const char * what() const throw()
	{
		return _message.c_str();
	}

	std::string _message;
};

void
resources_init (const std::string & argv0)
{
	std::string path = Glib::path_get_dirname(argv0);
	path = Glib::build_filename(path, "..");
	path = Glib::build_filename(path, "data");

	src_data_path = path;
	ins_data_path = DATADIR;
}

std::string
resource_filename (const std::string & filename)
{
	std::string candidates[] = {
		Glib::build_filename(src_data_path, filename),
		Glib::build_filename(ins_data_path, filename)
	};

	for (std::string * i = candidates; i != candidates + 2; i++)
	{
		if (Glib::file_test(* i, Glib::FILE_TEST_EXISTS))
			return * i;
	}

	throw file_not_found(filename);
}

std::string
resource_read (const std::string & filename)
{
	return Glib::file_get_contents(resource_filename(filename));
}

/*
** vim: ts=4 sw=4 cindent
*/
