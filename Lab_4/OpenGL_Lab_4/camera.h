//
//  camera.h
//  opengl lab 4
//
//  Created by Александр on 24.04.17.
//  Copyright © 2017 Александр. All rights reserved.
//

#ifndef camera_h
#define camera_h

void releaseKey(int,int,int);

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
    if (key == 106)
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
    
void mouseMove(int x, int y){
        // Когда нажата левая кнопка мыши
        if (xOrigin >= 0) {
            // Обновление deltaAngle
            deltaAngle = (x - xOrigin) * 0.001f;
            // Обновление направления камеры
            lx = sin(angle + deltaAngle);
            lz = -cos(angle + deltaAngle);
        }
    }
    
void mouseButton(int button, int state, int x, int y){
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
    

#endif /* camera_h */
