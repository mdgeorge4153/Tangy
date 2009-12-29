#include <GL/gl.h>
#include <iterator>

template<typename GameTraits>
void
render_opengl (const typename GameTraits::controller & c)
{
	glClear(GL_COLOR_BUFFER_BIT);

	typedef typename GameTraits::tanset tanset;

	const tanset & tans = c.tans();

	for (typename tanset::container::const_iterator i = tans.tans().begin(); i != tans.tans().end(); i++)
	{
		typedef typename std::vector<typename GameTraits::point> pointset;

		pointset points;
		i->points(std::back_inserter(points));

		if (i == c.selection())
			glColor4f(0.2, 0.0, 1.0, 1.0);
		else
			glColor4f(0.13, 0.0, 0.66, 1.0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);

		for (typename pointset::iterator j = points.begin(); j != points.end(); j++)
		{
			glVertex2f(j->real(), j->imag());
		}

		glEnd();

		glColor4f(0.06, 0.0, 0.32, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2.0);
		glBegin(GL_POLYGON);

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
