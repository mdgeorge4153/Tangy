import cmath
import random
from math import *
from sys  import maxint

def random_point(boundary):
	"""
	Generate a random point within boundary
	"""
	pass

def _random_near(point, boundary):
	"""
	Generate a random point distance 1 from point and with boundary
	"""
	pass

def _random_towards(current, target, radius):
	"""
	Generate a random point distance 1 from current, and distance < radius from target
	"""

class PointSequence(object):
	"""
	A pointlist is a (potentially infinite) sequence of points.  Each point is
	guaranteed to be within distance 1 from the previous point.
	"""

	def __init__(self):
		self.__iter      = self.__points()
		self.__min_index = 0
		self.__points    = []

	def __getitem__(self, n):
		"""
		ps.__getitem__(int) -> complex

		return the nth element of the sequence.  Raises an IndexException unless
		ps.min_index <= n < max_index.
		"""

		if isinstance(n, slice):
			indices = n.indices(len(self))
			return [self[i] for i in range(*indices)]

		if not self.min_index() <= n < self.max_index():
			raise IndexException

		self.__extend_past(n)
		return self.__points[n - self.__min_index]

	def forget(self, n):
		"""
		Drop the prefix [0...n) from the sequence.
		"""
		if n > self.__min_index:
			self.__extend_past(n)
			self.__points    = self.__points[n - self.__min_index:]
			self.__min_index = n

	def min_index(self):
		"""
		ps.min_index() -> int
		"""
		return self.__min_index

	def __len__(self):
		return self.max_index()

	def __extend_past(self, n):
		self.__points.extend([self.__iter.next() for i in range(self.__min_index + len(self.__points), n)])

	def max_index(self):
		"""
		ps.max_index() -> int
		"""
		pass

	def __points(self, n):
		pass

class Wander(PointSequence):
	def __init__(self, start):
		pass

	def __points(self):
		pass

class Circle(PointSequence):
	pass

class Approach(PointSequence):
	pass

class Transform(PointSequence):
	pass

class Node(object):
	def __init__(self, back, frwd):
		self.back = back
		self.frwd = frwd
		self.pos  = (back + frwd)/2

def random_node(boundary):
	xmin, xmax, ymin, ymax = boundary

	back  = complex(random.uniform(xmin, xmax), random.uniform(ymin, ymax))
	while True:
		diff  = cmath.rect(1, random.uniform(0, 2*pi))
		frwd  = back + diff
		if xmin < frwd.real < xmax and ymin < frwd.imag < ymax:
			return Node(back, frwd)

class Path(object):
	# logical node i is self._nodes[i - self._step]
	def __init__(self, start):
		self._step  = 0
		self._nodes = [start]

	def advance_to(self, step):
		self._extend_past(step)
		i = int(step)
		self._nodes = self._nodes[i - self._step:]
		self._step  = i

	def pos(self, step):
		prev, next = self.get_nodes(step)

		return bezier_interpolate((prev.pos, prev.frwd, next.back, next.pos), step - floor(step))

	# return an interpolated bezier node representing the position and derivative at the given step
	def node(self, step):
		prev, next = self.get_nodes(step)
		t = step - floor(step)

		points = (prev.pos, prev.frwd, next.back, next.pos)
		pos = bezier_interpolate(points, t)
		der = bezier_derivative(points, t)
		return Node(pos - der, pos + der)

	# return the nodes before and after the given step
	def get_nodes(self, step):
		
		if step < self._step:
			raise Exception

		step = int(step)
		self._extend_past(step+1)

		return self._nodes[step - self._step : step+2 - self._step]

	def _extend_past(self, step):
		current = self._nodes[-1]
		for i in range(self._step + len(self._nodes), int(step)+2):
			current = self._create_node(current)
			self._nodes.append(current)

		assert (int(step) + 1) < self._step + len(self._nodes)

	def _create_node(self,prev):
		back = self.next(prev.frwd)
		frwd = self.next(back)
		return Node(back,frwd)

class WanderPath(Path):
	"""A Path that wanders aimlessly within bounds.  This path is defined for all steps > 0"""
	def __init__(self, start, boundary):
		Path.__init__(self, start)
		self._xmin, self._xmax, self._ymin, self._ymax = boundary

	def next(self, point):
		"generate a random point distance 1 from point that is within the boundary"
		while True:
			theta  = random.uniform(0, 2*pi)
			result = point + cmath.rect(1, theta)
			if self._xmin < result.real < self._xmax and self._ymin < result.imag < self._ymax:
				return result

