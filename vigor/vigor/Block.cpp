#include "Block.h"
#include "MeshEntity.h"


namespace game {
	Block::Block(std::shared_ptr<Mesh> mesh,
		const glm::vec3 position,
		const glm::vec3 rotation,
		const glm::vec3 scale,
		int _ID,
		int _union_ID,
		std::vector<glm::vec3> _positions,
		int _legLeftInsertBlockID,
		int _legRightInsertBlockID,
		int _pocketLeftInsertBlockID,
		int _pocketRightInsertBlockID) : game::MeshEntity(mesh, position, rotation, scale,1,5),
		ID(_ID),
		union_ID(_union_ID),
		positions(_positions),
		legLeftInsertBlockID(_legLeftInsertBlockID),
		legRightInsertBlockID(_legRightInsertBlockID),
		pocketLeftInsertBlockID(_pocketLeftInsertBlockID),
		pocketRightInsertBlockID(_pocketRightInsertBlockID)
	{
		for (int points = 0; points < _positions.size(); points++)
		{
			game::massPoint* massPoint = new game::massPoint(_ID, points, this);
			massPoints.push_back(massPoint);
		}
		springType sp = springType::Edge;
		massPoints[0]->AddSpring(massPoints[1], sp);
		massPoints[1]->AddSpring(massPoints[0], sp);
		massPoints[0]->AddSpring(massPoints[2], sp);
		massPoints[2]->AddSpring(massPoints[0], sp);
		massPoints[1]->AddSpring(massPoints[2], sp);
		massPoints[2]->AddSpring(massPoints[1], sp);
		massPoints[3]->AddSpring(massPoints[5], sp);
		massPoints[5]->AddSpring(massPoints[3], sp);
		massPoints[3]->AddSpring(massPoints[4], sp);
		massPoints[4]->AddSpring(massPoints[3], sp);
		massPoints[4]->AddSpring(massPoints[5], sp);
		massPoints[5]->AddSpring(massPoints[4], sp);
		//脚の間にバネを貼る
	    //massPoints[1]->AddSpring(massPoints[5], springType::Leg);
		//massPoints[5]->AddSpring(massPoints[1], springType::Leg);
	};

	void Block::SetSpring(game::Spring* _spring) {
		springs.push_back(_spring);
	}
	
	void Block::Simulate(float delta) {
		//減衰定数
		float d = 0.2;
		glm::vec3 force = glm::vec3(0);
		glm::vec3 velocity = glm::vec3(0);
		glm::vec3 position = glm::vec3(0);
		//ブロック内の各質点についてバネ計算を行う
		auto mesh = this->mesh_;
		auto verteices = mesh->GetVertices();
		for (auto massPoint : massPoints)
		{
			for (auto spring : massPoint->springs)
			{
				auto target_massPoint = spring->right;
				auto target_vertex = (target_massPoint->prev_position);
				auto Lr = spring->restLength / glm::length(target_vertex - massPoint->prev_position);
				force += (1 - Lr) * spring->k * (target_vertex - massPoint->prev_position);
			}
			velocity = massPoint->prev_velocity + d * force * delta;
			position = massPoint->prev_position + massPoint->prev_velocity * delta;
			massPoint->prev_velocity = velocity;
			massPoint->prev_position = position;
			verteices[massPoint->vertexIndex] = position;
		}
		mesh_->SetVertices(verteices);
	}

