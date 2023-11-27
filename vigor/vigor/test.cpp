#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "test/test.h"

//ダイアログ表示の確認
void TestDialog() {
	std::cout << "Hello! This is my computer! See you soon!" << std::endl;
}

void TestOpenGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex3d(-0.0, -0.0, 0.2);
    glVertex3d(0.9, -0.9, 0.2);
    glVertex3d(0.9, 0.9, 0.2);
    glVertex3d(-0.9, 0.9, 0.2);
    glEnd();
    glFlush();
}
void TestDrawRectangle() {

}

void TestDrawCube() {

}


