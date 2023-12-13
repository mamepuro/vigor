#pragma once
#include"Block.h"
#include<vector>

namespace game {
	class Block;
	class massPoint
	{
		/// <summary>
		/// 自身が所属するブロックのID
		/// </summary>
		const int bolckID;
		/// <summary>
		/// 質量
		/// </summary>
		const float mass;
		/// <summary>
		/// この質点がセットされているブロックの頂点のインデックス
		/// </summary>
		const int vertexIndex;
		/// <summary>
		/// この質点を持っているブロックへの参照
		/// </summary>
		Block *block;
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="_blockID"></param>
		/// <param name="vertexIndex"></param>
		/// <param name="_block"></param>
		massPoint(int _blockID, int vertexIndex, Block _block);
	};
}


