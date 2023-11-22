#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>


class Window
{
	//ウィンドウのハンドル
	GLFWwindow* const _mWindow;
	//TODO:アスペクト比を一定に保つようにしておく
public:
	Window(int width = 1000, int height = 800, const char* title = "OpenGL Window")
		:_mWindow(glfwCreateWindow(width, height, title, NULL, NULL))
	{
		if (_mWindow == NULL)
		{
			std::cerr << "Can't create window!" << std::endl;
			exit(1);
		}

		//描画対象のウィンドウを設定する
		glfwMakeContextCurrent(_mWindow);

		//リサイズ時のコールバック関数(イベント発火時に呼ばれる関数)を登録する.
		glfwSetWindowSizeCallback(_mWindow, resizeWindow);
		resizeWindow(_mWindow, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glm::mat4 
		glLoadMatrixd();
		glfwSwapInterval(1);
	}

	virtual ~Window() {
		glfwDestroyWindow(_mWindow);
	}

	explicit operator bool()
	{
		//イベントの検出を行う
		//TODO: waitだとイベント検出まで動作止まらないっけ？調べておくこと
		glfwWaitEvents();
		
		return !glfwWindowShouldClose(_mWindow);
	}

	//メソッド名 + const でメンバに変更を加えないことを明示する
	void swapBuffer() const {
		glfwSwapBuffers(_mWindow);
	}

	//ウィンドウのリサイズ処理を行う
	static void resizeWindow(GLFWwindow *const window, int width, int height) {
		int framebufferWidth, framebufferHeight;
		//引数windowのフレームバッファイサイズを取得し，サイズを2,3の引数に格納する
		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

		//ビューポート(描画範囲)の設定を行う
		glViewport(0, 0, framebufferWidth, framebufferWidth);
	}
};

