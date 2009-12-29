#ifndef __tangy_traits_h__
#define __tangy_traits_h__

#include <complex>
#include "algebra.h"
#include "tans.h"
#include "controller.h"

struct GameTraits
{
	typedef ExtendedRational     number;

	typedef std::complex<number> point;
	typedef std::complex<number> vector;

	typedef TanSet<GameTraits>   tanset;
	typedef Tan<GameTraits>      tan;

	typedef SimpleMouseController<GameTraits> controller;
};

#endif

