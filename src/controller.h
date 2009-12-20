/*
 * mouse_controller.h - maps mouse motion and clicks to tan motion and rotations
 */

#ifndef __gtans_mouse_controller_h__
#define __gtans_mouse_controller_h__ 1

class MouseController
{
public:
	MouseController (int, int, bool = false, bool = false);
	~MouseController ();

	void move_to    (int, int);

	void left_down  ();
	void left_up    ();

	void right_down ();
	void right_up   ();

private:
	struct State
	{
		State(MouseController &);
		virtual ~State();

		virtual void move_to    (int, int) {};
		virtual void left_down  ()         {};
		virtual void left_up    ()         {};
		virtual void right_down ()         {};
		virtual void right_up   ()         {};

		void transition (State *);

		MouseController & _dragger;
	};

	struct Unselected : public State
	{
		Unselected (MouseController &);
		virtual ~Unselected ();

		virtual void move_to    (int, int); // -> Unselected, Hover
		virtual void left_down  ();         // -> Panning
	};

	struct Hovering : public State
	{
		Hovering (MouseController &);
		virtual ~Hovering ();

		virtual void move_to    (int, int); // -> Unselected, Hover
		virtual void left_down  ();         // -> Dragging
		virtual void right_down ();         // -> Dragging
	};

	struct Panning : public State
	{
		Panning (MouseController &);
		virtual ~Panning ();

		virtual void move_to (int, int);    // -> Panning
		virtual void left_up ();            // -> Unselected
	};

	struct Dragging : public State
	{
		virtual void move_to    (int, int); // -> Dragging

		virtual void left_down  ();         // -> DoubleDragging
		virtual void right_down ();         // -> DoubleDragging

		virtual void left_up    ();         // -> Selected, SelectedHover
		virtual void right_up   ();         // -> Selected, SelectedHover
	};

	struct DoubleDragging : public State
	{
		virtual void move_to  (int, int);   // -> DoubleDragging
		virtual void left_up  ();           // -> Dragging
		virtual void right_up ();           // -> Dragging
	};

	struct Selected : public State
	{
		virtual void move_to    (int, int); // -> Selected, SelectHovering
		virtual void left_down  ();         // -> Panning
		virtual void right_down ();         // -> Rotating
	};

	struct SelectHovering : public State
	{
		virtual void move_to    (int, int); // -> Selected, SelectHovering
		virtual void left_down  ();         // -> Dragging
		virtual void right_down ();         // -> Dragging
	};

	struct Rotating : public State
	{
		virtual void move_to  (int, int);   // -> Rotating
		virtual void right_up ();           // -> Selected, SelectHovering
	};

	State * _state;
	int     _last_x, _last_y;

};


#endif

/*
** vim: ts=4 sw=4 cindent
*/
