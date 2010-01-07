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
private:
	typedef typename GameTraits::number number;

	typedef typename CGAL::Extended_cartesian<number> kernel;
	typedef typename CGAL::Nef_polyhedron_2<kernel>   polygon;
	typedef typename kernel::Standard_point_2         cgal_point;

public:
	typedef typename GameTraits::point            point;
	typedef typename GameTraits::tan              tan;
	typedef typename GameTraits::tanset           tanset;
	typedef typename GameTraits::tan_handle       tan_handle;
	typedef typename GameTraits::const_tan_handle const_tan_handle;

	typedef typename polygon::Explorer explorer;

	ObstacleSet (const tan *, const tanset &);
	ObstacleSet ();  
	ObstacleSet & operator= (const ObstacleSet &);

	point closest (const point &) const;

	explorer mask () const;

private:

	polygon _impl;

};

#include "geometry.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
