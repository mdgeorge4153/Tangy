#ifndef __tangy_traits_h__
#define __tangy_traits_h__

#include <complex>
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

	typedef tanset::tan_handle       tan_handle;
	typedef tanset::const_tan_handle const_tan_handle;

	typedef SimpleMouseController<SimpleGameTraits> controller;
};

typedef SimpleGameTraits GameTraits;

#endif

