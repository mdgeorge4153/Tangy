from algebra  import SIN15, COS15, SQRT2
from euclid   import Vector2, Point2

from abc import ABCMeta

class Tan(object):
	#
	# public API
	#

	def is_selected(self):
		"returns true if this tan is currently selected"
		return self._offset is not None

	def is_offset(self):
		assert self.is_selected()
		return self._offset != 0

	def coords(self):
		return iter(self._points)

	def desired_coords(self):
		if not self.is_offset():
			return iter(self._points)

		return iter(map(lambda x: x + self._offset, self._points))

	__iter__ = coords

	#
	# private API
	#

	def __init__(self, *points):
		self._points = list(points)
		self._offset = None

	def _tranlate(self, vec):
		self._points = map(lambda x: x + vec, self._points)

	def _rotate(self, rot):
		self._points = map(lambda x: x * vec, self._points)

class GameListener(metaclass=ABCMeta):
	@abstractmethod
	def selected(tan):
		pass

	@abstractmethod
	def unselected(tan):
		pass

	@abstractmethod
	def moved(tan):
		pass

	@abstractmethod
	def flipped(tan):
		pass

	@abstractmethod
	def rotated(tan):
		pass

class GameModel(object):
	def __init__(self):
		self._tans = (
			smalltri(),
			smalltri(),
			square(),
			parallelogram(),
			bigtri(),
			bigtri()
		)

		for i in range(4):
			self._tans[i]._translate(Vector2(1 + 2*i, 0))

		for i in range(4,7):
			self._tans[i]._translate(Vector2(1 + 3*i, 2))

		self._selected = None

	#
	# motion
	#

	def begin_motion(self, tan):
		assert self._selected is None
		self._selected = tan
		tan._offset    = Vector2(0,0)

	def move(self, vec):
		pass

	def flip(self):
		pass

	def rotate(self, theta):
		pass

	def end_motion(self):
		pass

	#
	# state accessors
	#

	def get_tans(self):
		return iter(self._tans)

	__iter__ = get_tans

	#
	# callback api
	#

	def add_listener(self, listener):
		pass

	def remove_listener(self, listener):
		pass



def smalltri():
	return Tan(Point2(0,0), Point2(0,1), Point2(1,0))

def medtri():
	return Tan(Point2(0,0), Point2(0,SQRT2), Point2(SQRT2, 0))

def bigtri():
	return Tan(Point2(0,0), Point2(0,2), Point2(2,0))

def square():
	return Tan(Point2(0,0), Point2(0,1), Point2(1,1), Point2(1,0))

def parallelogram():
	return Tan(Point2(0,0), Point2(1,1), Point2(2,1), Point2(1,0))

