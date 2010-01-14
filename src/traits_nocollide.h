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

	typedef std::vector<tan>              tan_container;
	typedef tan_container::iterator       tan_handle;
	typedef tan_container::const_iterator const_tan_handle;

	typedef SimpleMouseController<NoCollideGameTraits> controller;
	typedef BasicRenderer<NoCollideGameTraits> renderer;
};

typedef NoCollideGameTraits GameTraits;

#endif
