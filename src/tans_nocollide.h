/*
 * tans_nocollide.h - implementation of tans interface that maintains the
 * invariant that no two tans intersect.
 */

#ifndef __gtans_tans_nocollide_h__
#define __gtans_tans_nocollide_h__ 1

#include "tans.h"
#include "algebra.h"

template<typename N>
class TanSetNoCollide
	: public TanSet<N>
{
protected:
	virtual void _best_fit(int, int);
};


typedef TanSetNoCollide<int>              TanSetNoCollide90;
typedef TanSetNoCollide<ExtendedRational> TanSetNoCollide15;

#include "tans_nocollide.hcc"

#endif
