#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <cmath>

class Window
{
	//�E�B���h�E�̃n���h��
	GLFWwindow* const _mWindow;
	//TODO:�A�X�y�N�g������ɕۂ悤�ɂ��Ă���
public:
	Window(int width = 1000, int height = 800, const char* title = "OpenGL Window")
		:_mWindow(glfwCreateWindow(width, height, title, NULL, NULL))
	{
		if (_mWindow == NULL)
		{
			std::cerr << "Can't create window!" << std::endl;
			exit(1);
		}

		//�`��Ώۂ̃E�B���h�E��ݒ肷��
		glfwMakeContextCurrent(_mWindow);

		//���T�C�Y���̃R�[���o�b�N�֐�(�C�x���g���Ύ��ɌĂ΂��֐�)��o�^����.
		glfwSetWindowSizeCallback(_mWindow, resizeWindow);
		resizeWindow(_mWindow, width, height);
		glfwSwapInterval(1);
	}

	virtual ~Window() {
		glfwDestroyWindow(_mWindow);
	}

	explicit operator bool()
	{
		//�C�x���g�̌��o���s��
		//TODO: wait���ƃC�x���g���o�܂œ���~�܂�Ȃ������H���ׂĂ�������
		glfwWaitEvents();
		
		return !glfwWindowShouldClose(_mWindow);
	}

	//���\�b�h�� + const �Ń����o�ɕύX�������Ȃ����Ƃ𖾎�����
	void swapBuffer() const {
		glfwSwapBuffers(_mWindow);
	}

	//�E�B���h�E�̃��T�C�Y�������s��
	static void resizeWindow(GLFWwindow *const window, int width, int height) {
		int framebufferWidth, framebufferHeight;
		//����window�̃t���[���o�b�t�@�C�T�C�Y���擾���C�T�C�Y��2,3�̈����Ɋi�[����
		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

		//�r���[�|�[�g(�`��͈�)�̐ݒ���s��
		glViewport(0, 0, framebufferWidth, framebufferWidth);
		/*
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
		*/
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//���_�̐ݒ�
		gluLookAt(0.0, 0.0, -5.0, //�J�����̍��W
			0.0, 0.0, 0.0, // �����_�̍��W
			0.0, 1.0, 0.0); // ��ʂ̏�������w���x�N�g��
			
			
	}
};

