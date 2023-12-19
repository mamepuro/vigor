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
		/// 自身が所属するブロックのID
		/// </summary>
		int blockID;
		/// <summary>
		/// 質量
		/// </summary>
		float mass;
		/// <summary>
		/// この質点がセットされているブロックの頂点のインデックス
		/// </summary>
		int vertexIndex;
		glm::vec3 prev_position;
		glm::vec3 prev_velocity;
		/// <summary>
		/// この質点を持っているブロックへの参照
		/// </summary>
		Block *block;
		/// <summary>
		/// この質点に接続しているバネのコレクション
		/// </summary>
		std::vector<game::Spring*> springs;
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="_blockID"></param>
		/// <param name="vertexIndex"></param>
		/// <param name="_block"></param>

		massPoint(int _blockID, int vertexIndex, Block* _block);
		void AddSpring(game::massPoint* _another, springType springType);
	private:
	};
}


