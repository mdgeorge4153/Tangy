#include "resources.h"
#include <glibmm.h>
#include <iostream>

static std::string src_data_path;
static std::string ins_data_path;

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
	std::cout << "searching for " << filename << std::endl;

	std::string candidates[] = {
		Glib::build_filename(src_data_path, filename),
		Glib::build_filename(ins_data_path, filename)
	};

	for (std::string * i = candidates; i != candidates + 2; i++)
	{
		std::cout << "  checking " << * i << " ...";

		if (Glib::file_test(* i, Glib::FILE_TEST_EXISTS))
		{
			std::cout << "found" << std::endl;
			return * i;
		}
		else
			std::cout << "not found" << std::endl;
	}

	std::cout << "failed" << std::endl;
	throw std::exception();
}

/*
** vim: ts=4 sw=4 cindent
*/
