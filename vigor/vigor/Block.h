#pragma once
#ifndef OPENGL_PBR_MAP_BLOCK_H_
#define OPENGL_PBR_MAP_BLOCK_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include"MeshEntity.h"
#include"massPoint.h"
#include"Spring.h"


namespace game {
	class massPoint;
	class Spring;
	class Block : public game::MeshEntity
	{
		static int mID;
	public:

		/*�r�̔ԍ� 1, 5 �|�P�b�g�̔ԍ�0,3*/
		//����5,3 �E��1,0�Ƃ���

		int ID;
		int union_ID;
		std::vector<glm::vec3> positions;
		int legLeftInsertBlockID;
		int legRightInsertBlockID;
		int pocketLeftInsertBlockID;
		int pocketRightInsertBlockID;
		/// <summary>
		/// �E���̃u���b�N�̖ʂƏՓ˔��肷���(���݂͍��̖ʂƏՓ˔��肷��)
		/// </summary>
		std::vector<Block*> r_connect;
		/// <summary>
		/// �����̖ʂƏՓ˔��肷���
		/// </summary>
		std::vector<Block*> l_connect;
		/// <summary>
		/// �u���b�N�������_�̃R���N�V����
		/// ���_�̓u���b�N�̑S�Ă̒��_�ɐݒu����A���̃R���N�V�����ɂ͒��_���Ɏ��_���i�[�����
		/// </summary>
		std::vector<game::massPoint*> massPoints;
		std::vector<game::Spring*> springs;
		Block(std::shared_ptr<Mesh> mesh,
			const glm::vec3 position,
			const glm::vec3 rotation,
			const glm::vec3 scale,
			int _ID,
			int _union_ID,
			std::vector<glm::vec3> _positions,
			int _legLeftInsertBlockID,
			int _legRightInsertBlockID,
			int _pocketLeftInsertBlockID,
			int _pocketRightInsertBlockID);
		void SetSpring(game::Spring* spring);
		void Simulate(float delta);
		void Connect(Block* _target);
		/// <summary>
		/// �������ɐڑ����s��
		/// </summary>
		void ConnectNext(Block* _target);
		void TestBend();

		/// <summary>
		/// �u���b�N�̃��[���h���W���X�V����
		/// </summary>
		void UpdateWorldPosition();
		/// <summary>
		/// �u���b�N�̃��[�J�����W���X�V����
		/// </summary>
		void UpdateLocalPosition();
		/// <summary>
		/// �u���b�N�̖ʓ��m�̌����𔻒肷��
		/// </summary>
		void CheckCollide();
		/// <summary>
		/// �u���b�N���f���̊e���_�̃��[���h���W
		/// </summary>
		std::vector<glm::vec3> world_position;
		std::vector<glm::vec3> local_position;
	private:
		/// <summary>
		/// �u���b�N���f���̊e���_���[�J�����W(���f�����W)
		/// </summary>

	};
}


#endif  // OPENGL_PBR_MAP_CAMERA_H_#pragma once