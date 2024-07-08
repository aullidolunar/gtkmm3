#include <gtkmm/application.h>
#include "mywindow.h"

int main(int argc, char** argv)
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, PROGRAM_APPID);
	MyWindow win;
	return app->run(win);
}
