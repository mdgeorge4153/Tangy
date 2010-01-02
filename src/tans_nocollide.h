
#ifndef __tangy_tans_nocollide_h__
#define __tangy_tans_nocollide_h__ 1

#include "tans.h"
#include "geometry.h"

template<typename GameTraits>
class NoCollideTan
	: public Tan<GameTraits>
{
public:
	
protected:
	NoCollideTan(point, point, point);
	NoCollideTan(point, point, point, point);
};

template<typename GameTraits>
class NoCollideTanSet
	: public TanSet<GameTraits>
{
public:

};

#endif

/*
** vim: ts=4 sw=4 cindent
*/

