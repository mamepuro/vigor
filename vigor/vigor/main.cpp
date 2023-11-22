#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "test/test.h"
#include "Window.h"

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2d(-0.9, -0.9);
    glVertex2d(0.9, -0.9);
    glVertex2d(0.9, 0.9);
    glVertex2d(-0.9, 0.9);
    glEnd();
    glFlush();
}

int main() {
    //dialogtest
    TestDialog();
    if (!glfwInit()) {
        return -1;
    }
    //GLFWwindow* window = glfwCreateWindow(1000, 800, "test", NULL, NULL);
    Window window;
    if (!window) {
        glfwTerminate();
        return -1;
    }
    //glfwMakeContextCurrent(window); //���̊֐��������
    //TODO: �Ȃ���glew�����s�ł��Ȃ��̂Ō��������ƏC�����s��
    //glewInit(); //���s���Ȃ��Ă͂����Ȃ�
    glfwSwapInterval(1);

    while (window) {
        glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
        TestOpenGL();
        

        window.swapBuffer();
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}