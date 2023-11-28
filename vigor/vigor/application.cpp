#include "application.h"
#include "MeshEntity.h"
#include "camera.h"

namespace game {

	void PrintParam(glm::vec3 v)
	{
		std::cout << "type: vec3 x = " << v.x << " y= " << v.y << " z= " << v.z << std::endl;
		return;
	}

	GLuint createProgram(std::string vertexShaderFile,
		std::string fragmentShaderFile) {
		// ���_�V�F�[�_�̓ǂݍ���
		std::ifstream vertexIfs(vertexShaderFile, std::ios::binary);
		if (vertexIfs.fail()) {
			std::cerr << "Error: Can't open source file: " << vertexShaderFile
				<< std::endl;
			return 0;
		}
		auto vertexShaderSource =
			std::string(std::istreambuf_iterator<char>(vertexIfs),
				std::istreambuf_iterator<char>());
		if (vertexIfs.fail()) {
			std::cerr << "Error: Can't read source file: " << vertexShaderFile
				<< std::endl;
			return 0;
		}
		const GLchar* vertexShaderSourcePointer = vertexShaderSource.c_str();

		// �t���O�����g�V�F�[�_�̓ǂݍ���
		std::ifstream fragmentIfs(fragmentShaderFile, std::ios::binary);
		if (fragmentIfs.fail()) {
			std::cerr << "Error: Can't open source file: " << fragmentShaderFile
				<< std::endl;
			return 0;
		}
		auto fragmentShaderSource =
			std::string(std::istreambuf_iterator<char>(fragmentIfs),
				std::istreambuf_iterator<char>());
		if (fragmentIfs.fail()) {
			std::cerr << "Error: Can't read source file: " << fragmentShaderFile
				<< std::endl;
			return 0;
		}
		const GLchar* fragmentShaderSourcePointer = fragmentShaderSource.c_str();

		// �v���O�����I�u�W�F�N�g���쐬
		const GLuint program = glCreateProgram();

		GLint status = GL_FALSE;
		GLsizei infoLogLength;

		// ���_�V�F�[�_�̃R���p�C��
		const GLuint vertexShaderObj = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderObj, 1, &vertexShaderSourcePointer, nullptr);
		glCompileShader(vertexShaderObj);
		glAttachShader(program, vertexShaderObj);

		// ���_�V�F�[�_�̃`�F�b�N
		glGetShaderiv(vertexShaderObj, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
			std::cerr << "Compile Error in Vertex Shader." << std::endl;
		glGetShaderiv(vertexShaderObj, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 1) {
			std::vector<GLchar> vertexShaderErrorMessage(infoLogLength);
			glGetShaderInfoLog(vertexShaderObj, infoLogLength, nullptr,
				vertexShaderErrorMessage.data());
			std::cerr << vertexShaderErrorMessage.data() << std::endl;
		}

		glDeleteShader(vertexShaderObj);

		// �t���O�����g�V�F�[�_�̃R���p�C��
		const GLuint fragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderObj, 1, &fragmentShaderSourcePointer, nullptr);
		glCompileShader(fragmentShaderObj);
		glAttachShader(program, fragmentShaderObj);

		// �t���O�����g�V�F�[�_�̃`�F�b�N
		glGetShaderiv(fragmentShaderObj, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
			std::cerr << "Compile Error in Fragment Shader." << std::endl;
		glGetShaderiv(fragmentShaderObj, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 1) {
			std::vector<GLchar> fragmentShaderErrorMessage(infoLogLength);
			glGetShaderInfoLog(fragmentShaderObj, infoLogLength, nullptr,
				fragmentShaderErrorMessage.data());
			std::cerr << fragmentShaderErrorMessage.data() << std::endl;
		}

		glDeleteShader(fragmentShaderObj);

		// �v���O�����̃����N
		glLinkProgram(program);

		// �����N�̃`�F�b�N
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 1) {
			std::vector<GLchar> programLinkErrorMessage(infoLogLength);
			glGetProgramInfoLog(program, infoLogLength, nullptr,
				programLinkErrorMessage.data());
			std::cerr << programLinkErrorMessage.data() << std::endl;
		}

