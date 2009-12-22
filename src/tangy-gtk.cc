#include <gtkmm.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "tans.h"
#include "render_opengl.h"
#include "algebra.h"
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

	TanSet<GameTraits> tans;
};

TanView::
TanView(BaseObjectType * base, const Glib::RefPtr<Gtk::Builder> &)
	: Gtk::DrawingArea(base),
	  Gtk::GL::Widget<TanView>(* this)
{
	Glib::RefPtr<Gdk::GL::Config> glconfig;
   
	glconfig = Gdk::GL::Config::create (Gdk::GL::MODE_RGB   |
	                                    Gdk::GL::MODE_DEPTH |
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

	gl_end();
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

	gl_begin();

	/*
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f(0.3, 0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);

	glVertex2f(1.0, 1.0);
	glVertex2f(2.0, 1.0);
	glVertex2f(2.0, 2.0);
	glVertex2f(1.0, 2.0);

	glEnd();
	*/

	render_opengl(tans);

	gl_flush();
	gl_end();

	return result;
}

bool
TanView::
on_button_press_event (GdkEventButton * event)
{
	return Gtk::DrawingArea::on_button_press_event (event);
}

bool
TanView::
on_button_release_event (GdkEventButton * event)
{
	return Gtk::DrawingArea::on_button_release_event (event);
}

bool
TanView::
on_motion_notify_event (GdkEventMotion * event)
{
	return Gtk::DrawingArea::on_motion_notify_event (event);
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
