/* 
 * File:   TDGame.cpp
 * Author: lsv
 * 
 * Created on 10 декабря 2014 г., 21:59
 */

#include "TDGame.h"
#include <ProcessLogger.h>
#include <GL/gl.h> // Библиотека OpenGL
#include <GL/glu.h> // Библиотека GLU

TDGame::TDGame() {
}

TDGame::~TDGame() {
}

void TDGame::OnActivate() {
}

void TDGame::OnDeactivate() {
}

void TDGame::OnLoop() {
}

void drawCube(float xrf, float yrf, float zrf){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -7.0f);    // Сдвинуть вглубь экрана
     
    glRotatef(xrf, 1.0f, 0.0f, 0.0f);   // Вращение куба по X, Y, Z
    glRotatef(yrf, 0.0f, 1.0f, 0.0f);   // Вращение куба по X, Y, Z
    glRotatef(zrf, 0.0f, 0.0f, 1.0f);   // Вращение куба по X, Y, Z
     
    glBegin(GL_QUADS);                  // Рисуем куб
 
    glColor3f(0.0f, 1.0f, 0.0f);        // Синяя сторона (Верхняя)
    glVertex3f( 1.0f, 1.0f, -1.0f);     // Верхний правый угол квадрата
    glVertex3f(-1.0f, 1.0f, -1.0f);     // Верхний левый
    glVertex3f(-1.0f, 1.0f,  1.0f);     // Нижний левый
    glVertex3f( 1.0f, 1.0f,  1.0f);     // Нижний правый
     
    glColor3f(1.0f, 0.5f, 0.0f);        // Оранжевая сторона (Нижняя)
    glVertex3f( 1.0f, -1.0f,  1.0f);    // Верхний правый угол квадрата
    glVertex3f(-1.0f, -1.0f,  1.0f);    // Верхний левый
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Нижний левый
    glVertex3f( 1.0f, -1.0f, -1.0f);    // Нижний правый
     
    glColor3f(1.0f, 0.0f, 0.0f);        // Красная сторона (Передняя)
    glVertex3f( 1.0f,  1.0f, 1.0f);     // Верхний правый угол квадрата
    glVertex3f(-1.0f,  1.0f, 1.0f);     // Верхний левый
    glVertex3f(-1.0f, -1.0f, 1.0f);     // Нижний левый
    glVertex3f( 1.0f, -1.0f, 1.0f);     // Нижний правый
 
    glColor3f(1.0f,1.0f,0.0f);          // Желтая сторона (Задняя)
    glVertex3f( 1.0f, -1.0f, -1.0f);    // Верхний правый угол квадрата
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Верхний левый
    glVertex3f(-1.0f,  1.0f, -1.0f);    // Нижний левый
    glVertex3f( 1.0f,  1.0f, -1.0f);    // Нижний правый
 
    glColor3f(0.0f,0.0f,1.0f);          // Синяя сторона (Левая)
    glVertex3f(-1.0f,  1.0f,  1.0f);    // Верхний правый угол квадрата
    glVertex3f(-1.0f,  1.0f, -1.0f);    // Верхний левый
    glVertex3f(-1.0f, -1.0f, -1.0f);    // Нижний левый
    glVertex3f(-1.0f, -1.0f,  1.0f);    // Нижний правый
     
    glColor3f(1.0f,0.0f,1.0f);          // Фиолетовая сторона (Правая)
    glVertex3f( 1.0f,  1.0f, -1.0f);    // Верхний правый угол квадрата
    glVertex3f( 1.0f,  1.0f,  1.0f);    // Верхний левый
    glVertex3f( 1.0f, -1.0f,  1.0f);    // Нижний левый
    glVertex3f( 1.0f, -1.0f, -1.0f);    // Нижний правый
 
    glEnd();                            // Закончили квадраты    
 
}

void TDGame::OnRender() {
    logger<<"draw cube\n";
    drawCube(10,10,10);
}

