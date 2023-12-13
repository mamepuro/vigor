#pragma once
#include "massPoint.h"
namespace game{
	class massPoint;
	class Spring
	{
	public:
		//バネ端点の質点
		//注意 C2079のコンパイルエラー回避のため、他クラスのオブジェクトをメンバとする場合はオブジェクトのポインタとする
		game::massPoint *left;
		game::massPoint *right;
		Spring(float _k, game::massPoint _left, game::massPoint _right, float restLength);
	private:
		//バネ定数
		float k;
		float restLength;
	};

}

