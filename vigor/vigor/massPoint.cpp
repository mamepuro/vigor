#include "massPoint.h"

namespace game {
	massPoint::massPoint(int id, int vertexIndex, Block* block):
		blockID(id),
		mass(1.0),
		vertexIndex(vertexIndex),
		block(block)
	{
		prev_position = (block->positions)[vertexIndex];
		prev_velocity = glm::vec3(0);
	};
	void massPoint::AddSpring(game::massPoint* _another, springType springType)
	{
		glm::vec3 initial_position = (_another->block->positions)[_another->vertexIndex];
		glm::vec3 myInitialPosition = (block->positions)[vertexIndex];
		float restLength = glm::length(initial_position - myInitialPosition);
		float k = 0;

		if (springType == springType::Edge)
		{
			k = 3.0f;
		}
		else if (springType == springType::Leg)
		{
			k = 2.0f;
		}
		else if (springType == springType::Union)
		{
			k = 1.0f;
		}
		else
		{
			//ƒGƒ‰[
			k = 4.0f;
		}
		game::Spring* spring = new Spring(k,this, _another, restLength, springType);
		spring->currentLength = restLength;
		springs.push_back(spring);
		block->SetSpring(spring);
	}
}

