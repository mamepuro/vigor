#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "test/test.h"

//�_�C�A���O�\���̊m�F
void TestDialog() {
	std::cout << "Hello! This is my computer! See you soon!" << std::endl;
}

void TestOpenGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2d(-0.9, -0.9);
    glVertex2d(0.9, -0.9);
    glVertex2d(0.9, 0.9);
    glVertex2d(-0.9, 0.9);
    glEnd();
    glFlush();
}
void TestDrawRectangle() {

}

void TestDrawCube() {

}


