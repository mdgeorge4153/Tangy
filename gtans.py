import sys
import gtk
import gtk.gtkgl
from OpenGL.GL   import *
from OpenGL.GLU  import *
from OpenGL.GLUT import *


class Tan(object):
	def __init__(self):
		self._waves = [(200, 200), (250, 150), (325, 325), (300, 120)]
		self._rot   = 0
		self._sel   = False
		self.

class GTansApp(object):

	def on_window_destroy(self, widget, data=None):
		gtk.main_quit()

	def on_scene_realize(self, widget, data=None):
		print "realize"
		self._gl_begin()

		w = widget.allocation.width
		h = widget.allocation.height
		print w, h

		glMatrixMode(GL_PROJECTION)
		glLoadIdentity()
		glViewport(0, 0, w, h)
		gluPerspective(45, w/float(h), 1, 1000)

		glMatrixMode(GL_MODELVIEW)
		glLoadIdentity()
		gluLookAt(0.0, 0.0, 5.0,
			  0.0, 0.0, -1.0,
			  0.0, 1.0, 0.0)

		program = glCreateProgram()
		shader  = glCreateShader(GL_FRAGMENT_SHADER)

		file = open("animation/organic.frag")
		glShaderSource(shader, file.read())
		glCompileShader(shader)
		file.close()

		glAttachShader(program, shader)
		glLinkProgram(program)
		glUseProgram(program)

		self._gl_end()

	def on_scene_configure(self, widget, event, data=None):
		print "configure"

	def on_scene_expose(self, widget, data=None):
		print "expose"
		self._gl_begin()

		glClearColor(1.0,1.0,1.0,1.0)
		glClear(GL_COLOR_BUFFER_BIT)

		glColor(0.0, 0.0, 0.0)
		glutSolidTeapot(1)

		self._gl_end()

	def on_scene_motion_notify(self, widget, event, data=None):
		print widget.window.get_pointer()

	def on_scene_button_press(self, widget, data=None):
		print "press"

	def on_scene_button_release(self, widget, data=None):
		print "release"

	def on_load_activate(self, widget, data=None):
		pass

	def on_statistics_activate(self, widget, data=None):
		pass

	def on_quit_activate(self, widget, data=None):
		gtk.main_quit()

	def on_animate_toggled(self, widget, data=None):
		pass

	def on_fullscreen_activate(self, widget, data=None):
		pass

	def on_help_activate(self, widget, data=None):
		pass

	def on_about_activate(self, widget, data=None):
		pass

	def __init__(self):
		# create gui and connect signals
		builder = gtk.Builder()
		builder.add_from_file("gtans.xml") 
		builder.connect_signals(self)		

		# initialize gl stuff
		self.scene = builder.get_object("scene")
		display_mode = (gtk.gdkgl.MODE_RGB    |
				gtk.gdkgl.MODE_DEPTH  |
				gtk.gdkgl.MODE_DOUBLE )
		config = gtk.gdkgl.Config(mode=display_mode)
		gtk.gtkgl.widget_set_gl_capability(self.scene, config)

		glutInit()

		# save window
		self.window   = builder.get_object("window")

	def _gl_begin(self):
		drawable = gtk.gtkgl.widget_get_gl_drawable(self.scene)
		context  = gtk.gtkgl.widget_get_gl_context(self.scene)

		if not drawable or not context:
			raise Exception

		if not drawable.gl_begin(context):
			raise Exception

	def _gl_end(self):
		drawable = gtk.gtkgl.widget_get_gl_drawable(self.scene)

		drawable.swap_buffers()
		drawable.gl_end();


if __name__ == "__main__":
	app = GTansApp()
	app.window.show()
	gtk.main()

