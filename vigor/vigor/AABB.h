#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <vector>

/// <summary>
/// Axis-Aligned Bounding Box 軸並行境界ボックス
/// </summary>
class AABB
{
	public:
		AABB(std::vector<glm::vec3> world_position, int bid);
		void SetMaxAndMinVerteices(std::vector<glm::vec3> world_positions);
		glm::vec3 max_vertex;
		glm::vec3 min_vertex;
	private:
		int _bid;
};

