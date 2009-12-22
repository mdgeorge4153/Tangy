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
	typedef typename GameTraits::tanset tanset;
	typedef typename GameTraits::tan    tan;
	typedef typename GameTraits::point  position;

	SimpleMouseController (tanset &);
	~SimpleMouseController ();

	void move_to    (const position &);

	void left_down  ();
	void left_up    ();

	void right_down ();
	void right_up   ();

private:

	// this class uses the state design pattern internally to manage the mouse state

	class State;

	State  * _state;
	position _pos;
	tanset & _tans;
	tan    * _selection;

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
	};

	struct Dragging : public State
	{
		Dragging (SimpleMouseController &);

		virtual void move     ();
		virtual void left_up  ();
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
