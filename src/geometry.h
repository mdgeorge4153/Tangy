/*
 * geometry.h - polygons, polygon union, and minkoski sum
 */

#ifndef __tangy_geometry_h__
#define __tangy_geometry_h__ 1

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

	typedef CGAL::Extended_cartesian<number> kernel;
	typedef CGAL::Nef_polyhedron_2<kernel>   polygon;
	typedef polygon::Point                   cgal_point;
};

#include "geometry.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
