#include "MeshEntity.h"

namespace game {

    const glm::vec3 MeshEntity::GetPosition() const { return position_; }

    void MeshEntity::SetPosition(const glm::vec3 position) {
        position_ = position;
        RecaluculateModelMatrix();
    }

    const glm::vec3 MeshEntity::GetRotation() const { return rotation_; }

    void MeshEntity::SetRotation(const glm::vec3 rotation) {
        rotation_ = rotation;
        RecaluculateModelMatrix();
    }

    const glm::vec3 MeshEntity::GetScale() const { return scale_; }

    void MeshEntity::SetScale(const glm::vec3 scale) {
        scale_ = scale;
        RecaluculateModelMatrix();
    }

    const glm::mat4 MeshEntity::GetModelMatrix() const { return model_matrix_; }

    MeshEntity::MeshEntity(std::shared_ptr<Mesh> mesh,
        const glm::vec3 position, const glm::vec3 rotation,
        const glm::vec3 scale, int r, int l)
        : mesh_(mesh),
        position_(position),
        rotation_(rotation),
        scale_(scale),
        model_matrix_(),
        leg_right_ind(r),
        leg_left_ind(l) {
        RecaluculateModelMatrix();
        auto vertices = mesh_->vertices_;
        restLength = glm::length( (vertices[r] - vertices[l]));
        r_velocity_prev = glm::vec3(0);
        l_velocity_prev = glm::vec3(0);
        r_position_prev = vertices[r];
        l_position_prev = vertices[l];
        r_connect_ind.push_back(l);
        l_connect_ind.push_back(r);
        r_restLengths.push_back(restLength);
        l_restLengths.push_back(restLength);
    }

    void MeshEntity::RecaluculateModelMatrix() {
        auto scale = glm::scale(glm::mat4(1), scale_);
        auto rotation = glm::eulerAngleYXZ(rotation_.y, rotation_.x, rotation_.z);
        auto translate = glm::translate(glm::mat4(1), position_);
        model_matrix_ = translate * rotation * scale;
    }

    /// <summary>
    /// バネ質点系モデルによるシミュレーションを行う
    /// </summary>
    /// <param name="delta"></param>
    void MeshEntity::Simulate(float delta) {
        glm::vec3 r_force = glm::vec3(0);
        glm::vec3 l_force = glm::vec3(0);
        auto vertices = mesh_->GetVertices();
        int count = 0;
        for (auto var :r_connect)
        {
            auto target_vertices = (var.mesh_->GetVertices());
            auto target_vertex = target_vertices[r_connect_ind[count]];
            auto Lr = r_restLengths[count] / glm::length(vertices[leg_right_ind] - target_vertex);
            r_force += (1 - Lr) * (vertices[leg_right_ind] - target_vertex);
            count++;
        }
        count = 0;
        for (auto var : l_connect)
        {
            auto target_vertices = (var.mesh_->GetVertices());
            auto target_vertex = target_vertices[l_connect_ind[count]];
            auto Lr = l_restLengths[count] / glm::length(vertices[leg_left_ind] - target_vertex);
            l_force += (1 - Lr) * (vertices[leg_left_ind] - target_vertex);
            count++;
        }
        float d = 0.5;
        glm::vec3 r_velocity = r_velocity_prev + d * r_force * delta;
        glm::vec3 r_pos = r_position_prev + r_velocity_prev * delta;
        glm::vec3 l_velocity = l_velocity_prev + d * l_force * delta;
        glm::vec3 l_pos = l_position_prev + l_velocity_prev * delta;
        r_velocity_prev = r_velocity;
        r_position_prev = r_pos;
        l_velocity_prev = l_velocity;
        l_position_prev = l_pos;
        vertices[leg_right_ind] = r_pos;
        vertices[leg_left_ind] = l_pos;
        mesh_->SetVertices(vertices);
    }

    void MeshEntity::ConnectTo(game::MeshEntity &connected)
    {
        auto target_mesh = connected.mesh_;
        auto target_vertex = target_mesh->GetVertices();
        auto myVertex = mesh_->GetVertices();
        int count = 0;
        for (auto var : target_vertex)
        {
            target_vertex[count] = myVertex[count] + glm::vec3(0, 0, 5);
            count++;
        }

        connected.mesh_->SetVertices(target_vertex);
        //return target_vertex;
    }



}  // namespace game