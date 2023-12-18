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
	class Block : game::MeshEntity
	{
	public:
		const int ID;
		int union_ID;
		std::vector<glm::vec3> positions;
		int legLeftInsertBlockID;
		int legRightInsertBlockID;
		int pocketLeftInsertBlockID;
		int pocketRightInsertBlockID;
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
		void SetSpring(game::Spring spring);
	private:
	};
}


#endif  // OPENGL_PBR_MAP_CAMERA_H_#pragma once