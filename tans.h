/*
 * tans.h - interface for manipulating sets of tans.
 */

#ifndef __gtans_tans_h__
#define __gtans_tans_h__ 1

#include <vector>
#include <valarray>

template<typename N> class Tan;
template<typename N> class TanSet;
template<typename N> class TanSetObserver;

template<typename N>
struct tan_traits
{
	typedef N                    value;
	typedef std::complex<N>      point;
	typedef std::complex<N>      vector;
	typedef std::valarray<point> polygon;

	typedef Tan<N>            tan;
	typedef TanSet<N>         tanset;
	typedef TanSetObserver<N> observer;
};

template<typename N>
class Tan
	: public tan_traits<N>
{
public:
	bool is_selected () const;
	bool is_offset   () const;

	const polygon& coords () const;

	friend class tanset;
};

template<typename N>
class TanSet
	: public tan_traits<N>
{
public:

	typedef std::vector< Tan<N> > container;

	void begin_motion (int, int);
	void move         (int, int);
	void flip         ();
	void rotate       (float);
	void end_motion   ();

	void set_size     (int, int);
	void add_obstacle (const polygon&);

	void add_listener    (observer *);
	void remove_listener (observer *);

	const container& tans      () const;
	const tan&       selection () const;

protected:

	virtual void _best_fit (int, int) = 0;

};

template<typename N>
class TanSetObserver
	: public tan_traits<N>
{
public:
	virtual void selected   (const tan &) = 0;
	virtual void unselected (const tan &) = 0;
	virtual void moved      (const tan &) = 0;
	virtual void rotated    (const tan &) = 0;
};

#include "tans.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
