/*
 * tans.h - interface for manipulating sets of tans.
 */

#ifndef __gtans_tans_h__
#define __gtans_tans_h__ 1

#include <vector>
#include <valarray>
#include <complex>

template<typename N> class Tan;
template<typename N> class TanSet;
template<typename N> class TanSetObserver;

template<typename N>
struct tan_traits
{
	typedef N                             value;
	typedef typename std::complex<N>      point;
	typedef typename std::complex<N>      vector;
	typedef typename std::valarray<point> polygon;

	typedef Tan<N>            tan;
	typedef TanSet<N>         tanset;
	typedef TanSetObserver<N> observer;
};

template<typename N>
class TanSet
{
public:
	typedef typename tan_traits<N>::polygon  polygon;
	typedef typename tan_traits<N>::tan      tan;

	typedef std::vector< Tan<N> > container;

	TanSet ();

	template<typename InputIterator>
	TanSet (InputIterator, InputIterator);

	void begin_motion (int, int);
	void move         (int, int);
	void flip         ();
	void rotate       (float);
	void end_motion   ();

	void set_size     (int, int);
	void add_obstacle (const polygon &);

	const container& tans      () const;
	const tan&       selection () const;

	virtual void operator~ ();

protected:

	container _tans;
	tan       _selection;

};

template<typename N>
class Tan
{
public:
	typedef typename tan_traits<N>::polygon polygon;

	bool is_selected () const;
	bool is_offset   () const;

	const polygon& coords         () const;
	const polygon  desired_coords () const;

	friend class tanset;

private:

	Tan(const polygon &);

	polygon _coords;
};

#include "tans.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
