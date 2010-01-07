#ifndef __tangy_utils_h__
#define __tangy_utils_h__ 1

#include <iterator>

/* circular_difference and circular_sum are similar to std::adjacent_difference
 * and std::partial_sum, but work for types (such as points, or pointers) where
 * the types of differences between values are different than the types of the
 * values themselves.  As with std::adjacent_difference and std::partial_sum,
 * circular_difference and circular_sum are two-sided inverses.
 */

/* t = circular_difference (c.begin(), c.end(), out)
 *
 * on input a, b, c, d
 * outputs (a - d, b - a, c - b, d - a)
 * returns d
 *
 * note that the sum of the output is zero
 */
template<typename In, typename Out, typename BinOp>
typename std::iterator_traits<In>::value_type circular_difference (In, In, Out, BinOp op);

template<typename In, typename Out>
typename std::iterator_traits<In>::value_type circular_difference (In, In, Out);

/* circular_sum (c.begin(), c.end(), out, t)
 *
 * on inputs a, b, c, d with initial value t
 * outputs (   t + a,
 *            (t + a) + b,
 *           ((t + a) + b) + c,
 *          (((t + a) + b) + c) + d))
 *
 */
template<typename In, typename Out, typename T, typename BinOp>
Out circular_sum (In, In, Out, T, BinOp op);

template<typename In, typename Out, typename T>
Out circular_sum (In, In, Out, T);

#include "utils.hcc"

#endif
