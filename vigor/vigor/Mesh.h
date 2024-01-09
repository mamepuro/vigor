#pragma once
#ifndef OPENGL_PBR_MAP_MESH_H_
#define OPENGL_PBR_MAP_MESH_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace game {

	class Mesh {
	public:
		std::vector<glm::vec3> vertices_;
		std::vector<glm::vec3> GetVertices() const;
		void SetVertices(std::vector<glm::vec3> vertices);
		void UpdateModel();
		/**
		 * @brief VAO���o�C���h���`�悷��
		 */
		void Draw() const;
		/**
		 * @brief VAO���o�C���h���`�悷��(�Ő��`��p�̃v���O�������g�p����)
		 * @param program �Ő��`��p�̃v���O����
		 */
		void Draw(GLuint program) const;
		/**
		 * @brief �R���X�g���N�^
		 * @param vertices ���_�ʒu�̗�
		 * @param colors ���_�F�̗�
		 *
		 * �W�I���g�����\�z���AVBO��VAO���\�z���܂��B
		 * �e�풸�_���͑O���珇��3���ň�̖ʂ��\�����Ă����܂��B
		 */
		void DrawPoints() const;
		Mesh(std::vector<glm::vec3>& vertices);
		/**
		 * @brief �f�X�g���N�^
		 *
		 * VBO��VAO���J�����܂��B
		 */
		~Mesh();

		// �R�s�[�֎~
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		/**
		 * @brief ���[�u�R���X�g���N�^
		 * @param other ���[�u��
		 *
		 * ���[�u���VAO�y��VBO��0�ɐݒ肳��܂��B
		 */
		Mesh(Mesh&& other) noexcept;

		/**
		 * @brief ���[�u������Z�q
		 * @param other ���[�u��
		 *
		 * ���[�u���VAO�y��VBO��0�ɐݒ肳��܂��B
		 */
		Mesh& operator=(Mesh&& other) noexcept;

		/// <summary>
		/// �e�X�g�p�̃��b�V���t�@�C�����쐬����
		/// </summary>
		/// <returns>���b�V���f�[�^</returns>
		static std::shared_ptr<Mesh> CreateTestMesh();
		/**
   * @brief obj��ǂݍ��ސÓI�����o�֐�
   * @param file �ǂݍ���obj�t�@�C���̃p�X
   * @return �ǂݍ���Mesh
   */
		static std::shared_ptr<Mesh> LoadObjMesh(const std::string file);



		/**
		 * @brief ��������w�肵����؂蕶���ŕ�������ÓI�����o�֐�
		 * @param s �������镶����
		 * @param delim �����Ɏg����؂蕶��
		 * @return �������ꂽ������
		 */
		static std::vector<std::string> SplitString(const std::string& s, char delim);

	private:
		GLuint size_;
		GLuint vertices_vbo_;
		GLuint colors_vbo_;
		GLuint vao_;


		/**
		 * @brief OpenGL�̃I�u�W�F�N�g���J������
		 *
		 * �R���X�g���N�^�Ŋm�ۂ���VAO��VBO���J�����܂��B
		 */
		void Release();
	};

}  // namespace game

#endif  // OPENGL_PBR_MAP_MESH_H_