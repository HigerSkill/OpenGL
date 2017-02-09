/*OpenGL 2.x
  C++11*/

#include <iostream>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <C:\lib\GLAUX.H>

#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")
#pragma comment (lib, "glaux.lib")
#pragma comment (lib, "legacy_stdio_definitions.lib")

struct coordinates { 
	//Color primitives
	float r, g, b;  
	
	//We will only use the necessary coordinates
	float x1, y1; 
	float x2, y2;
	float x3, y3;
};

float width, size;

void CALLBACK resize(int width, int height){

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
}

void draw() {
	coordinates line1 { 1, 1, 1, -5, 4.85, 5, 4.85 };
	coordinates line2 { 0, 1, 1, -5, -0.5f, 5, -0.5f };
	coordinates line3 { 0, 0, 1, -2.5f, 5, -2.5f, -0.5f };
	coordinates line4 { 0, 0, 1, 2.5f, 5, 2.5f, -0.5f };
	width = 10;

	coordinates point1{ 1, 0, 0, 0, 2.3f };
	size = 142.5f;

	//The drawing order
	Line(line2, width);
	Line(line4, width);
	Point(point1, size);
	Line(line3, width);
	Line(line1, width);
}

void CALLBACK display(void){
	
	/*Clears video buffer faster, than 
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glLoadIdentity();
	glTranslated(0, 0, -20);
	
	//Enable anti-aliasing primitives
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	
	draw();

	//Frame switching
	auxSwapBuffers(); 
}


void RunOpenGL(){
	//Resolution 
	auxInitPosition(0, 0, 600, 600);
	
	auxInitDisplayMode(AUX_RGB | AUX_DEPTH | AUX_DOUBLE);

	//Windows title
	auxInitWindow("Lab_1");

	auxIdleFunc(display);
	auxReshapeFunc(resize);
	auxMainLoop(display);
}

void main(){
	RunOpenGL();
}
