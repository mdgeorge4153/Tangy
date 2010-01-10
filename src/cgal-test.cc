#include "algebra.h"
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arr_landmarks_point_location.h>
#include <CGAL/Arr_naive_point_location.h>

namespace CGAL {
	template<>
	class Algebraic_structure_traits<ExtendedRational>
		: public Algebraic_structure_traits_base<ExtendedRational, Field_tag>
	{
	};

	template<>
	class Real_embeddable_traits<ExtendedRational>
		: public INTERN_RET::Real_embeddable_traits_base<ExtendedRational, Tag_true>
	{
	};
}


int main (int, char**)
{
	typedef ExtendedRational number;
	typedef CGAL::Simple_cartesian<number>     kernel;
	typedef CGAL::Arr_segment_traits_2<kernel> traits;
	typedef CGAL::Arrangement_2<traits>        arrangement;

	typedef arrangement::Point_2               point;
	typedef arrangement::X_monotone_curve_2    segment;
	typedef arrangement::Halfedge_handle       edge;
	typedef arrangement::Vertex_handle         vertex;
	typedef arrangement::Face_handle           face;



	point pts[3] = {
		point(number(11, 0, 0, 1, 4), number( 3, -1, 0, 0, 4)),
		point(number(11, 0, 0,-1, 4), number(11,  1, 0, 0, 4)),
		point(number(11,-1, 0, 0, 4), number( 3,  0, 0,-1, 4))
	};

	point * begin = pts;
	point * end   = pts + 3;

	arrangement result;

	point  first_point = *begin++;
	vertex first_vert  = result.insert_in_face_interior(first_point, result.unbounded_face());

	point  prev_point = first_point;
	vertex prev_vert  = first_vert;

	while (begin != end)
	{
		point  next_point = *begin++;
		vertex next_vert  = result.insert_in_face_interior (next_point, result.unbounded_face());

		result.insert_at_vertices (segment(prev_point, next_point), prev_vert, next_vert);

		prev_point = next_point;
		prev_vert  = next_vert;
	}

	result.insert_at_vertices (segment(prev_point, first_point), prev_vert, first_vert);

	return 0;
}

/*
** vim: ts=4 sw=4 cindent
*/
