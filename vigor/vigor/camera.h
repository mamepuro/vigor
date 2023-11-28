#ifndef OPENGL_PBR_MAP_CAMERA_H_
#define OPENGL_PBR_MAP_CAMERA_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace game {

    /**
     * @brief �J������\������N���X
     */
    class Camera {
    public:
        /**
         * @brief �J�����̈ʒu���擾����
         * @return �J�����̈ʒu
         */
        const glm::vec3 GetPosition() const;

        /**
         * @brief �J�����̈ʒu��ݒ肷��
         * @param position �V�����ʒu
         *
         * �����ŕێ�����View�s��̍Čv�Z���s���܂��B
         */
        void SetPosition(const glm::vec3 position);

        /**
         * @brief �J�����̉�]�̃I�C���[�p���擾����
         * @return �J�����̉�]�̃I�C���[�p
         *
         * �I�C���[�p��YXZ�̏��ł��B
         */
        const glm::vec3 GetRotation() const;

        /**
         * @brief �J�����̉�]�̃I�C���[�p��ݒ肷��
         * @param rotation �V������]�̃I�C���[�p
         *
         * �I�C���[�p��YXZ�̏��ł��B
         * �����ŕێ�����View�s��̍Čv�Z���s���܂��B
         */
        void SetRotation(const glm::vec3 rotation);

        /**
         * @brief �J������Projection�s��̃p�����[�^��ݒ肷��
         * @param fovy fovy�̒l�iradians�j
         * @param aspect aspect�̒l
         * @param near near�̒l
         * @param far far�̒l
         */
        void Perspective(const GLfloat fovy, const GLfloat aspect, const GLfloat near,
            const GLfloat far);

        /**
         * @brief ViewProjection�s����v�Z���擾����
         * @return �v�Z���ꂽViewProjection�s��
         *
         * �Ăяo�����т�view_matrix_��projection_matrix_�̊|���Z���s���܂��B
         */
        const glm::mat4 GetViewProjectionMatrix() const;

        /**
         * @brief View�s����擾����
         * @return View�s��
         */
        const glm::mat4 GetViewMatrix() const;

        /**
         * @brief Projection�s����擾����
         * @return Projection�s��
         */
        const glm::mat4 GetProjectionMatrix() const;

        /**
         * @brief �R���X�g���N�^
         * @param position �J�����̈ʒu
         * @param rotation �J�����̉�]�̃I�C���[�p
         * @param fovy fovy�̒l�iradians�j
         * @param aspect aspect�̒l
         * @param near near�̒l
         * @param far far�̒l
         *
         * �K�v�ȃp�����[�^�����ׂĎ󂯎��R���X�g���N�^�ł��B
         * �I�C���[�p��YXZ�̏��ł��B
         */
        Camera(const glm::vec3 position, const glm::vec3 rotation, const GLfloat fovy,
            const GLfloat aspect, const GLfloat near, const GLfloat far);

    private:
        glm::vec3 position_;
        glm::vec3 rotation_;
        glm::mat4 view_matrix_;
        glm::mat4 projection_matrix_;

        /**
         * @brief View�s����Čv�Z����
         *
         * view_matrix_�̒l��position_��rotation_����v�Z�����l�ɐݒ肵�܂��B
         */
        void RecaluculateViewMatirx();
    };

}  // namespace game

#endif  // OPENGL_PBR_MAP_CAMERA_H_#pragma once
