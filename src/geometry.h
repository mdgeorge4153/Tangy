/*
 * geometry.h - polygons, polygon union, and minkoski sum
 */

#ifndef __gtans_geometry_h__
#define __gtans_geometry_h__ 1

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

typedef ExtendedRational FT;
typedef CGAL::Extended_cartesian<FT>   Kernel;
typedef CGAL::Nef_polyhedron_2<Kernel> Polygon;
typedef Polygon::Point                 Point;


#endif

/*
** vim: ts=4 sw=4 cindent
*/
