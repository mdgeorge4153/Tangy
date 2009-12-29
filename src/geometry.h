/*
 * geometry.h - polygons, polygon union, and minkoski sum
 */

#ifndef __tangy_geometry_h__
#define __tangy_geometry_h__ 1

#include <CGAL/Extended_cartesian.h>
#include <CGAL/Nef_polyhedron_2.h>


template<typename GameTraits>
class ObstacleSet
{
public:
	typedef typename GameTraits::point  point;
	typedef typename GameTraits::tan    tan;
	typedef typename GameTraits::tanset tanset;

	ObstacleSet (const tan *, const tanset &);

	point closest (const point &) const;

private:
	typedef typename GameTraits::number number;

	typedef typename CGAL::Extended_cartesian<number> kernel;
	typedef typename CGAL::Nef_polyhedron_2<kernel>   polygon;
	typedef typename polygon::Point                   cgal_point;

	void add_sum(const tan &, const tan &);

	polygon _impl;
};

#include "geometry.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
