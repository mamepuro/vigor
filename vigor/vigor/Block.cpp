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
		int _pocketRightInsertBlockID) : game::MeshEntity(mesh, position, rotation, scale, 1, 5),
		union_ID(_union_ID),
		positions(_positions),
		local_position(_positions),
		legLeftInsertBlockID(_legLeftInsertBlockID),
		legRightInsertBlockID(_legRightInsertBlockID),
		pocketLeftInsertBlockID(_pocketLeftInsertBlockID),
		pocketRightInsertBlockID(_pocketRightInsertBlockID)
	{
		ID = mID;
		mID++;
		world_position = local_position;
		UpdateWorldPosition();
		for (int points = 0; points < _positions.size(); points++)
		{
			game::massPoint* massPoint = new game::massPoint(ID, points, this);
			massPoints.push_back(massPoint);
		}
		springType sp = springType::Edge;


		//massPoints[0]->AddSpring(massPoints[1], sp);
		////massPoints[1]->AddSpring(massPoints[0], sp);
		//massPoints[0]->AddSpring(massPoints[2], sp);
		////massPoints[2]->AddSpring(massPoints[0], sp);
		//massPoints[1]->AddSpring(massPoints[2], sp);
		////massPoints[2]->AddSpring(massPoints[1], sp);
		//massPoints[3]->AddSpring(massPoints[5], sp);
		////massPoints[5]->AddSpring(massPoints[3], sp);
		//massPoints[3]->AddSpring(massPoints[4], sp);
		////massPoints[4]->AddSpring(massPoints[3], sp);
		//massPoints[4]->AddSpring(massPoints[5], sp);
		//massPoints[5]->AddSpring(massPoints[4], sp);
		//脚の間にバネを貼る
		massPoints[1]->AddSpring(massPoints[5], springType::Leg);
		//massPoints[5]->AddSpring(massPoints[1], springType::Leg);
	};

	void Block::UpdateWorldPosition()
	{

		for (int i = 0; i < local_position.size(); i++)
		{
			//同次座標系に変換(4つめの要素(w)は1とする)
			// 注:w=1 でないと平行移動を考慮した計算にならない
			//TODO: テストしておくこと
			glm::vec4 vec4_local = glm::vec4(local_position[i], 1);
			vec4_local = model_matrix_ * vec4_local;
			world_position[i] = glm::vec3(vec4_local);
			if (local_position.size() == massPoints.size())
			{
				//質点の座標を更新する
				massPoints[i]->world_position = world_position[i];
			}
		}
		UpdateLocalPosition();
	}

	void Block::UpdateLocalPosition()
	{
		//同次座標系に変換(4つめの要素(w)は1とする)
		// 注:w=1 でないと平行移動を考慮した計算にならない
		//TODO: テストしておくこと
		// OK
		for (int i = 0; i < world_position.size(); i++)
		{
			glm::vec4 vec4_world = glm::vec4(world_position[i], 1);
			local_position[i] = glm::inverse(model_matrix_) * vec4_world;
			if (local_position.size() == massPoints.size())
			{
				//質点の座標を更新する
				massPoints[i]->world_position = world_position[i];
			}
		}
	}

	void Block::CheckCollide() {
		//T1 = 自分の面
		//T2 = 相手の面
		//v1_0 = 自分の面の頂点0
		glm::vec3 v1_0, v1_1, v1_2, v2_0, v2_1, v2_2;
		glm::vec3 n1, n2;
		float d1, d2, d1_0, d1_1, d1_2, d2_0, d2_1, d2_2;
		//最初に右の面から調査する
		v1_0 = world_position[0];
		v1_1 = world_position[1];
		v1_2 = world_position[2];
		n1 = glm::cross(v1_2 - v1_0, v1_1 - v1_0);
		d1 = glm::dot(-n1, v1_0);
		for (int i = 0; i < r_connect.size(); i++)
		{
			//相手は左の面を見る
			v2_0 = r_connect[i]->world_position[3];
			v2_1 = r_connect[i]->world_position[4];
			v2_2 = r_connect[i]->world_position[5];
			n2 = glm::cross(v2_2 - v2_0, v2_1 - v2_0);
			d2 = glm::dot(-n2, v2_0);

			//ここから交差判定
			d1_0 = glm::dot(n2, v1_0) + d2;
			d1_1 = glm::dot(n2, v1_1) + d2;
			d1_2 = glm::dot(n2, v1_2) + d2;
			d2_0 = glm::dot(n1, v2_0) + d1;
			d2_1 = glm::dot(n1, v2_1) + d1;
			d2_2 = glm::dot(n1, v2_2) + d1;

			//全てのdの符号が一致する場合は衝突していないので以降の計算はしない
			if ((d1_0 > 0 && d1_1 > 0 && d1_2 > 0)
				|| (d1_0 < 0 && d1_1 < 0 && d1_2 < 0))
			{
				continue;
			}

			//法線を正規化する
			n1 = glm::normalize(n1);
			n2 = glm::normalize(n2);

			float distance1, distance2;
			glm::vec3 p1_1, p1_2, p2_1, p2_2;
			//v1_0とv1_1が同じ側にあるとき
			if (((d1_0 > 0 && d1_1 > 0)
				|| (d1_0 < 0 && d1_1 < 0)))
			{
				distance1 = glm::dot(v2_0 - v1_0, n2);
				distance2 = glm::dot(v2_0 - v1_2, n2);
				p1_1 = v1_2 + (v1_0 - v1_2) * (distance2 / (distance1 + distance2));
				distance1 = glm::dot(v2_0 - v1_1, n2);
				p1_2 = v1_2 + (v1_1 - v1_2) * (distance2 / (distance1 + distance2));
			}
			//v1_1とv1_2が同じ側にあるとき
			else if ((d1_1 > 0 && d1_2 > 0)
				|| (d1_1 < 0 && d1_2 < 0))
			{
				distance1 = glm::dot(v2_0 - v1_1, n2);
				distance2 = glm::dot(v2_0 - v1_0, n2);
				p1_1 = v1_0 + (v1_1 - v1_0) * (distance2 / (distance1 + distance2));
				distance1 = glm::dot(v2_0 - v1_2, n2);
				p1_2 = v1_0 + (v1_2 - v1_0) * (distance2 / (distance1 + distance2));
			}
			else
			{
				distance1 = glm::dot(v2_0 - v1_0, n2);
				distance2 = glm::dot(v2_0 - v1_1, n2);
				p1_1 = v1_1 + (v1_0 - v1_1) * (distance2 / (distance1 + distance2));
				distance1 = glm::dot(v2_0 - v1_2, n2);
				p1_2 = v1_1 + (v1_2 - v1_1) * (distance2 / (distance1 + distance2));
			}

			//T2側でも同様の計算をする
			if (((d2_0 > 0 && d2_1 > 0)
				|| (d2_0 < 0 && d2_1 < 0)))
			{
				distance1 = glm::dot(v1_0 - v2_0, n1);
				distance2 = glm::dot(v1_0 - v2_2, n1);
				p2_1 = v2_2 + (v2_0 - v2_2) * (distance2 / (distance1 + distance2));
				distance1 = glm::dot(v1_0 - v2_1, n1);
				p2_2 = v2_2 + (v2_1 - v2_2) * (distance2 / (distance1 + distance2));
			}
			//v1_1とv1_2が同じ側にあるとき
			else if ((d2_1 > 0 && d2_2 > 0)
				|| (d2_1 < 0 && d2_2 < 0))
			{
				distance1 = glm::dot(v1_0 - v2_1, n1);
				distance2 = glm::dot(v1_0 - v2_0, n1);
				p2_1 = v2_0 + (v2_1 - v2_0) * (distance2 / (distance1 + distance2));
				distance1 = glm::dot(v1_0 - v2_2, n1);
				p2_2 = v2_0 + (v2_2 - v2_0) * (distance2 / (distance1 + distance2));
			}
			else
			{
				distance1 = glm::dot(v1_0 - v2_0, n1);
				distance2 = glm::dot(v1_0 - v2_1, n1);
				p2_1 = v2_1 + (v2_0 - v2_1) * (distance2 / (distance1 + distance2));
				distance1 = glm::dot(v1_0 - v2_2, n1);
				p2_2 = v2_1 + (v2_2 - v2_1) * (distance2 / (distance1 + distance2));
			}
			glm::vec3 test1 = p2_1 - p2_2;
			glm::vec3 test2 = p1_1 - p1_2;
			float x = glm::dot(test1, test2);
			float k = 0;
			float dist = glm::distance(v1_1, v2_2);
			float l = glm::length(v1_1 - v2_2);
			world_position[1].x -= dist;
			r_connect[i]->world_position[5].x
				+= dist;
			UpdateLocalPosition();
			r_connect[i]->UpdateLocalPosition();
			mesh_->SetVertices(local_position);
			r_connect[i]->mesh_->SetVertices(r_connect[i]->world_position);
		}
	}

	void Block::SetSpring(game::Spring* _spring) {
		springs.push_back(_spring);
	}

	void Block::Simulate(float delta) {
		UpdateWorldPosition();
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
			massPoint->Update(0.01f);
			world_position[massPoint->vertexIndex] = massPoint->position;
			//verteices[massPoint->vertexIndex] = massPoint->position;
			/*for (auto spring : massPoint->springs)
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
			verteices[massPoint->vertexIndex] = position;*/

		}
		//world_position = verteices;
		UpdateLocalPosition();
		mesh_->SetVertices(local_position);
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
		for (auto massPoint : massPoints)
		{
			massPoint->prev_position = myVertex[massPoint->vertexIndex];
		}
		for (auto massPoint : _target->massPoints)
		{
			massPoint->prev_position = target_vertex[massPoint->vertexIndex];
		}
		_target->mesh_->SetVertices(target_vertex);
		springType sp = springType::Union;
		//massPoints[0]->AddSpring(_target->massPoints[0], sp);
		//massPoints[1]->AddSpring(_target->massPoints[1], sp);
		//massPoints[2]->AddSpring(_target->massPoints[2], sp);
		//massPoints[3]->AddSpring(_target->massPoints[3], sp);
		//massPoints[4]->AddSpring(_target->massPoints[4], sp);
		//massPoints[5]->AddSpring(_target->massPoints[5], sp);
		//_target->massPoints[0]->AddSpring(massPoints[0], sp);
		//_target->massPoints[1]->AddSpring(massPoints[1], sp);
		//_target->massPoints[2]->AddSpring(massPoints[2], sp);
		//_target->massPoints[3]->AddSpring(massPoints[3], sp);
		//_target->massPoints[4]->AddSpring(massPoints[4], sp);
		//_target->massPoints[5]->AddSpring(massPoints[5], sp);
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

	void Block::ConnectNext(Block* _target)
	{
		auto target_mesh = _target->mesh_;
		auto target_vertex = target_mesh->GetVertices();
		auto myVertex = mesh_->GetVertices();
		int count = 0;
		auto move = glm::vec3(0);
		move.x = move.x + myVertex[1].x * 2;
		for (auto var : target_vertex)
		{
			//右側の計算
			if (count < 3)
			{
				target_vertex[count] = myVertex[count] + move;
			}
			//左側の計算
			else
			{
				target_vertex[count] = myVertex[count] + move;
			}
			count++;
		}

		mesh_->SetVertices(myVertex);
		for (auto massPoint : massPoints)
		{
			massPoint->prev_position = myVertex[massPoint->vertexIndex];
		}
		for (auto massPoint : _target->massPoints)
		{
			massPoint->prev_position = target_vertex[massPoint->vertexIndex];
		}
		_target->mesh_->SetVertices(target_vertex);
		springType sp = springType::Union;
		massPoints[0]->AddSpring(_target->massPoints[0], sp);
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
	};

	void Block::TestBend() {
		auto myVertex = world_position;
		//auto length = glm::length(myVertex[pocket_right_ind] - myVertex[leg_right_ind]);
		//auto r_target_pos = r_pocketToLeg * (1 - tate_r) + myVertex[pocket_right_ind];
		//auto l_target_pos = l_pocketToLeg * (1 - tate_r) + myVertex[pocket_left_ind];
		//auto r_tToLeg = myVertex[leg_right_ind] - r_target_pos;
		//auto l_tToLeg = myVertex[leg_left_ind] - l_target_pos;
		//auto r_tToY = r_target_pos + glm::vec3(0, 1, 0) - r_target_pos;
		//auto l_tToY = l_target_pos + glm::vec3(0, 1, 0) - l_target_pos;
		//auto r_oh = glm::dot(r_tToLeg, r_tToY) / (glm::length(r_tToY) * glm::length(r_tToY)) * r_tToY;
		//auto l_oh = glm::dot(l_tToLeg, l_tToY) / (glm::length(l_tToY) * glm::length(l_tToY)) * l_tToY;
		////myVertex[leg_right_ind] = glm::normalize(r_target_pos + r_oh - myVertex[pocket_right_ind]) * length;
		////myVertex[leg_left_ind] = glm::normalize(l_target_pos + l_oh - myVertex[pocket_left_ind]) * length;
		//myVertex[leg_right_ind] = r_target_pos + r_oh * length;
		//myVertex[leg_left_ind] = l_target_pos + l_oh * length;
		//r_pocketToLeg = myVertex[leg_right_ind] - myVertex[pocket_right_ind];
		//l_pocketToLeg = myVertex[leg_left_ind] - myVertex[pocket_left_ind];
		myVertex[leg_right_ind].x += 0.1;
		myVertex[leg_left_ind].x -= 0.1;
		mesh_->SetVertices(myVertex);
		for (auto massPoint : massPoints)
		{
			massPoint->position = myVertex[massPoint->vertexIndex];
		}
	}

}