
#ifndef __tangy_tans_nocollide_h__
#define __tangy_tans_nocollide_h__ 1

#include "tans.h"
#include "geometry.h"

/*
********************************************************************************
*/

template<typename> class NoCollideTan;
template<typename> class NoCollideTanSet;

/*
********************************************************************************
*/

template<typename GameTraits>
class NoCollideTan
	: public Tan<GameTraits>
{
public:
	typedef typename GameTraits::point  point;
	typedef typename GameTraits::vector vector;
	typedef typename GameTraits::tanset tanset;

	void flip    ();
	void set_pos (const point  &);
	void set_rot (const vector &);

protected:
	NoCollideTan(const point &, const point &, const point &);
	NoCollideTan(const point &, const point &, const point &, const point &);

	void set_tanset(tanset *);

	tanset * _container;

	point _desired;

	friend class TanSet<GameTraits>;
	friend class NoCollideTanSet<GameTraits>;
};

/*
********************************************************************************
*/

template<typename GameTraits>
class NoCollideTanSet
	: public TanSet<GameTraits>
{
public:
	typedef typename GameTraits::tan                      tan;
	typedef typename TanSet<GameTraits>::tan_handle       tan_handle;
	typedef typename TanSet<GameTraits>::const_tan_handle const_tan_handle;
	typedef typename GameTraits::vector                   vector;
	typedef ObstacleSet<GameTraits>  obstacles;

	NoCollideTanSet ();

	void pan (const vector &);

protected:
	friend class NoCollideTan<GameTraits>;

	obstacles _obstruction;
	tan *     _dragged;
};

/*
********************************************************************************
*/

#include "tans_nocollide.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/

