#include "Spring.h"

namespace game {
	Spring::Spring(float _k, game::massPoint* _left, game::massPoint* _right, float _restLength, springType springType)
		:restLength(restLength),
		left(_left),
		right(_right),
		k(_k),
		m_springType(springType)
	{};


}