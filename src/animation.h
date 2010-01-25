#include <functional>

/*
********************************************************************************
*/

struct PingPong
	: public std::unary_function<float, float>
{
	float _width, _speed, _start;

	PingPong(float width, float max_speed)
	{
		_speed = (float) rand() / RAND_MAX * max_speed;
		_start = (float) rand() / RAND_MAX * width / _speed * -2;
		_width = width;
	}

	float operator() (float t)
	{
		float d = fmod(_speed * (t - _start), 2*_width);
		if (d <= _width)
			return d - 0.5 * _width;
		else
			return 1.5*_width - d;
	}
};

/*
********************************************************************************
*/

struct Oscillate
	: public std::unary_function<float, float>
{
	float _amplitude, _phase, _freq;

	Oscillate(float width, float max_speed)
	{
		_amplitude = width / 2;
		_phase     = (float) rand() / RAND_MAX * 2 * M_PI;
		_freq      = (float) rand() / RAND_MAX * max_speed * M_PI / width;
	}

	float operator() (float t)
	{
		return _amplitude * sin(_phase + t*_freq);
	}
};

/*
********************************************************************************
*/

template<typename P>
struct Const
	: public std::unary_function<float, P>
{
	P _value;

	Const(P value)
	{
		_value = value;
	}

	P operator() (float t)
	{
		return _value;
	}
};

/*
********************************************************************************
*/

template<typename XFun, typename YFun>
struct Point
	: public std::unary_function<float, std::complex<float> >
{
	XFun _x;
	YFun _y;

	Point (XFun x, YFun y)
		: _x(x), _y(y)
	{
	}

	std::complex<float> operator() (float t)
	{
		return std::complex<float> (_x(t), _y(t));
	}
};

/*
********************************************************************************
*/

struct Alpha
	: public std::unary_function<float, float>
{
	float _start, _end;

	Alpha (float start, float end)
	{
		_start = start;
		_end   = end;
	}

	float operator() (float t)
	{
		if (t < _start)
			return 0;
		if (t > _end)
			return 1;
		return (t - _start) / (_end - _start);
	}
};

/*
********************************************************************************
*/

template<typename PFun1, typename PFun2, typename Alpha>
struct Blend
	: public std::unary_function<float, typename PFun1::result_type>
{
	PFun1 _source;
	PFun2 _target;
	Alpha _alpha;

	Blend(PFun1 source, PFun2 target, Alpha alpha)
		: _source(source), _target(target), _alpha(alpha)
	{
	}

	typename PFun1::result_type operator() (float t)
	{
		float a = _alpha(t);

		return (1 - a)*_source(t) + a * _target(t);
	}
};

/*
********************************************************************************
*/

/*
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
*/

/*
** vim: ts=4 sw=4 cindent
*/
