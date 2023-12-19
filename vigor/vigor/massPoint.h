#pragma once
#include"Block.h"
#include"Spring.h"
#include "springType.h"
#include<vector>

namespace game {
	class Block;
	class massPoint
	{
	public:
		/// <summary>
		/// ���g����������u���b�N��ID
		/// </summary>
		int blockID;
		/// <summary>
		/// ����
		/// </summary>
		float mass;
		/// <summary>
		/// ���̎��_���Z�b�g����Ă���u���b�N�̒��_�̃C���f�b�N�X
		/// </summary>
		int vertexIndex;
		glm::vec3 prev_position;
		glm::vec3 prev_velocity;
		/// <summary>
		/// ���̎��_�������Ă���u���b�N�ւ̎Q��
		/// </summary>
		Block *block;
		/// <summary>
		/// ���̎��_�ɐڑ����Ă���o�l�̃R���N�V����
		/// </summary>
		std::vector<game::Spring*> springs;
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="_blockID"></param>
		/// <param name="vertexIndex"></param>
		/// <param name="_block"></param>

		massPoint(int _blockID, int vertexIndex, Block* _block);
		void AddSpring(game::massPoint* _another, springType springType);
	private:
	};
}


