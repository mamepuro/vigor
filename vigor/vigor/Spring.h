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
		Spring(float _k, game::massPoint* _left, game::massPoint* _right, float restLength, springType springType);
	private:

	};

}

