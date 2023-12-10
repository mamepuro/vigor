#ifndef OPENGL_PBR_MAP_MESH_ENTITY_H_
#define OPENGL_PBR_MAP_MESH_ENTITY_H_

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <memory>

#include "mesh.h"

namespace game {

    /**
     * @brief Mesh��Model�s���ێ�����N���X
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
        /// ���̋r�ɐڑ����Ă���MeshEntity�̎���
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
        /// ���b�V���G���e�B�e�B���c�ɐڑ�����B�Ȃ��A�����ʒu�͐ڑ��������������r�������ꂽ�ʒu�Ƃ���
        /// </summary>
        /// <param name="meshEntity">�G���e�B�e�B</param>
        void ConnectTo(game::MeshEntity &meshEntity, game::MeshEntity &me);
        /**
         * @brief �V�[����̈ʒu��Ԃ�
         * @return �V�[����̈ʒu
         */
        const glm::vec3 GetPosition() const;

        /**
         * @brief �V�[����̈ʒu��ݒ肷��
         * @param position �V�����ʒu
         *
         * �����ŕێ�����Model�s��̍Čv�Z���s���܂��B
         */
        void SetPosition(const glm::vec3 position);

        /**
         * @brief ����Entity�̉�]�̃I�C���[�p���擾����
         * @return ����Entity�̉�]�̃I�C���[�p
         *
         * �I�C���[�p��YXZ�̏��ł��B
         */
        const glm::vec3 GetRotation() const;

        /**
         * @brief ����Entity�̉�]�̃I�C���[�p��ݒ肷��
         * @param rotation �V������]�̃I�C���[�p
         *
         * �I�C���[�p��YXZ�̏��ł��B
         * �����ŕێ�����Model�s��̍Čv�Z���s���܂��B
         */
        void SetRotation(const glm::vec3 rotation);

        /**
         * @brief ����Entity�̃X�P�[�����擾����
         * @return ����Entity�̃X�P�[��
         */
        const glm::vec3 GetScale() const;

        /**
         * @brief ����Entity�̃X�P�[����ݒ肷��
         * @param scale �V�����X�P�[��
         *
         * �����ŕێ�����Model�s��̍Čv�Z���s���܂��B
         */
        void SetScale(const glm::vec3 scale);

        /**
         * @brief Model�s����擾����
         * @return Model�s��
         */
        const glm::mat4 GetModelMatrix() const;

        /**
         * @brief �R���X�g���N�^
         * @param mesh Mesh��shared_ptr
         * @param position Entity�̈ʒu
         * @param rotation Entity�̉�]�̃I�C���[�p
         * @param scale Entity�̊e���̃X�P�[��
         *
         * �I�C���[�p��YXZ�̏��ł��B
         */
        MeshEntity(std::shared_ptr<Mesh> mesh, const glm::vec3 position,
            const glm::vec3 rotation, const glm::vec3 scale, int r, int l);

    private:
        glm::vec3 position_;
        glm::vec3 rotation_;
        glm::vec3 scale_;
        glm::mat4 model_matrix_;

        /**
         * @brief Model�s����Čv�Z����
         */
        void RecaluculateModelMatrix();
    };

}  // namespace game

#endif  // OPENGL_PBR_MAP_MESH_ENTITY_H_