#include "algebra.h"
#include "geometry.h"

int main (int, char**)
{
	typedef ExtendedRational number;
	typedef CGAL::Simple_cartesian<number>     kernel;
	typedef CGAL::Arr_segment_traits_2<kernel> traits;
	typedef CGAL::Arr_extended_dcel<traits, bool, bool, bool> dcel;
	typedef CGAL::Arrangement_2<traits, dcel>  arrangement;
	typedef traits::Point_2                    cgal_point;


	cgal_point pts[7] = {
		cgal_point(number(11, 0, 0, 1, 4), number( 3, -1, 0, 0, 4)),
		cgal_point(number(15, 0, 0, 1, 4), number( 7, -1, 0, 0, 4)),
		cgal_point(number(15, 1, 0, 0, 4), number( 7,  0, 0, 1, 4)),
		cgal_point(number(11, 1, 0, 0, 4), number(11,  0, 0, 1, 4)),
		cgal_point(number(11, 0, 0,-1, 4), number(11,  1, 0, 0, 4)),
		cgal_point(number(11, 0, 0,-1, 4), number( 3,  1, 0, 0, 4)),
		cgal_point(number(11,-1, 0, 0, 4), number( 3,  0, 0,-1, 4))
	};

	arrangement result;
	make_poly(pts, pts+7, result);

	return 0;
}

/*
** vim: ts=4 sw=4 cindent
*/
