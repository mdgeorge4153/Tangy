#include "tans.h"

struct GameTraits
{
	typedef ExtendedRational     number;

	typedef std::complex<number> point;
	typedef std::complex<number> vector;

	typedef TanSet<GameTraits>   tanset;
	typedef Tan<GameTraits>      tan;
};

