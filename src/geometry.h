/*
 * geometry.h - polygons, polygon union, and minkoski sum
 */

#ifndef __tangy_geometry_h__
#define __tangy_geometry_h__ 1

#include <CGAL/Cartesian.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arr_extended_dcel.h>
#include <CGAL/Arr_landmarks_point_location.h>
#include <CGAL/Arr_naive_point_location.h>

template<typename GameTraits>
class ObstacleSet
{
private:
	typedef typename GameTraits::number number;

	typedef typename CGAL::Cartesian<number>            kernel;
	typedef typename CGAL::Arr_segment_traits_2<kernel> traits;
	typedef typename CGAL::Arr_extended_dcel<traits, bool, bool, bool> dcel;
	typedef typename CGAL::Arrangement_2<traits, dcel>  arrangement;
	typedef typename traits::Point_2                    cgal_point;

	typedef typename CGAL::Arr_landmarks_point_location<arrangement> point_locator;

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

	arrangement    _impl;
	point_locator  _pl;

};

#include "geometry.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
