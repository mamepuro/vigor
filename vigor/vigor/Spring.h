#pragma once
#include "massPoint.h"
#include "springType.h"

namespace game{
	class massPoint;
	class Spring
	{
	public:
		//�o�l�[�_�̎��_
		//���� C2079�̃R���p�C���G���[����̂��߁A���N���X�̃I�u�W�F�N�g�������o�Ƃ���ꍇ�̓I�u�W�F�N�g�̃|�C���^�Ƃ���
		game::massPoint *left;
		game::massPoint *right;
		float currentLength;
		springType m_springType;
		//�����̒���
		float restLength;
		//�o�l�萔
		float k;
		std::vector<glm::vec3> vertices;
		Spring(float _k, game::massPoint* _left, game::massPoint* _right, float restLength, springType springType);
		void Draw();
	private:
		GLuint size_;
		GLuint vertices_vbo_;
		GLuint colors_vbo_;
		GLuint vao_;
	};

}

