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
		glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, static_cast<void *>(0));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0); //ÉoÉCÉìÉhÇâèú

	};

	void Spring::Draw()
	{
		glBindVertexArray(vao_);
		glDrawArrays(GL_LINES, 0, size_);
	}
	


}