#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    if (!glfwInit()) {
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(1000, 800, "test", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //Ç±ÇÃä÷êîÇÊÇËÇ‡å„Ç…
    //glewInit(); //é¿çsÇµÇ»Ç≠ÇƒÇÕÇ¢ÇØÇ»Ç¢
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  

        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}