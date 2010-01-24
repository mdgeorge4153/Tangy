#include <GL/glew.h>
#include <vector>

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

	struct WaveState;
	std::vector<WaveState> _waves;
};

#include "render_basic.hcc"

/*
** vim: ts=4 sw=4 cindent
*/
