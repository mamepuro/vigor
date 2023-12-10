#ifndef OPENGL_PBR_MAP_MESH_ENTITY_H_
#define OPENGL_PBR_MAP_MESH_ENTITY_H_

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <memory>

#include "mesh.h"

namespace game {

    /**
     * @brief MeshとModel行列を保持するクラス
     */

    class MeshEntity {
    public:
        std::shared_ptr<Mesh> mesh_;
        int leg_right_ind;
        int leg_left_ind;
        glm::vec3 r_velocity_prev;
        glm::vec3 l_velocity_prev;
        glm::vec3 r_position_prev;
        glm::vec3 l_position_prev;
        float restLength;
        std::vector<float> r_restLengths;
        std::vector<float> l_restLengths;
        /// <summary>
        /// 左の脚に接続しているMeshEntityの実態
        /// </summary>
        std::vector<MeshEntity> r_connect;
        std::vector<int> r_connect_ind;
        std::vector<MeshEntity> l_connect;
        std::vector<int> l_connect_ind;
        const float tate_r = 0.6;
        const int pocket_right_ind = 0;
        const int pocket_left_ind = 3;
        glm::vec3 r_pocketToLeg;
        glm::vec3 l_pocketToLeg;
        void Simulate(float delta);
        /// <summary>
        /// メッシュエンティティを縦に接続する。なお、初期位置は接続元から微小距離rだけ離れた位置とする
        /// </summary>
        /// <param name="meshEntity">エンティティ</param>
        void ConnectTo(game::MeshEntity &meshEntity, game::MeshEntity &me);
        /**
         * @brief シーン上の位置を返す
         * @return シーン上の位置
         */
        const glm::vec3 GetPosition() const;

        /**
         * @brief シーン上の位置を設定する
         * @param position 新しい位置
         *
         * 内部で保持するModel行列の再計算が行われます。
         */
        void SetPosition(const glm::vec3 position);

        /**
         * @brief このEntityの回転のオイラー角を取得する
         * @return このEntityの回転のオイラー角
         *
         * オイラー角はYXZの順です。
         */
        const glm::vec3 GetRotation() const;

        /**
         * @brief このEntityの回転のオイラー角を設定する
         * @param rotation 新しい回転のオイラー角
         *
         * オイラー角はYXZの順です。
         * 内部で保持するModel行列の再計算が行われます。
         */
        void SetRotation(const glm::vec3 rotation);

        /**
         * @brief このEntityのスケールを取得する
         * @return このEntityのスケール
         */
        const glm::vec3 GetScale() const;

        /**
         * @brief このEntityのスケールを設定する
         * @param scale 新しいスケール
         *
         * 内部で保持するModel行列の再計算が行われます。
         */
        void SetScale(const glm::vec3 scale);

        /**
         * @brief Model行列を取得する
         * @return Model行列
         */
        const glm::mat4 GetModelMatrix() const;

        /**
         * @brief コンストラクタ
         * @param mesh Meshのshared_ptr
         * @param position Entityの位置
         * @param rotation Entityの回転のオイラー角
         * @param scale Entityの各軸のスケール
         *
         * オイラー角はYXZの順です。
         */
        MeshEntity(std::shared_ptr<Mesh> mesh, const glm::vec3 position,
            const glm::vec3 rotation, const glm::vec3 scale, int r, int l);

    private:
        glm::vec3 position_;
        glm::vec3 rotation_;
        glm::vec3 scale_;
        glm::mat4 model_matrix_;

        /**
         * @brief Model行列を再計算する
         */
        void RecaluculateModelMatrix();
    };

}  // namespace game

#endif  // OPENGL_PBR_MAP_MESH_ENTITY_H_