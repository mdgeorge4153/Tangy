#include <iostream>
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

	return 0;
}

