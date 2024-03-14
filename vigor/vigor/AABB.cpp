#include "AABB.h"

	AABB::AABB(std::vector <glm::vec3> world_positions, int bid)
	{
		_bid = bid;
		SetMaxAndMinVerteices(world_positions);
	}

	void AABB::SetMaxAndMinVerteices(std::vector <glm::vec3> world_positions)
	{
		float max_x = -10000.f;
		float max_y = -10000.f;
		float max_z = -10000.f;
		float min_x = 10000.0f;
		float min_y = 10000.0f;
		float min_z = 10000.0f;
		for (auto&& world_position : world_positions)
		{
			if(max_x < world_position.x)
			{
				max_x = world_position.x;
			}
			if (min_x > world_position.x)
			{
				min_x = world_position.x;
			}
			if (max_y < world_position.y)
			{
				max_y = world_position.y;
			}
			if (min_y > world_position.y)
			{
				min_y = world_position.y;
			}
			if (max_z < world_position.z)
			{
				max_z = world_position.z;
			}
			if (min_z > world_position.z)
			{
				min_z = world_position.z;
			}
		}

		max_vertex = glm::vec3(max_x, max_y, max_z);
		min_vertex = glm::vec3(min_x, min_y, min_z);
	}
