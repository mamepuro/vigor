#pragma once
#include "massPoint.h"
#include "springType.h"

namespace game{
	class massPoint;
	class Spring
	{
	public:
		//バネ端点の質点
		//注意 C2079のコンパイルエラー回避のため、他クラスのオブジェクトをメンバとする場合はオブジェクトのポインタとする
		game::massPoint *left;
		game::massPoint *right;
		float currentLength;
		springType m_springType;
		//初期の長さ
		float restLength;
		//バネ定数
		float k;
		Spring(float _k, game::massPoint* _left, game::massPoint* _right, float restLength, springType springType);
	private:

	};

}

