/*
 * geometry.h - polygons, polygon union, and minkoski sum
 */

#ifndef __gtans_geometry_h__
#define __gtans_geometry_h__ 1

namespace CGAL {
	template<>
	class Algebraic_structure_traits<Number>
		: public Algebraic_structure_traits_base<Number, Field_tag>
	{
	};

	template<>
	class Real_embeddable_traits<Number>
		: public INTERN_RET::Real_embeddable_traits_base<Number, Tag_true>
	{
	};
}

typedef Number FT;
typedef CGAL::Extended_cartesian<FT>   Kernel;
typedef CGAL::Nef_polyhedron_2<Kernel> Polygon;
typedef Polygon::Point                 Point;


#endif

/*
** vim: ts=4 sw=4 cindent
*/
