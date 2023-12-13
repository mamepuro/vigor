#pragma once
#include"Block.h"
#include<vector>

namespace game {
	class Block;
	class massPoint
	{
		/// <summary>
		/// ���g����������u���b�N��ID
		/// </summary>
		const int bolckID;
		/// <summary>
		/// ����
		/// </summary>
		const float mass;
		/// <summary>
		/// ���̎��_���Z�b�g����Ă���u���b�N�̒��_�̃C���f�b�N�X
		/// </summary>
		const int vertexIndex;
		/// <summary>
		/// ���̎��_�������Ă���u���b�N�ւ̎Q��
		/// </summary>
		Block *block;
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="_blockID"></param>
		/// <param name="vertexIndex"></param>
		/// <param name="_block"></param>
		massPoint(int _blockID, int vertexIndex, Block _block);
	};
}


