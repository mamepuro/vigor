#include "massPoint.h"

namespace game {
	massPoint::massPoint(int id, int vertexIndex, Block* block) :
		blockID(id),
		mass(1.0),
		vertexIndex(vertexIndex),
		block(block)
	{
		prev_position = (block->positions)[vertexIndex];
		prev_velocity = glm::vec3(0, 0, 0);
		velocity = glm::vec3(0, 0, 0);;
		position = (block->world_position)[vertexIndex];
	};
	void massPoint::AddSpring(game::massPoint* _another, springType springType)
	{
		glm::vec3 initial_position = (_another->position);
		glm::vec3 myInitialPosition = position;
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
			//エラー
			k = 4.0f;
		}
		game::Spring* spring = new Spring(k, this, _another, restLength, springType);
		spring->currentLength = restLength;
		springs.push_back(spring);
		_another->springs.push_back(spring);
		block->SetSpring(spring);
	}

	glm::vec3 massPoint::CalculateForce()
	{
		//重力は現時点では使わない
		glm::vec3 gravity = glm::vec3(0, 0, 0);
		glm::vec3 force = glm::vec3(0.0, 0.0, 0.0);

		for (int i = 0; i < springs.size(); i++)
		{
			force += springs[i]->GetForce(this);
		}

		return force + gravity;
	}

	void massPoint::Update(float delta)
	{
		glm::vec3 acc = CalculateForce() / mass;

		velocity = velocity + acc * delta * 0.2f;
		//std::cout << "velocity = " << glm::length(velocity) << std::endl;
		position = position + velocity * delta;
	}
}

