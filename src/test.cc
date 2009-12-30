#include <iostream>
#include <vector>
#include <utility>
#include "geometry.h"
#include "traits.h"


int main(int, char **)
{
	typedef GameTraits::point       point;
	typedef GameTraits::tanset      tanset;
	typedef ObstacleSet<GameTraits> obstacle_set;

	tanset       tans;
	obstacle_set obs (tans.find (point (1, 1)), tans);

	std::cout << obs.closest (point (2, 2)) << std::endl;
	/*
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

	polyset ps;
	ps.push_back(pair(t1.begin(), t1.end()));
	ps.push_back(pair(t2.begin(), t2.end()));

	mask u (ps.begin(), ps.end(), mask::POLYGONS);

	number half    = number(1)/2;
	number quarter = half / 2;

	mask::Object_handle h = u.locate(point(-half,-half));
	std::cout << "-1/2,-1/2: " << u.contains(h) << std::endl;
	//std::cout << h << std::endl;

	h = u.locate(point(half,half));
	std::cout << " 1/2, 1/2: " << u.contains(h) << std::endl;
	//std::cout << h << std::endl;

	h = u.locate(point(quarter,quarter));
	std::cout << " 1/4, 1/4: " << u.contains(h) << std::endl;
	//std::cout << h << std::endl;
	*/

	return 0;
}

/*
** vim: ts=4 sw=4 cindent
*/
