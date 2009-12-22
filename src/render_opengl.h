#include <GL/gl.h>

template<typename TanSet>
void
render_opengl (const TanSet & tans)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (typename TanSet::container::const_iterator i = tans.tans().begin(); i != tans.tans().end(); i++)
	{
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glColor4f(0.3, 0.0, 1.0, 1.0);

		glBegin(GL_POLYGON);

		typename TanSet::tan::point_container points = i->shape() + i->pos();

		for (unsigned j = 0; j < points.size(); j++)
		{
			glVertex2f(points[j].real(), points[j].imag());
		}

		glEnd();
	}
}

/*
** vim: ts=4 sw=4 cindent
*/
