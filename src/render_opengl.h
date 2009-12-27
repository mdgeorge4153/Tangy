#include <GL/gl.h>
#include <iterator>
#include <iostream>

template<typename TanSet>
void
render_opengl (const TanSet & tans)
{
	glClear(GL_COLOR_BUFFER_BIT);

	float x;

	glReadPixels(5, 5, 1, 1, GL_FLOAT, GL_ALPHA, &x);

	std::cout << "alpha " << x << std::endl;

	for (typename TanSet::container::const_iterator i = tans.tans().begin(); i != tans.tans().end(); i++)
	{
		typedef typename std::vector<typename TanSet::point> pointset;

		pointset points;
		i->points(std::back_inserter(points));

		glColor4f(0.3, 0.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);

		for (typename pointset::iterator j = points.begin(); j != points.end(); j++)
		{
			glVertex2f(j->real(), j->imag());
		}

		glEnd();

		glColor4f(0.0, 0.0, 0.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2.0);
		glBegin(GL_POLYGON);

		for (typename pointset::iterator j = points.begin(); j != points.end(); j++)
		{
			glVertex2f(j->real(), j->imag());
		}

		glEnd();
	}

	/*
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(-10.0, -10.0);
	glVertex2f(-10.0,  10.0);
	glVertex2f( 10.0,  10.0);
	glVertex2f( 10.0, -10.0);
	glEnd();
	*/
}

/*
** vim: ts=4 sw=4 cindent
*/
