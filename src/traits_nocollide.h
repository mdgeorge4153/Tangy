#ifndef __tangy_traits_nocollide_h__
#define __tangy_traits_nocollide_h__ 1

#include <complex>

#include "controller.h"
#include "algebra.h"
#include "tans_nocollide.h"

struct NoCollideGameTraits
{
	typedef ExtendedRational     number;

	typedef std::complex<number> point;
	typedef std::complex<number> vector;

	typedef NoCollideTanSet<NoCollideGameTraits> tanset;
	typedef NoCollideTan<NoCollideGameTraits>    tan;

	typedef tanset::tan_handle       tan_handle;
	typedef tanset::const_tan_handle const_tan_handle;

	typedef SimpleMouseController<NoCollideGameTraits> controller;
};


#endif
