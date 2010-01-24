#include <GL/glew.h>

template<typename GameTraits>
class BasicRenderer
{
public:
	typedef typename GameTraits::controller state;
	typedef typename GameTraits::point      point;

	BasicRenderer(const state &);

	void init    ();
	void reshape (int w, int h);
	void render  ();

	point transform(int x, int y) const;

private:

	const state & _state;

	int _width, _height;

	GLhandleARB _shader;
	GLint       _handle[5];
};

#include "render_basic.hcc"

/*
** vim: ts=4 sw=4 cindent
*/
