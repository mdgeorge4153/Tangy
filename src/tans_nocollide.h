
#ifndef __tangy_tans_nocollide_h__
#define __tangy_tans_nocollide_h__ 1

#include "tans.h"
#include "geometry.h"

template<typename> class NoCollideTan;
template<typename> class NoCollideTanSet;

template<typename GameTraits>
class NoCollideTan
	: public Tan<GameTraits>
{
public:
	typedef typename GameTraits::point point;

protected:
	NoCollideTan(const point &, const point &, const point &);
	NoCollideTan(const point &, const point &, const point &, const point &);

	friend class TanSet<GameTraits>;
	friend class NoCollideTanSet<GameTraits>;
};

template<typename GameTraits>
class NoCollideTanSet
	: public TanSet<GameTraits>
{
public:

};

#include "tans_nocollide.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/

