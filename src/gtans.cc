#include <iostream>
#include <gtkmm.h>

int main(int argc, char ** argv)
{
	Gtk::Main kit(argc, argv);

	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("../data/gtans.xml");

	Gtk::Window * window = 0;
	builder->get_widget("window", window);

	kit.run(*window);
}

/*
** vim: ts=4 sw=4 cindent
*/
