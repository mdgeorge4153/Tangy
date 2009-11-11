class Node(object):
	def __init__(self, back, frwd):
		self.back = back
		self.frwd = frwd
		self.pos  = (back + frwd)/2

class Path(object):
	# logical node i is self._nodes[i - self._step]
	def __init__(self, start):
		self._step  = 0
		self._nodes = [start]

	def advance_to(self, step):
		self._extend_past(step)
		i = floor(step)
		self._nodes = self._nodes[i - self._step:]
		self._step  = i

	def pos(self, step):
		prev, next = self.get_nodes(step)
		t = step - floor(step)
		s = 1-t

		return bezier_interpolate(prev.pos, prev.frwd, next.back, next.pos)

	# return an interpolated bezier node representing the position and derivative at the given step
	def node(self, step):
		prev,next = self.get_nodes(step)
		t = step - floor(step)

		points = (prev.pos, prev.frwd, next.back, next.pos)
		pos = bezier_interpolate(points, t)
		der = bezier_derivative(points, t)
		return Node(pos - der, pos + der)

	# return the nodes before and after the given step
	def get_nodes(self, step):
		
		if step < self._step:
			raise Exception

		step = floor(step)
		self._extend_past(step+1)

		return self._nodes[step - self._step : step+1 - self._step]

	def _extend_past(self, step):
		current = self._nodes[-1]
		for i in range(self._step + len(self._nodes), ceil(step)):
			current = self.next(current)
			self._nodes.append(current)

	def _create_node(prev):
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
			theta = math.uniform(0, 2*math.PI)
			x,y = cos(theta), sin(theta)
			if self._xmin < x < self._xmax and self._ymin < y < self._ymax:
				return point + complex(x,y)

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
			theta = atan2(final.x - current.x, final.y - current.y)

			# delta is the angle between that connecting line and
			# one of the intersections between the circles.  By the
			# law of cosines:
			d2 = (final - current)^2
			r2 = (2*n - i)^2
			cos_delta = (1 + d2 - r2) / 2 / sqrt(d2)

			if cos_delta > 1:
				# only happens if we started too far away
				raise Exception
			if cos_delta < -1:
				# only happens if radius 1 circle is inside larger circle
				cos_delta = -1

			delta = acos(cos_delta)

			# sample a random angle and convert it to a unit vector
			gamma = random.uniform(theta - delta, theta + delta)
			unit  = (cos(gamma), sin(gamma))
			units.append(unit)
			current = current + unit

		# this penultimate unit vector actually isn't necessarily of
		# unit length.  However, note that in the algorithm above (r - d)
		# is decreasing with each step.  In the last step r is 1, so d
		# is likely to be close to 1 also, so we call it good enough
		units.append(final - current) # may be shorter than unit, but likely to be close enough
		units.append(steps.frwd - steps.back)

		# we shuffle the unit vectors to get rid of the tendency to
		# wander as long as possible and then race to the target
		random.shuffle(units)

		self._units = units

	def next(self, point):
		return point + self._units.pop()

class FollowPath(ApproachPath):
	"""A Path that approaches another Path, joining with it after self has
	   advanced n_self steps and other has advanced to other_step steps.
	   This path is valid for steps [0...nself)"""


class CirclePath(Path):
	"""A Path that walks a circlish shape"""
	def __init__(self, start, center):
		self._center = center

	def next(self, point):
		return (point - self._center) * 1j


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

