from game      import GameListener
from OpenGL.GL import *

class GLRenderer(GameListener):
	def __init__(self, game):
		self._game = game

		glClearColor(1.0, 1.0, 1.0, 1.0)

	def update(self):
		pass

	def render(self):
		glClear(GL_COLOR_BUFFER_BIT)

		for tan in self._game:
			if tan.is_selected():
				glColor(0.3, 1.0, 0.0)
			else:
				glColor(0.0, 1.0, 1.0)

			glBegin(GL_POLYGON)
			for point in tan:
				glVertex2f(float(point.x), float(point.y))
			glEnd()
