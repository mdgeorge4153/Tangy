class Polygon(objects):
	def __init__(self, points):
		self._points = points

	def __iter__(self):
		return iter(self._points)

	def rotate(self, rot):
		self._points = [rot * x for x in self._points]

	def translate(self, vec):
		self._points = [vec + x for x in self._points]