	void Block::Connect(Block* _target)
	{
		auto target_mesh = _target->mesh_;
		auto target_vertex = target_mesh->GetVertices();
		auto myVertex = mesh_->GetVertices();
		auto r_target_pos = r_pocketToLeg * (1 - tate_r) + myVertex[pocket_right_ind];
		auto l_target_pos = l_pocketToLeg * (1 - tate_r) + myVertex[pocket_left_ind];
		auto r_tToLeg = myVertex[leg_right_ind] - r_target_pos;
		auto l_tToLeg = myVertex[leg_left_ind] - l_target_pos;
		auto r_tToY = r_target_pos + glm::vec3(0, 1, 0) - r_target_pos;
		auto l_tToY = l_target_pos + glm::vec3(0, 1, 0) - l_target_pos;
		auto r_oh = glm::dot(r_tToLeg, r_tToY) / (glm::length(r_tToY) * glm::length(r_tToY)) * r_tToY;
		auto l_oh = glm::dot(l_tToLeg, l_tToY) / (glm::length(l_tToY) * glm::length(l_tToY)) * l_tToY;
		myVertex[leg_right_ind] = r_target_pos + r_oh;
		myVertex[leg_left_ind] = l_target_pos + l_oh;
		r_pocketToLeg = myVertex[leg_right_ind] - myVertex[pocket_right_ind];
		l_pocketToLeg = myVertex[leg_left_ind] - myVertex[pocket_left_ind];
		int count = 0;
		for (auto var : target_vertex)
		{
			//右側の計算
			if (count < 3)
			{
				target_vertex[count] = myVertex[count] + r_pocketToLeg * (tate_r);
			}
			//左側の計算
			else
			{
				target_vertex[count] = myVertex[count] + l_pocketToLeg * (tate_r);
			}
			count++;
		}

		mesh_->SetVertices(myVertex);
		for(auto massPoint : massPoints)
		{
			massPoint->prev_position = myVertex[massPoint->vertexIndex];
		}
		for (auto massPoint : _target->massPoints)
		{
			massPoint->prev_position = target_vertex[massPoint->vertexIndex];
		}
		_target->mesh_->SetVertices(target_vertex);
		springType sp = springType::Union;
		massPoints[0]->AddSpring(_target->massPoints[0],sp);
		massPoints[1]->AddSpring(_target->massPoints[1], sp);
		massPoints[2]->AddSpring(_target->massPoints[2], sp);
		massPoints[3]->AddSpring(_target->massPoints[3], sp);
		massPoints[4]->AddSpring(_target->massPoints[4], sp);
		massPoints[5]->AddSpring(_target->massPoints[5], sp);
		_target->massPoints[0]->AddSpring(massPoints[0], sp);
		_target->massPoints[1]->AddSpring(massPoints[1], sp);
		_target->massPoints[2]->AddSpring(massPoints[2], sp);
		_target->massPoints[3]->AddSpring(massPoints[3], sp);
		_target->massPoints[4]->AddSpring(massPoints[4], sp);
		_target->massPoints[5]->AddSpring(massPoints[5], sp);
		//auto restLength = glm::length(target_vertex[leg_right_ind] - myVertex[leg_left_ind]);
		//r_restLengths.push_back(restLength);
		//l_restLengths.push_back(restLength);
		//connected.r_restLengths.push_back(restLength);
		//connected.l_restLengths.push_back(restLength);
		//r_connect_ind.push_back(leg_left_ind);
		//l_connect_ind.push_back(leg_right_ind);
		//connected.r_connect_ind.push_back(leg_left_ind);
		//connected.l_connect_ind.push_back(leg_right_ind);
		//r_connect.push_back(connected);
		//l_connect.push_back(connected);
		//connected.r_connect.push_back(me);
		//connected.l_connect.push_back(me);
		//r_position_prev = myVertex[leg_right_ind];
		//l_position_prev = myVertex[leg_left_ind];
		//connected.r_position_prev = target_vertex[leg_right_ind];
		//connected.l_position_prev = target_vertex[leg_left_ind];

		//auto restLength = glm::length(target_vertex[leg_left_ind] - myVertex[leg_left_ind]);
		//r_restLengths.push_back(restLength);
		//l_restLengths.push_back(restLength);
		//connected.r_restLengths.push_back(restLength);
		//connected.l_restLengths.push_back(restLength);
		//r_connect_ind.push_back(leg_right_ind);
		//l_connect_ind.push_back(leg_left_ind);
		//connected.r_connect_ind.push_back(leg_right_ind);
		//connected.l_connect_ind.push_back(leg_left_ind);
		//r_connect.push_back(connected);
		//l_connect.push_back(connected);
		//connected.r_connect.push_back(me);
		//connected.l_connect.push_back(me);
		//r_position_prev = myVertex[leg_right_ind];
		//l_position_prev = myVertex[leg_left_ind];
		//connected.r_position_prev = target_vertex[leg_right_ind];
		//connected.l_position_prev = target_vertex[leg_left_ind];
		//return target_vertex;
	};

	void Block::TestBend() {
		auto myVertex = mesh_->GetVertices();
		auto length = glm::length(myVertex[pocket_right_ind] - myVertex[leg_right_ind]);
		auto r_target_pos = r_pocketToLeg * (1 - tate_r) + myVertex[pocket_right_ind];
		auto l_target_pos = l_pocketToLeg * (1 - tate_r) + myVertex[pocket_left_ind];
		auto r_tToLeg = myVertex[leg_right_ind] - r_target_pos;
		auto l_tToLeg = myVertex[leg_left_ind] - l_target_pos;
		auto r_tToY = r_target_pos + glm::vec3(0, 1, 0) - r_target_pos;
		auto l_tToY = l_target_pos + glm::vec3(0, 1, 0) - l_target_pos;
		auto r_oh = glm::dot(r_tToLeg, r_tToY) / (glm::length(r_tToY) * glm::length(r_tToY)) * r_tToY;
		auto l_oh = glm::dot(l_tToLeg, l_tToY) / (glm::length(l_tToY) * glm::length(l_tToY)) * l_tToY;
		//myVertex[leg_right_ind] = glm::normalize(r_target_pos + r_oh - myVertex[pocket_right_ind]) * length;
		//myVertex[leg_left_ind] = glm::normalize(l_target_pos + l_oh - myVertex[pocket_left_ind]) * length;
		myVertex[leg_right_ind] = r_target_pos + r_oh * length;
		myVertex[leg_left_ind] = l_target_pos + l_oh  * length;
		r_pocketToLeg = myVertex[leg_right_ind] - myVertex[pocket_right_ind];
		l_pocketToLeg = myVertex[leg_left_ind] - myVertex[pocket_left_ind];
		mesh_->SetVertices(myVertex);
		for (auto massPoint : massPoints)
		{
			massPoint->prev_position = myVertex[massPoint->vertexIndex];
		}
	}

}