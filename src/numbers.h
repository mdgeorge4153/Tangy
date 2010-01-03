#ifndef __tangy_numbers_h__
#define __tangy_numbers_h__ 1

#include <complex>

inline
std::complex<float>
approximate (const std::complex<float> & n)
{
	return n;
}

inline
std::complex<float>
normalize (const std::complex<float> & n)
{
	return n / std::abs(n);
}

#endif

