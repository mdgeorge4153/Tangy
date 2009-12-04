/*
 * tans_basic.h - basic implementation of tans interface.  Provides free
 * rotation implementation using floats.
 */


#ifndef __gtans_tans_basic_h__
#define __gtans_tans_basic_h__ 1

#include "tans.h"

class FreeRotTanSet
	: public TanSet<float>
{
protected:
	virtual void _best_fit (int, int);
};


#endif

/*
** vim: 