		return program;
	}

	bool Application::Run() {
		if (!Init()) {
			std::cerr << "Initialization error..." << std::endl;
			return false;
		}

		glfwSetTime(0.0);
		double delta_time = 0.0;
		double prev_time = 0.0;

		while (glfwWindowShouldClose(window_) == GL_FALSE) {
			//����̎��Ԃ��o�߂����郍�W�b�N�͂����ɂ���
			const double time = glfwGetTime();
			delta_time = time - prev_time;
			prev_time = time;

			Update(delta_time);
			if (glfwGetKey(window_, GLFW_KEY_LEFT) != GLFW_RELEASE)
			{
				//camera_->SetPosition(camera_->GetPosition() + glm::vec3(0, 1, 0));
				//PrintParam(camera_->GetPosition());
				//�J��������]������
				camera_->SetRotation(camera_->GetRotation() + glm::vec3(0, 0.1, 0));
				PrintParam(camera_->GetRotation());
				//�I�u�W�F�N�g���g����]������
				//for (auto&& mesh_entity : mesh_entities_) {
				//    mesh_entity.SetRotation(mesh_entity.GetRotation() + glm::vec3(0,0.1,0));

				//}
			}
			glfwSwapBuffers(window_);
			glfwPollEvents();
		}

		glfwTerminate();

		return true;
	}

	bool Application::Init() {
		const GLuint width = 960;
		const GLuint height = 540;

		if (!InitWindow(width, height)) {
			std::cerr << "Error: InitWindow" << std::endl;
			return false;
		}

		// Shader�v���O�����̍쐬
		program_ = createProgram("shader.vert", "shader.frag");
		program_edge_ = createProgram("shader.vert", "shader_edge.frag");
		model_loc_ = glGetUniformLocation(program_, "Model");
		view_projection_loc_ = glGetUniformLocation(program_, "ViewProjection");

		// Mesh�̓ǂݍ���
	  //TODO:�t�@�C����null�Ȃ�G���[��Ԃ�������ǉ�����
		auto mesh = Mesh::LoadObjMesh("block.obj");

		// MeshEntity�̍쐬
		mesh_entities_.emplace_back(mesh, glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f), glm::vec3(1.0f));
		mesh_entities_.emplace_back(mesh, glm::vec3(2.0f, 0.0f, 0.0f),
			glm::vec3(0.0f), glm::vec3(1.0f));
		mesh_entities_.emplace_back(mesh, glm::vec3(-2.0f, 0.0f, 0.0f),
			glm::vec3(0.0f), glm::vec3(1.0f));

		// Camera�̍쐬
		camera_ = std::make_unique<Camera>(
			glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f), glm::radians(60.0f),
			static_cast<float>(width) / height, 0.1f, 100.0f);

		return true;
	}

	bool Application::InitWindow(const GLuint width, const GLuint height) {
		glfwSetErrorCallback(
			[](auto id, auto description) { std::cerr << description << std::endl; });

		// GLFW�̏�����
		if (!glfwInit()) {
			return false;
		}

		// OpenGL Version 4.6 Core Profile��I������
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// ���T�C�Y�s��
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		// �E�B���h�E�̍쐬
		window_ = glfwCreateWindow(width, height, "Game", nullptr, nullptr);
		if (window_ == nullptr) {
			std::cerr << "Can't create GLFW window." << std::endl;
			return false;
		}
		glfwMakeContextCurrent(window_);
		glClearColor(0.5, 0.5, 0.5, 1.0);
		// GLEW�̏�����
		if (glewInit() != GLEW_OK) {
			std::cerr << "Can't initialize GLEW." << std::endl;
			return false;
		}

		// VSync��҂�
		glfwSwapInterval(1);

		// OpenGL �G���[�̃R�[���o�b�N
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(
			[](auto source, auto type, auto id, auto severity, auto length,
				const auto* message, const void* userParam) {
					auto t = type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "";
		std::cerr << "GL CALLBACK: " << t << " type = " << type
			<< ", severity = " << severity << ", message = " << message
			<< std::endl;
			},
			0);
		glEnable(GL_DEPTH_TEST);
		return true;
	}

	void Application::Update(const double delta_time) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program_);

		auto view_projection = camera_->GetViewProjectionMatrix();
		glUniformMatrix4fv(view_projection_loc_, 1, GL_FALSE, &view_projection[0][0]);

		for (auto&& mesh_entity : mesh_entities_) {
			auto model = mesh_entity.GetModelMatrix();
			glUniformMatrix4fv(model_loc_, 1, GL_FALSE, &model[0][0]);
			mesh_entity.mesh_->Draw();

		}

		//TODO: �{���ɂ��̎����ł����́H
		//�Ő��`��p�ɁC������x�Ő��`����s���V�F�[�_���ĂсC�`�施�߂��Ă�
		glUseProgram(program_edge_);

		glUniformMatrix4fv(view_projection_loc_, 1, GL_FALSE, &view_projection[0][0]);

		for (auto&& mesh_entity : mesh_entities_) {
			auto model = mesh_entity.GetModelMatrix();
			glUniformMatrix4fv(model_loc_, 1, GL_FALSE, &model[0][0]);
			mesh_entity.mesh_->Draw(program_edge_);

		}
	}

}