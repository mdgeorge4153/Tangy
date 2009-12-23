#include <GL/gl.h>
#include <iterator>

template<typename TanSet>
void
render_opengl (const TanSet & tans)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (typename TanSet::container::const_iterator i = tans.tans().begin(); i != tans.tans().end(); i++)
	{
		typedef typename std::vector<typename TanSet::point> pointset;

		glColor4f(0.0, 0.0, 1.0, 1.0);
		glColor4f(0.3, 0.0, 1.0, 1.0);

		glBegin(GL_POLYGON);

		pointset points;
		i->points(std::back_inserter(points));

		for (typename pointset::iterator j = points.begin(); j != points.end(); j++)
		{
			glVertex2f(j->real(), j->imag());
		}

		glEnd();
	}
}

/*
** vim: ts=4 sw=4 cindent
*/
