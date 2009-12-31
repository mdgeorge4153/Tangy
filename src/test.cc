#include <iostream>
#include <vector>
#include <utility>
#include "geometry.h"
#include "traits.h"


int main(int, char **)
{
	/*
	typedef GameTraits::point       point;
	typedef GameTraits::tanset      tanset;
	typedef ObstacleSet<GameTraits> obstacle_set;

	tanset       tans;
	obstacle_set obs (tans.find (point (1, 1)), tans);

	std::cout << obs.closest (point (2, 2)) << std::endl;
	*/

	typedef GameTraits::number number;

	typedef CGAL::Extended_cartesian<number> kernel;
	typedef CGAL::Nef_polyhedron_2<kernel>   mask;
	typedef mask::Point                      point;

	typedef std::vector<point>   poly;
	typedef poly::iterator       iter;
	typedef std::pair<iter,iter> pair;
	typedef std::vector<pair>    polyset;

	poly t1;
	t1.push_back(point(0,0));
	t1.push_back(point(1,0));
	t1.push_back(point(0,1));

	poly t2;
	t2.push_back(point(0,1));
	t2.push_back(point(1,0));
	t2.push_back(point(1,1));

	mask u (mask::EMPTY);
	u += mask(t1.begin(), t1.end(), mask::EXCLUDED);
	u += mask(t2.begin(), t2.end(), mask::EXCLUDED);

	print_map(u);

	return 0;
}

/*
** vim: ts=4 sw=4 cindent
*/
