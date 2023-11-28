#pragma once
#ifndef OPENGL_PBR_MAP_APPLICATION_H_
#define OPENGL_PBR_MAP_APPLICATION_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include "MeshEntity.h"
#include "camera.h"
#include "mesh.h"

namespace game {

	class Application {
	public:
		/**
		 * @brief �A�v���P�[�V�����̃G���g���[�|�C���g
		 * @return ����I���Ȃ��true�A�ُ�I���Ȃ��false
		 *
		 * �A�v���P�[�V�����̃G���g���[�|�C���g�ł��B
		 * �����Ń��[�v���񂵃Q�[�������s���܂��B
		 * �E�B���h�E������ꂽ�ꍇ�A�Q�[�����I�������ꍇ�A
		 * ��������̃G���[�Œ�~�����ꍇ�Ȃǂɂ��̃��\�b�h���I�����܂��B
		 * �߂�l�͐���I���Ȃ��true�A�ُ�I���Ȃ��false�ł��B
		 *
		 * ```
		 * int main() {
		 *     game::Application app;
		 *     return app.Run() ? 0 : -1;
		 * }
		 * ```
		 */
		bool Run();

	private:
		GLFWwindow* window_;
		GLuint program_;
		GLuint model_loc_;
		GLuint view_projection_loc_;
		std::vector<MeshEntity> mesh_entities_;
		std::unique_ptr<Camera> camera_;

		/**
		 * @brief ����������
		 * @return ����I���Ȃ��true�A�ُ�I���Ȃ��false
		 */
		bool Init();

		/**
		 * @brief GLFW�̃E�B���h�E���쐬����
		 * @param width �E�B���h�E�̕�
		 * @param height �E�B���h�E�̍���
		 * @return ����I���Ȃ��true�A�ُ�I���Ȃ��false
		 *
		 * GLFW�̏������ƃE�B���h�E�쐬�AGLEW�̏������A
		 * ���̑�GL�̏����ݒ���s���܂��B
		 */
		bool InitWindow(const GLuint width, const GLuint height);

		/**
		 * @brief ���t���[���Ă΂�鏈��
		 * @param delta_time �O�t���[���Ƃ̍������ԁi�b�j
		 */
		void Update(const double delta_time);
	};

}  // namespace game

#endif  //  OPENGL_PBR_MAP_APPLICATION_H_