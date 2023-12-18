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
			game::massPoint massPoint = game::massPoint(_ID, points, this);
		}
	};

	void Block::SetSpring(game::Spring _spring) {
		springs.push_back(&_spring);
	}
	
}