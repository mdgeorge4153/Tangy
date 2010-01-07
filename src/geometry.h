/*
 * geometry.h - polygons, polygon union, and minkoski sum
 */

#ifndef __tangy_geometry_h__
#define __tangy_geometry_h__ 1

#include <CGAL/Extended_cartesian.h>
#include <CGAL/Nef_polyhedron_2.h>

template<typename> class NefUnionPolicy;
template<typename> class ArrUnionPolicy;

template<typename GameTraits, template<typename number> class UnionPolicy = NefUnionPolicy>
class ObstacleSet
	: public UnionPolicy<typename GameTraits::number>
{
private:
	typedef typename GameTraits::number number;

	typedef typename CGAL::Extended_cartesian<number> kernel;
	typedef typename CGAL::Nef_polyhedron_2<kernel>   polygon;
	typedef typename kernel::Standard_point_2         cgal_point;

	typedef typename polygon::Explorer explorer;


public:
	typedef typename GameTraits::point            point;
	typedef typename GameTraits::tan              tan;
	typedef typename GameTraits::tanset           tanset;
	typedef typename GameTraits::const_tan_handle const_tan_handle;

	ObstacleSet (const tan *, const tanset &);
	ObstacleSet ();  
	ObstacleSet & operator= (const ObstacleSet &);

	point closest (const point &) const;

private:

	polygon _impl;

};

template<typename number>
class NefUnionPolicy
{

};

template<typename number>
class ArrUnionPolicy
{

};

#include "geometry.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
