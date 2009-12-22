/*


  Simple Demo for GLSL

  www.lighthouse3d.com

*/

#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include "textfile.h"
#include <malloc.h>
#include <stdlib.h>
#include <math.h>


GLhandleARB f,p;

typedef struct Wave {
	float x, y;
	float xv, yv;
	GLint loc;
} Wave;

const int nwaves = 3;
Wave waves[nwaves];

void printInfoLog(GLhandleARB obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB,
							  &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetInfoLogARB(obj, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
		free(infoLog);
	}
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);


}


void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, 
	          0.0,0.0,-1.0,
	          0.0f,1.0f,0.0f);

	for (int i = 0; i < nwaves; i++)
	{
		waves[i].x += waves[i].xv;
		waves[i].y += waves[i].yv;

		if (waves[i].x < 0 || waves[i].x > 400)
			waves[i].xv = - waves[i].xv;
		if (waves[i].y < 0 || waves[i].y > 400)
			waves[i].yv = -waves[i].yv;

		glUniform2fARB(waves[i].loc, waves[i].x, waves[i].y);
	}

	glutSolidTeapot(1);

	for (int i = 0; i < nwaves; i++)
		glUniform2fARB(waves[i].loc, 400 - waves[i].y, 400 - waves[i].x);

	glTranslatef(0.5, 0.5, 0.5);
	glutSolidTeapot(1);

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) 
		exit(0);
}

void setShaders() {

	f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	const char * fsource = textFileRead("organic.frag");
	glShaderSourceARB(f, 1, &fsource,NULL);

	glCompileShaderARB(f);
	printInfoLog(f);

	p = glCreateProgramObjectARB();
	glAttachObjectARB(p,f);
	glLinkProgramARB(p);
	printInfoLog(p);
	glUseProgramObjectARB(p);

	glUniform1iARB(glGetUniformLocationARB(p, "nwaves"), nwaves);

	for (int i = 0; i < nwaves; i++) {
		waves[i].x = (float) rand() / RAND_MAX * 400;
		waves[i].y = (float) rand() / RAND_MAX * 400;
		waves[i].xv = (float) rand() / RAND_MAX / 20;
		waves[i].yv = (float) rand() / RAND_MAX / 20;

		char buf[20];
		snprintf(buf,20,"waves[%d]", i);
		waves[i].loc = glGetUniformLocationARB(p, buf);
	}
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("MM 2004-05");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0,1.0,1.0,1.0);
//	glEnable(GL_CULL_FACE);

	glewInit();
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		printf("Ready for GLSL\n");
	else {
		printf("No GLSL support\n");
		exit(1);
	}

	setShaders();

	glutMainLoop();
	return 0;
}

