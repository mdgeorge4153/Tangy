#include <CGAL/Nef_polyhedron_2.h>
#include <CGAL/Extended_cartesian.h>
#include <CGAL/Algebraic_structure_traits.h>
#include <CGAL/Real_embeddable_traits.h>
#include <CGAL/Quotient.h>
#include <iostream>
#include "algebra.h"

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

int main(int, char **)
{
	Point p1(0,0), p2(0,1), p3(1,0);
	Point tri_points[3] = {p1, p2, p3};

	Polygon tri (tri_points, tri_points + 3);

	std::cout << tri;
}

