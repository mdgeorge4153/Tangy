#include <iostream>
#include <vector>
#include <utility>
#include "geometry.h"
#include "traits_nocollide.h"
#include "algebra.h"


int main(int, char **)
{
	typedef GameTraits::number      number;
	typedef GameTraits::point       point;
	typedef GameTraits::vector      vector;
	typedef GameTraits::tanset      tanset;
	typedef GameTraits::tan_handle  tan;
	typedef ObstacleSet<GameTraits> obstacle_set;

	tanset       tans;

	tan t = tans.find (point (5, 2));
	t->set_rot(vector(6, 1));

	return 0;
}

/*
** vim: ts=4 sw=4 cindent
*/
