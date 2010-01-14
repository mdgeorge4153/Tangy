
template<typename R>
struct Varying
{
	R eval (float) const = 0;

	virtual ~Varying() {}
};

/*
********************************************************************************
*/

template<typename R>
class Const
	: public Varying<R>
{
public:
	Const (const R & v)
		: _value(v)
	{}

	R eval (float) const
	{
		return _value;
	}

private:
	R _value;
};

/*
********************************************************************************
*/

template<typename R>
class Spline
	: public Varying<R>
{
public:
	Spline (const R & r0, const R & r1, const R & r2, const R & r3)
	{
		_basis[0] = - 1*r0 + 3*r1 - 3*r2 + 1*r3;
		_basis[1] =   3*r0 - 6*r1 + 3*r2 + 0*r3;
		_basis[2] = - 3*r0 + 0*r1 + 3*r2 + 0*r3;
		_basis[3] =   1*r0 + 4*r1 + 1*r2 + 0*r3;
	}

	template<typename InputIterator>
	Spline (InputIterator begin)
		: Spline(begin++, begin++, begin++, begin++)
	{
	}

	R eval (float t) const
	{
		R result = 0;

		for (int i = 0; i < 3; i++)
		{
			result *= t;
			result += _basis[i];
		}

		result /= 6;

		return result;
	}

private:

	R _basis[4];
};

/*
********************************************************************************
*/

template<typename R>
class Shift
	: public Varying<R>
{
public:
	Shift(std::auto_ptr<Varying<R> > impl, float t0, float alpha)
		: _impl(impl), _t0(t0), _alpha(alpha)
	{
	}

	R eval(float t) const
	{
		return _impl.eval(alpha * (t - _t0));
	}

private:
	std::auto_ptr<Varying<R> > _impl;
	float _t0, _alpha;
};

/*
********************************************************************************
*/

template<typename R>
class Transform
	: public Varying<R>
{
public:
	Transform(std::auto_ptr<Varying<R> > impl, const R& rot, const R& trans)
		: _impl(impl), _rot(rot), _trans(trans)
	{
	}

	R eval (float) const
	{
		return _rot * (_impl.eval(t) + _trans);
	}

private:
	std::auto_ptr<Varying<R> > _impl;
	R _rot, _trans;
};

/*
** vim: ts=4 sw=4 cindent
*/
