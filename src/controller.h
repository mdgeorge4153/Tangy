/*
 * controller.h - classes for mapping inputs (e.g. mouse motion and clicks) to
 *                tan manipulations (e.g. move, flip, rotate)
 */

#ifndef __tangy_mouse_controller_h__
#define __tangy_mouse_controller_h__ 1

/*
** Simple Mouse Controller *****************************************************
**
** This takes mouse input and converts it to move, flip, rotate, and pan.  It is
** simple because it only allows one action at a time.  For example, while
** dragging, you cannot flip or rotate.
*/

template<typename GameTraits>
class SimpleMouseController
{
public:
	typedef typename GameTraits::tanset           tanset;
	typedef typename GameTraits::tan_handle       tan_handle;
	typedef typename GameTraits::const_tan_handle const_tan_handle;
	typedef typename GameTraits::point            position;
	typedef typename GameTraits::vector           vector;

	SimpleMouseController (tanset &);
	~SimpleMouseController ();

	void move_to    (const position &);

	void left_down  ();
	void left_up    ();

	void right_down ();
	void right_up   ();

	const tanset &   tans () const; 
	const_tan_handle selection () const;
private:

	// this class uses the state design pattern internally to manage the mouse state

	class State;

	position   _pos;
	tanset &   _tans;
	tan_handle _selection;
	State  *   _state;

	void pacify();

	struct State
	{
		State (SimpleMouseController &);
		virtual ~State();

		virtual void move       () {};
		virtual void left_down  () {};
		virtual void left_up    () {};
		virtual void right_down () {};
		virtual void right_up   () {};

		void transition (State *);

		SimpleMouseController & _context;
	};

	struct Inactive : public State
	{
		Inactive (SimpleMouseController &);

		virtual void left_down  ();
		virtual void right_down ();
	};

	struct Panning : public State
	{
		Panning (SimpleMouseController &);

		virtual void move    ();
		virtual void left_up ();

		position _last_pos;
	};

	struct Dragging : public State
	{
		Dragging (SimpleMouseController &);

		virtual void move     ();
		virtual void left_up  ();

		vector _offset;
	};

	struct Flipping : public State
	{
		Flipping (SimpleMouseController &);

		virtual void move     ();
		virtual void right_up ();
	};

	struct Rotating : public State
	{
		Rotating (SimpleMouseController &);

		virtual void move     ();
		virtual void right_up ();

		vector _rot_offset;

		vector offset ();
	};
};

/*
** ComplexMouseController ******************************************************
*/

// TODO

/*
** MultitouchController ********************************************************
*/

// TODO

#include "controller.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
