#ifndef __tangy_traits_h__
#define __tangy_traits_h__

#include <complex>
#include <vector>
#include "controller.h"
#include "numbers.h"
#include "tans.h"

struct SimpleGameTraits
{
	typedef float number;

	typedef std::complex<number> point;
	typedef std::complex<number> vector;

	typedef TanSet<SimpleGameTraits>   tanset;
	typedef Tan<SimpleGameTraits>      tan;

	typedef std::vector<tan>              tan_container;
	typedef tan_container::iterator       tan_handle;
	typedef tan_container::const_iterator const_tan_handle;

	typedef SimpleMouseController<SimpleGameTraits> controller;
};

typedef SimpleGameTraits GameTraits;

#endif

