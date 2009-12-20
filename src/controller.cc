#include "controller.h"

MouseController::
MouseController (int x, int y, bool left_down, bool right_down)
	: _state(new Unselected(* this))
{
	// TODO
}

MouseController::
~MouseController ()
{
	delete _state;
}

void
MouseController::
move_to (int x, int y)
{
	_state->move_to (x, y);
}

void
MouseController::
left_down ()
{
	_state->left_down ();
}

void
MouseController::
left_up ()
{
	_state->left_up ();
}

void
MouseController::
right_down ()
{
	_state->right_down ();
}

void
MouseController::
right_up ()
{
	_state->right_up ();
}

MouseController::State::
State (MouseController & d)
	: _dragger (d)
{
}

MouseController::State::
~State ()
{
}

void
MouseController::State::
transition (State * new_state)
{
	_dragger._state = new_state;
	delete this;
}


/*
** vim: ts=4 sw=4 cindent
*/
