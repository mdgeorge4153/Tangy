#include <gtkmm.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "tans.h"
#include "render_opengl.h"
#include "algebra.h"
#include "controller.h"
#include "traits.h"

class TanView
	: public Gtk::DrawingArea,
	  public Gtk::GL::Widget<TanView>
{
public:
	TanView(BaseObjectType *, const Glib::RefPtr<Gtk::Builder> &);

	virtual ~TanView();

protected:

	virtual void on_realize              ();
	virtual bool on_configure_event      (GdkEventConfigure *);
	virtual bool on_expose_event         (GdkEventExpose    *);

	virtual bool on_button_press_event   (GdkEventButton *);
	virtual bool on_button_release_event (GdkEventButton *);
	virtual bool on_motion_notify_event  (GdkEventMotion *);

	void gl_begin ();
	void gl_end   ();
	void gl_flush ();

	bool render   ();

	TanSet<GameTraits>                tans;
	SimpleMouseController<GameTraits> mouse;
};

TanView::
TanView(BaseObjectType * base, const Glib::RefPtr<Gtk::Builder> &)
	: Gtk::DrawingArea(base),
	  Gtk::GL::Widget<TanView>(* this),
	  tans(),
	  mouse(tans)
{
	Glib::RefPtr<Gdk::GL::Config> glconfig;
   
	glconfig = Gdk::GL::Config::create (Gdk::GL::MODE_RGBA  |
									    Gdk::GL::MODE_DOUBLE);
	set_gl_capability(glconfig);
}

TanView::
~TanView ()
{
}

void
TanView::
on_realize ()
{
	Gtk::DrawingArea::on_realize ();

	gl_begin();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gl_end();

	Glib::signal_idle().connect( sigc::mem_fun (*this, &TanView::render) );
}

bool
TanView::
on_configure_event (GdkEventConfigure * event)
{
	bool result = Gtk::DrawingArea::on_configure_event (event);

	gl_begin();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double waspect = float (get_width  ()) / float (get_height ());
	double haspect = float (get_height ()) / float (get_width  ());

	if (waspect < 1.0)
		waspect = 1.0;
	else
		haspect = 1.0;

	gluOrtho2D(0.0, 8.0 * waspect, 8.0 * haspect, 0.0);
	glViewport(0, 0, get_width(), get_height());

	gl_end();

	return result;
}

bool
TanView::
on_expose_event (GdkEventExpose * event)
{
	bool result = Gtk::DrawingArea::on_expose_event (event);

	render();

	return result;
}

bool
TanView::
on_button_press_event (GdkEventButton * event)
{
	Gtk::DrawingArea::on_button_press_event (event);

	if (event->button == 1)
		mouse.left_down();
	else if (event->button == 3)
		mouse.right_down();

	return false;
}

bool
TanView::
on_button_release_event (GdkEventButton * event)
{
	Gtk::DrawingArea::on_button_release_event (event);

	if (event->button == 1)
		mouse.left_up();
	else if (event->button == 3)
		mouse.right_up();

	return false;
}

bool
TanView::
on_motion_notify_event (GdkEventMotion * event)
{
	Gtk::DrawingArea::on_motion_notify_event (event);

	GameTraits::point pos (event->x, event->y);

	int size = get_width () < get_height () ? get_width () : get_height ();
	pos /= size;
	pos *= 8;

	mouse.move_to(pos);

	return false;
}

void
TanView::
gl_begin()
{
	get_gl_window()->gl_begin(get_gl_context());
}

void
TanView::
gl_end()
{
	get_gl_window()->gl_end();
}

void
TanView::
gl_flush()
{
	get_gl_window()->swap_buffers();
}

bool
TanView::
render()
{
	gl_begin();

	render_opengl(tans);

	gl_flush();
	gl_end();

	return true;
}

int main(int argc, char ** argv)
{
	Gtk::Main kit(argc, argv);

	Gtk::GL::init(argc, argv);

	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("../data/tangy.xml");

	Gtk::Window * window = 0;
	builder->get_widget("window", window);
	TanView * view = 0;
	builder->get_widget_derived("scene", view);

	kit.run(*window);
}

/*
** vim: ts=4 sw=4 cindent
*/