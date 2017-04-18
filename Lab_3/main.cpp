//
//  main.cpp
//  1
//
//  Created by Александр on 14.04.17.
//  Copyright © 2017 Александр. All rights reserved.
//

#include <iostream>
#include <math.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

 
using namespace std;

bool createMas = false;
float **masF, **masFF;
int masSize;

// Control camera

int i,j;
//  Угол поворота камеры
float angle = 0.0f;
// Вектор направления
float lx=0.0f,lz=-1.0f;
// XZ позиция
float x=0.0f, z=5.0f;

float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;


void computePos(float deltaMove) {
    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}


void processNormalKeys(unsigned char key, int xx, int yy) {
    if (key == 107)
        exit(0);
}

void pressKey(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_UP : deltaMove = 0.5f; break;
        case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
    }
}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
}

void mouseMove(int x, int y) {
    // Когда нажата левая кнопка мыши
    if (xOrigin >= 0) {
        // Обновление deltaAngle
        deltaAngle = (x - xOrigin) * 0.001f;
        // Обновление направления камеры
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}

void mouseButton(int button, int state, int x, int y) {
    // Работает, когда нажата левая кнопка мыши
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            angle += deltaAngle;
            xOrigin = -1;
        }
        else  {
            xOrigin = x;
        }
    }
}


void DrawLine(float x1, float y1, float z1,
              float x2, float y2, float z2,
              float r, float g, float b)
{
    glBegin(GL_LINES);
        glColor3d(r, g, b);
        glVertex3d(x1, y1, z1);
        glVertex3d(x2, y2, z2);
    glEnd();
}

void DrawAxis(){
    
    glPushMatrix();
    double dx = 2;
    
    //Оси координат
    DrawLine(-10 * dx, 0, 0, 10 * dx, 0, 0, 1, 1, 1);
    DrawLine(0, -10 * dx, 0, 0, 10 * dx, 0, 1, 1, 1);
    
    //Деления
    for (int i = -10; i <= 10; i++){
        DrawLine(i * dx, 0.1 * dx, 0, i * dx, -0.1 * dx, 0, 1, 1, 1);
        DrawLine(0.1 * dx, i * dx, 0, -0.1 * dx, i * dx, 0, 1, 1, 1);
    }
    glPopMatrix();
}

float f(float x){
    
    return (sin(2*x));
    
}

void DrawFunc(){
    
    float x, x1 = -10, x2 = 10;
    int n = 100;
    float dx = (x2 - x1)/n;
    
    glBegin(GL_LINE_STRIP);
        glColor3f(1, 0, 0);
    
        for (x = x1; x <= x2; x += dx)
            glVertex3f(x, f(x), 0);
    glEnd();
}

// Сгенерировать массив
void GenerateMasByFunc(float **mas, float x1, float x2, float dx){
    
    for (int i = 0; i < masSize; i++){
        mas[0][i] = x1 + dx * i;
        mas[1][i] = f(x1 + dx * i);
    }
}

// Нарисовать функцию по массиву
void DrawFuncMas(float **mas, float xScale, float yScale, float r, float g, float b){
    
    glBegin(GL_LINE_STRIP);
        glColor3f(r, g, b);
        for (int i = 0; i < masSize; i++)
            glVertex3f(mas[0][i] * xScale, mas[1][i] * yScale, 0);
    glEnd();
}

// Производная функции
void CalcDFuncMas(float **mas, float **dmas, float dx){
    
    for (int i = 0; i < masSize; i++){
        dmas[0][i] = mas[0][i];
        
        if (i < masSize - 1)
            dmas[1][i] = (mas[1][i+1] - mas[1][i]) / dx;
        else
            dmas[1][i] = (mas[1][i] - mas[1][i-1]) / dx;
    }
}

void DrawMax(float **mas, int n){
        float resy = mas[1][0];
        float resx = 0.0;
        for (int i = 0; i < n; i++)
            if (mas[1][i] > resy){
                resy = mas[1][i];
                resx = mas[0][i];
            }
    
    glPointSize(5);
    
    glBegin(GL_POINTS);
        glColor3f(1, 0, 0);
        glVertex3f(resx, resy, 0);
    glEnd();
    
    glPointSize(2);
}

void DrawMin(float **mas, int n){
    float resy = mas[1][0];
    float resx = 0.0;
    for (int i = 0; i < n; i++)
        if (mas[1][i] < resy){
            resy = mas[1][i];
            resx = mas[0][i];
        }
    
    glPointSize(5);
    
    glBegin(GL_POINTS);
        glColor3f(1, 0, 0);
        glVertex3f(resx, resy, 0);
    glEnd();
    
    glPointSize(2);
}

void DrawFunction(){
    
    float xScale = 1, yScale = 1, x1 = -10, x2 = 10,
    dx = 0.01;
    masSize = int((x2 - x1)/dx);
   
    if (!createMas){
        
        masF = new float *[2];
        masF[0] = new float [masSize];
        masF[1] = new float [masSize];
        
        GenerateMasByFunc(masF, x1, x2, dx);
        createMas = true;
        
        masFF = new float *[2];
        masFF[0] = new float [masSize];
        masFF[1] = new float [masSize];
        
        CalcDFuncMas(masF, masFF, dx);
    }
    
   //DrawFuncMas(masF, xScale, yScale, 1, 0, 0);
    
    //Точки максимума/минимума
    DrawMax(masF, masSize);
    DrawMin(masF, masSize);
    
    for (int i = 0; i < masSize; i++){
        float eps = 0.1;
        
        //Точки экстремума
        if (masFF[1][i] <= eps && masFF[1][i] >= -eps){
            glPointSize(6);
            glBegin(GL_POINTS);
                glColor3f(1, 0, 1);
                glVertex3f(masF[0][i], masF[1][i], 0);
                glEnd();
            glPointSize(2);
        }
        //Ракскраска убывания/возрастания
        if (masFF[1][i] < 0){
            glBegin(GL_POINTS);
                glColor3f(0, 0, 1);
                glVertex3f(masF[0][i], masF[1][i], 0);
            glEnd();
        }
        if (masFF[1][i] > 0){
            glBegin(GL_POINTS);
                glColor3f(0.7f, 0.5f, 0.5f);
                glVertex3f(masF[0][i], masF[1][i], 0);
            glEnd();
        }
        
    }

     DrawFuncMas(masFF, xScale, 1, 0, 1, 0);
    
}

void DeleteMas(){
    
    if (createMas){
        
        delete masF[0];
        delete masF[1];
        delete masF;
    }
}

void resize(int width,int height){
   
    glViewport(0,0,width,height);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    gluPerspective(45.0, (GLfloat)width / height, 1.0, 10000.0);
  
    gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
    glFrustum ( -1 , 1 , -1 , 1 , 1.25 , 10.0 );
    glMatrixMode( GL_MODELVIEW );
    
        glEnable(GL_DEPTH_TEST);
}

void Draw(){
    
    float dx = 1;
   
    for (int i = -10; i <= 10; i++)
        DrawLine(float(i), -10, 0, i * dx, 10, 0, 1, 1, 1);
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
   
    DrawAxis();
    DrawFunction();
    
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
    glutMainLoop();
    
    return  1;
}

int main(int argc,char ** argv){
    
    glutInit(&argc,argv);
    RunOpenGL();
    
    return 1;
}
