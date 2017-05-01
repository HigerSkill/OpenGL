//
//  main.cpp
//  opengl lab 4
//
//  Created by Александр on 24.04.17.
//  Copyright © 2017 Александр. All rights reserved.
//

#include <iostream>
#include <map>
#include <math.h>
#include <mach/mach_time.h>
#include <CoreServices/CoreServices.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include "camera.h"

using namespace std;

void DrawLine(float x1, float y1, float z1,
              float x2, float y2, float z2,
              float r,  float g,  float b)
{
    
    glBegin(GL_LINES);
    
    glVertex3d(x1, y1, z1);
    glVertex3d(x2, y2, z2);
    glEnd();
}

void DrawTriangle(float x1, float y1, float z1,
                  float x2, float y2, float z2,
                  float x3, float y3, float z3, int n)
{
    switch(n){
        case 1: glColor3f(1, 0, 0); break;
        case 2: glColor3f(0, 1, 0); break;
        case 3: glColor3f(0, 0, 1); break;
        case 4: glColor3f(1, 1, 0); break;
        case 5: glColor3f(1, 0, 1); break;
        case 6: glColor3f(0, 1, 1); break;
        case 7: glColor3f(0.5f, 0.5f, 1.0f); break;
        default: glColor4f(1, 1, 1, 0.1f); break;
    }
    
    glBegin(GL_TRIANGLES);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x3, y3, z3);
    glEnd();
}

void DrawSerpinski(float x1, float y1,
                   float x2, float y2,
                   float x3, float y3, int n)
{
    
    float x1n, x2n, x3n, y1n, y2n, y3n;
    
    if (n > 0) {
        x1n = (x1 + x2) / 2;
        y1n = (y1 + y2) / 2;
        x2n = (x2 + x3) / 2;
        y2n = (y2 + y3) / 2;
        x3n = (x3 + x1) / 2;
        y3n = (y3 + y1) / 2;
        
        DrawTriangle(x1n, y1n, 0, x2n, y2n, 0, x3n, y3n, 0, n);
        
        DrawSerpinski(x1, y1, x1n, y1n, x3n, y3n, n-1);
        DrawSerpinski(x2, y2, x1n, y1n, x2n, y2n, n-1);
        DrawSerpinski(x3, y3, x2n, y2n, x3n, y3n, n-1);
    }
}

//OpenGL initialize
void resize(int width, int height){
    
    glViewport(0, 0, width, height);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    gluPerspective(45.0, (GLfloat)width / height, 1.0, 10000.0);
    
    gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
    glFrustum ( -1 , 1 , -1 , 1 , 1.25 , 10.0 );
    glMatrixMode( GL_MODELVIEW );
    
    glEnable(GL_DEPTH_TEST);
}

void renderScene(void) {
    
    if (deltaMove)
        computePos(deltaMove);
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Сброс трансформаций
    glLoadIdentity();
    // Установка камеры
    gluLookAt(	x, 1.0f, z,
              x+lx, 1.0f,  z+lz,
              0.0f, 1.0f,  0.0f);
    
    glTranslated(0,0,-10);
    
    int n;
    int nmax = 8; //Levels
    
    n = TickCount() / 100 % (nmax * 2);
    
    if (n > nmax)
        n = nmax + nmax - n;
    if (n == 0)
        n = 1;
    
    
    
    DrawSerpinski(15, -15, -15, -15, 0, 20, n);
    DrawTriangle(15, -15, 0, -15, -15, 0, 0, 20, 0, 0);
    
    glutSwapBuffers();
}

int RunOpenGL(){
    
    glutInitWindowPosition(400, 0);
    glutInitWindowSize(600, 600);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutCreateWindow("Lab");
    
    glutIdleFunc(renderScene);
    glutReshapeFunc(resize);
    glutDisplayFunc(renderScene);
    
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutMainLoop();
    
    return  1;
}

int main(int argc,char ** argv){
    
    glutInit(&argc,argv);
    RunOpenGL();
    
    return 1;
}
