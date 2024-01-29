#include "Spring.h"

namespace game {
	Spring::Spring(float _k, game::massPoint* _left, game::massPoint* _right, float _restLength, springType springType)
		:restLength(_restLength),
		left(_left),
		right(_right),
		k(_k),
		m_springType(springType)

	{
		vertices.push_back(left->prev_position);
		vertices.push_back(right->prev_position);
		size_ = vertices.size();
		glGenVertexArrays(1, &vao_);
		glBindVertexArray(vao_);


		glGenBuffers(1, &vertices_vbo_);
		glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo_);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
			&vertices[0], GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0); //バインドを解除

	};

	void Spring::Draw()
	{
		glBindVertexArray(vao_);
		glDrawArrays(GL_LINES, 0, size_);
	}

	glm::vec3 Spring::GetForce(massPoint* refMassPoint)
	{
		if (!(refMassPoint == left) &&
			!(refMassPoint == right))
		{
			std::cout << "Error：存在しないMassPointを参照して力を計算しました" << std::endl;
			return glm::vec3(0.0, 0.0, 0.0);
		}

		//距離の計算
		float distance = glm::length(left->position - right->position);
		//ばね定数等の考慮
		/*本当ならF = sigma_j k(1 - L / |r|) * r */
		float scaler = k * (distance - restLength) * 1.0f;  //0.1 = ダンピング定数
		//std::cout << "scaler = " << scaler << std::endl;
		glm::vec3 direction = glm::normalize(right->position - left->position);
		if (refMassPoint == left)
		{
			return scaler * direction;
		}
		else
		{
			//反対方向にする
			return -scaler * direction;
		}

	}



}