class ApproachPath(Path):
	"""A Path that approaches a node, reaching it in n steps.  This path is
	   defined for steps [0...n)."""
	def __init__(self, start, target, n):
		Path.__init__(self, start)

		# 
		# we generate unit vectors ahead of time so we can shuffle them.
		#
		units   = []
		current = start.frwd
		final   = start.back
		for i in range(2*n - 2):
			#
			# sample a point within 2n - i of the final target and distance 1 from current
			#

			# consider two circles, one with radius 2n-i around
			# final and one with radius 1 around current

			# theta is the angle of the line connecting the centers
			d, theta = cmath.polar(final - current)

			# delta is the angle between that connecting line and
			# one of the intersections between the circles.  By the
			# law of cosines:
			d2 = d^2
			r2 = (2*n - i)^2
			cos_delta = (1 + d2 - r2) / 2 / d

			if cos_delta > 1:
				# only happens if we started too far away
				raise Exception
			if cos_delta < -1:
				# only happens if radius 1 circle is inside larger circle
				cos_delta = -1

			delta = acos(cos_delta)

			# sample a random angle and convert it to a unit vector
			gamma = random.uniform(theta - delta, theta + delta)
			unit  = cmath.rect(1, gamma)
			units.append(unit)
			current = current + unit

		# this penultimate unit vector actually isn't necessarily of
		# unit length.  However, note that in the algorithm above (r - d)
		# is decreasing with each step.  In the last step r is 1, so d
		# is likely to be close to 1 also, so we call it good enough
		units.append(final - current) # may be shorter than unit, but likely to be close enough
		units.append(target.frwd - target.back)

		# we shuffle the unit vectors to get rid of the tendency to
		# wander as long as possible and then race to the target
		random.shuffle(units)

		self._units = units

	def next(self, point):
		return point + self._units.pop()

class FollowPath(Path):
	"""A Path that approaches points defined by a function f from steps to
	   Nodes, joining with it after self has advanced n steps.  Assumes that |f(n) - f(n-1)| < 2. This path is valid
	   for steps [0...n)"""

	def __init__(self, start, f, n):
		pass

class CirclePath(Path):
	"""A Path that walks a circlish shape"""
	def __init__(self, start, center):
		Path.__init__(self, start)
		self._center = center

	def next(self, point):
		r, theta = cmath.polar(point - self._center)
		return point + cmath.rect(1, theta + pi/2)


def bezier_interpolate(points, t):
	s = 1 - t
	return s*s*s*points[0] \
	   + 3*s*s*t*points[1] \
	   + 3*s*t*t*points[2] \
	   +   t*t*t*points[3]

def bezier_derivative(points, t):
	s = 1 - t

	return s*s*(points[1] - points[0]) \
	   + 2*s*t*(points[2] - points[1]) \
	   +   t*t*(points[3] - points[2])

if __name__ == '__main__':
	#
	# testing
	#

	from gtk.gtkgl.apputils import *
	from OpenGL.GL          import *
	from OpenGL.GLU         import *
	from time               import clock

	def glVertex1c(z):
		glVertex2f(z.real, z.imag)

	class Example(GLScene,
	              GLSceneKey,
	              GLSceneIdle):

		def __init__(self):
			GLScene.__init__(self)

			self._start    = clock()
			self._boundary = (-5.0, 5.0, -5.0, 5.0)

			self._circle = CirclePath(Node(complex(0, 1), complex(1,1)), complex(0,0))
			self._wander = WanderPath(random_node(self._boundary), self._boundary)
			self._sprout = None

		# GLScene mathods

		def init(self):
			glMatrixMode(GL_PROJECTION)
			gluOrtho2D(-5.0, 5.0, -5.0, 5.0)

		def reshape(self, width, height):
			glViewport(0, 0, width, height)

		def display(self, width, height):
			time = clock() - self._start
			time = time
			self._circle.advance_to(time)
			self._wander.advance_to(time)

			glClearColor(1.0, 1.0, 1.0, 1.0)
			glClear(GL_COLOR_BUFFER_BIT)
			glPointSize(2.0)

			glBegin(GL_LINES)

			glColor(1.0, 0.0, 0.0, 1.0)
			node = self._circle.node(time)
			glVertex1c(node.back)
			glVertex1c(node.pos)

			glColor(0.0, 0.0, 1.0, 1.0)
			node = self._wander.node(time)
			glVertex1c(node.back)
			glVertex1c(node.pos)

			glVertex2f(0.0, 0.0)
			glVertex2f(3,3)
			glEnd()


		# GLSceneKey methods
		
		def key_press(self, width, height, event):
			pass

		def key_release(self, width, height, event):
			pass

		# GLSceneIdle methods

		def idle(self, width, height):
			self.invalidate()
			self.update()

	scene = Example()
	app   = GLApplication(scene)
	app.set_title("Paths demo")
	app.run()

