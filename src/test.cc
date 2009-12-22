#include <iostream>
#include <complex>
#include "algebra.h"
#include "controller.h"
#include "tans.h"
#include "traits.h"

int main(int, char **)
{
	GameTraits::tanset tans;
	SimpleMouseController<GameTraits> controller (tans);
}

