//Develop by HigerSkill 
//OpenGL 2.x 
//2017 

#include <iostream>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/GLAUX.H>

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "glaux.lib")
#pragma comment (lib, "legacy_stdio_definitions.lib")

struct coordinates {
	//Color primitives
	double r, g, b;

	//We will only use the necessary coordinates
	double x1, y1;
	double x2, y2;
	double x3, y3;
};

void CALLBACK resize(int width, int height) {

	glViewport(0, 0, width, height);

	//This matrix will change
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)width / height, 1.0, 10000.0);

	//Camera 
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);

	//Clear and color window
	glClearColor(1, 1, 0, 0.0);
}

void Triangles(coordinates triangle) {
	glBegin(GL_TRIANGLE_STRIP);

	glColor3d(triangle.r, triangle.g, triangle.b);

	glVertex3d(triangle.x1, triangle.y1, 0);
	glVertex3d(triangle.x2, triangle.y2, 0);
	glVertex3d(triangle.x3, triangle.y3, 0);

	glEnd();
}

void Line(coordinates line, float width) {
	glEnable(GL_LINE_SMOOTH);

	glBegin(GL_LINES);

	glColor3d(line.r, line.g, line.b);

	glVertex3d(line.x1, line.y1, 0);
	glVertex3d(line.x2, line.y2, 0);

	glEnd();

	glLineWidth(width);
}

void Point(coordinates point, float size) {

	glPointSize(size);


	glBegin(GL_POINTS);

	glColor3d(point.r, point.g, point.b);
	glVertex3d(point.x1, point.y1, 0);

	glEnd();
	glEnable(GL_POINT_SMOOTH);
}

void Round(coordinates round, float radius)
{
	glColor3d(round.r, round.g, round.b);
	int n = 60;
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <n; i++)
		glVertex3d(round.x1 + radius*sin(i * 2 * 3.14 / n),
			round.y1 + radius*cos(i * 2 * 3.14 / n), 0);
	glEnd();
}


void draw() {
	float width, size, radius;

	coordinates line1 = { 1., 1., 1., -5., 4.85, 5., 4.85 };
	coordinates line2 = { 0., 1., 1., -5., -0.5, 5., -0.5 };
	coordinates line3 = { 0., 0., 1., -2.5, 5., -2.5, -0.5 };
	coordinates line4 = { 0., 0., 1., 2.5, 5., 2.5, -0.5 };
	width = 500;

	coordinates point1 = { 1, 0, 0, 0, 2.3f };
	size = 500;

	coordinates round = { 1., 0., 0., 0., 1.7, 0. };
	radius = 3;

	//The drawing order
	Line(line2, width);
	Line(line4, width);
	Round(round, radius);
	Line(line3, width);
	Line(line1, width);
}

void CALLBACK display(void) {

	/*Clears video buffer faster, than
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslated(0, 0, -20);

	//Enable anti-aliasing primitives
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	draw();

	//Frame switching
	auxSwapBuffers();
}


void RunOpenGL() {
	//Resolution 
	auxInitPosition(0, 0, 600, 600);

	auxInitDisplayMode(AUX_RGB | AUX_DEPTH | AUX_DOUBLE);

	//Windows title
	auxInitWindow(LPCWSTR("Lab_1"));

	auxIdleFunc(display);
	auxReshapeFunc(resize);
	auxMainLoop(display);
}

void main() {
	RunOpenGL();
}
