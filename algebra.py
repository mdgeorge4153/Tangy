import fractions
from math import sqrt

FLOAT_SQRT2 = sqrt(2)
FLOAT_SQRT3 = sqrt(3)
FLOAT_SQRT6 = sqrt(6)

class Number(object):
	"""
	Represents a number of the form [a1 + a2*sqrt(2) + a3*sqrt(3) + a6*sqrt(6)]/d, where ai and d are integers
	"""

	__slots__ = ['a1', 'a2', 'a3', 'a6', 'd']

	def __init__(self, a1=0, a2=0, a3=0, a6=0, d=1):
		self.a1 = a1
		self.a2 = a2
		self.a3 = a3
		self.a6 = a6
		self.d  = d
		self.reduce()

	def __copy__(self):
		return Number(self.a1, self.a2, self.a3, self.a6, self.d)

	#
	# string conversions
	#

	def __repr__(self):
		return 'Number(%d,%d,%d,%d,%d)' % tuple(self)

	def __str__(self):
		return '[%d%+d*sqrt(2)%+d*sqrt(3)%+d*sqrt(6)]/%d' % tuple(self)

	def __unicode__(self):
		return u'[%d%+d\u221a2%+d\u221a3%+d\u221a6]/%d' % tuple(self)

	#
	# comparison operators
	#

	def __eq__(self, other):
		a1, a2, a3, a6, ad = self
		b1, b2, b3, b6, bd = other

		return ad*b1 == bd*a1 \
		   and ad*b2 == bd*a2 \
		   and ad*b3 == bd*a3 \
		   and ad*b6 == bd*a6

	def __neq__(self, other):
		return not self.__eq__(other)

	def __cmp__(self, other):
		# TODO
		return NotImplemented

	def __nonzero__(self):
		return self.a1 != 0 \
		    or self.a2 != 0 \
		    or self.a3 != 0 \
		    or self.a6 != 0

	#
	# sequence operators
	#

	def __iter__(self):
		return iter((self.a1, self.a2, self.a3, self.a6, self.d))

	#
	# arithmetic operators
	#

	def __add__(self, other):
		a1, a2, a3, a6, ad = self
		b1, b2, b3, b6, bd = other

		return Number(bd*a1 + ad*b1,
		              bd*a2 + ad*b2,
		              bd*a3 + ad*b3,
		              bd*a6 + ad*b6,
		              ad*bd)

	def __sub__(self, other):
		return self + (-other)

	def __mul__(self, other):
		a1, a2, a3, a6, ad = self
		b1, b2, b3, b6, bd = other

		c1 =   a1*b1 + 2*a2*b2 + 3*a3*b3 + 6*a6*b6
		c2 =   a1*b2 +   a2*b1 + 3*a3*b6 + 3*a6*b3
		c3 =   a1*b3 + 2*a2*b6 +   a3*b1 + 2*a6*b2
		c6 =   a1*b6 +   a2*b3 +   a3*b2 +   a6*b1
		cd =   ad*bd

		return Number(c1, c2, c3, c6, cd)

	def __div__(self, other):
		return self * other.inv()

	def __radd__(self, other):
		return self + other

	def __rsub__(self, other):
		return (-self) + other

	def __rmul__(self, other):
		return self * other

	def __rdiv__(self, other):
		return self.inv() * other

	def __neg__(self):
		return Number(-self.a1, -self.a2, -self.a3, -self.a6, self.d)

	def __pos__(self):
		return self

	def __abs__(self):
		# TODO
		pass

	def __complex__(self):
		return complex(self.__float__())

	def __float__(self):
		return self.a1 + self.a2*FLOAT_SQRT2 + self.a3*FLOAT_SQRT3 + self.a6*FLOAT_SQRT6

	#
	# helper functions
	#

	def conj2(self):
		"""conjugate the sqrt(2) portion"""
		return Number(self.a1, -self.a2, self.a3, -self.a6, 1)

	def conj3(self):
		"""conjugate the sqrt(3) portion"""
		return Number(self.a1, self.a2, -self.a3, -self.a6, 1)

	def inv(self):
		factor1 = self.conj2()
		current = self * factor1
		assert current.a2 == current.a6 == 0

		factor2 = current.conj3()
		current = current * factor2 # = self * factor1 * factor2
		assert current.a2 == current.a3 == current.a6 == 0

		return Number(current.d, 0, 0, 0, current.a1) * factor1 * factor2

	def reduce(self):
		gcd     = reduce(fractions.gcd, self)
		self.a1 = self.a1 / gcd
		self.a2 = self.a2 / gcd
		self.a3 = self.a3 / gcd
		self.a6 = self.a6 / gcd
		self.d  = self.d  / gcd

NMBR1 = Number(1,0,0,0,1)
SQRT2 = Number(0,1,0,0,1)
SQRT3 = Number(0,0,1,0,1)
SQRT6 = Number(0,0,0,1,1)

