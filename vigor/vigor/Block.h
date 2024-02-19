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

		/*脚の番号 1, 5 ポケットの番号0,3*/
		//左は5,3 右は1,0とする

		int ID;
		int union_ID;
		std::vector<glm::vec3> positions;
		int legLeftInsertBlockID;
		int legRightInsertBlockID;
		int pocketLeftInsertBlockID;
		int pocketRightInsertBlockID;
		/// <summary>
		/// 右側のブロックの面と衝突判定する面(現在は左の面と衝突判定する)
		/// </summary>
		std::vector<Block*> r_connect;
		/// <summary>
		/// 左側の面と衝突判定する面
		/// </summary>
		std::vector<Block*> l_connect;
		/// <summary>
		/// ブロックが持つ質点のコレクション
		/// 質点はブロックの全ての頂点に設置され、このコレクションには頂点順に質点が格納される
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
		/// 横向きに接続を行う
		/// </summary>
		void ConnectNext(Block* _target);
		void TestBend();

		/// <summary>
		/// ブロックのワールド座標を更新する
		/// </summary>
		void UpdateWorldPosition();
		/// <summary>
		/// ブロックのローカル座標を更新する
		/// </summary>
		void UpdateLocalPosition();
		/// <summary>
		/// ブロックの面同士の交差を判定する
		/// </summary>
		void CheckCollide();
		/// <summary>
		/// ブロックモデルの各頂点のワールド座標
		/// </summary>
		std::vector<glm::vec3> world_position;
		std::vector<glm::vec3> local_position;
	private:
		/// <summary>
		/// ブロックモデルの各頂点ローカル座標(モデル座標)
		/// </summary>

	};
}


#endif  // OPENGL_PBR_MAP_CAMERA_H_#pragma once