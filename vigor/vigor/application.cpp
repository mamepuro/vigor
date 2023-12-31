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
		// 頂点シェーダの読み込み
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

		// フラグメントシェーダの読み込み
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

		// プログラムオブジェクトを作成
		const GLuint program = glCreateProgram();

		GLint status = GL_FALSE;
		GLsizei infoLogLength;

		// 頂点シェーダのコンパイル
		const GLuint vertexShaderObj = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderObj, 1, &vertexShaderSourcePointer, nullptr);
		glCompileShader(vertexShaderObj);
		glAttachShader(program, vertexShaderObj);

		// 頂点シェーダのチェック
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

		// フラグメントシェーダのコンパイル
		const GLuint fragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderObj, 1, &fragmentShaderSourcePointer, nullptr);
		glCompileShader(fragmentShaderObj);
		glAttachShader(program, fragmentShaderObj);

		// フラグメントシェーダのチェック
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

		// プログラムのリンク
		glLinkProgram(program);

		// リンクのチェック
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
		int prevKeyState = GLFW_RELEASE;
		while (glfwWindowShouldClose(window_) == GL_FALSE) {
			//特定の時間を経過させるロジックはここにある
			const double time = glfwGetTime();
			delta_time = time - prev_time;
			prev_time = time;
			int currentKeyStateSpace = glfwGetKey(window_, GLFW_KEY_ENTER);
			Update(delta_time);
			if (glfwGetKey(window_, GLFW_KEY_LEFT) != GLFW_RELEASE)
			{
				//camera_->SetPosition(camera_->GetPosition() + glm::vec3(0, 1, 0));
				//PrintParam(camera_->GetPosition());
				//カメラを回転させる
				//camera_->SetRotation(camera_->GetRotation() + glm::vec3(0, 0.1, 0));
				PrintParam(camera_->GetRotation());
				//オブジェクト自身を回転させる
				for (auto&& mesh_entity : mesh_entities_) {
				    mesh_entity.SetRotation(mesh_entity.GetRotation() + glm::vec3(0,0.1,0));

				}
			}
			if (glfwGetKey(window_, GLFW_KEY_UP) != GLFW_RELEASE)
			{
				//camera_->SetPosition(camera_->GetPosition() + glm::vec3(0, 1, 0));
				//PrintParam(camera_->GetPosition());
				//カメラを回転させる
				auto v = mesh_entities_[1].mesh_->GetVertices();
				v[0].z += 0.1f;
				mesh_entities_[1].mesh_->SetVertices(v);
				std::cerr << "z + 4" << std::endl;
				//PrintParam(camera_->GetRotation());
				//オブジェクト自身を回転させる
				//for (auto&& mesh_entity : mesh_entities_) {
				//    mesh_entity.SetRotation(mesh_entity.GetRotation() + glm::vec3(0,0.1,0));

				//}
			}
			if (currentKeyStateSpace != prevKeyState)
			{
				if (currentKeyStateSpace == GLFW_PRESS)
				{
					//mesh_entities_[0].ConnectTo(mesh_entities_[1], mesh_entities_[0]);
					//mesh_entities_[0].Connect(&mesh_entities_[1]);
					mesh_entities_[0].ConnectNext(&mesh_entities_[1]);
					//mesh_entities_[0].TestBend();
					std::cerr << "connected 0 to 1" << std::endl;
					prevKeyState = GLFW_PRESS;
				}
				else
				{
					prevKeyState = GLFW_RELEASE;
				}
				
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

		// Shaderプログラムの作成
		program_ = createProgram("shader.vert", "shader.frag");
		program_edge_ = createProgram("shader.vert", "shader_edge.frag");
		program_points_ = createProgram("shader_masspoint.vert", "shader_masspoint.frag")
		model_loc_ = glGetUniformLocation(program_, "Model");
		view_projection_loc_ = glGetUniformLocation(program_, "ViewProjection");

		// Meshの読み込み
	  //TODO:ファイルがnullならエラーを返す処理を追加する
		std::vector<std::shared_ptr<game::Mesh>> mesh_obj;
		for (int i = 0; i < 4; i++)
		{
			auto mesh = Mesh::LoadObjMesh("block.obj");
			mesh_obj.push_back(mesh);
		}
		auto testMesh = Mesh::CreateTestMesh();
		auto block1 = new Block(mesh_obj[0], glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f), glm::vec3(1.0f), 1, 1, mesh_obj[0]->vertices_,
			1, 5, 0, 3);
		auto block2 = new Block(mesh_obj[1], glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f), glm::vec3(1.0f), 1, 1, mesh_obj[1]->vertices_,
			1, 5, 0, 3);
		// MeshEntityの作成
		mesh_entities_.emplace_back(*block1);
		mesh_entities_.emplace_back(*block2);
		/*mesh_entities_.emplace_back(mesh_obj[2], glm::vec3(-0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f), glm::vec3(1.0f), 1, 5);*/
		/*mesh_entities_[0].r_connect.push_back(mesh_entities_[0]);
		mesh_entities_[0].l_connect.push_back(mesh_entities_[0]);
		mesh_entities_[1].r_connect.push_back(mesh_entities_[1]);
		mesh_entities_[1].l_connect.push_back(mesh_entities_[1]);*/
		//mesh_entities_[2].r_connect.push_back(mesh_entities_[2]);
		//mesh_entities_[2].l_connect.push_back(mesh_entities_[2]);
		// Cameraの作成
		camera_ = std::make_unique<Camera>(
			glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f), glm::radians(60.0f),
			static_cast<float>(width) / height, 0.1f, 100.0f);

		return true;
	}

	bool Application::InitWindow(const GLuint width, const GLuint height) {
		glfwSetErrorCallback(
			[](auto id, auto description) { std::cerr << description << std::endl; });

		// GLFWの初期化
		if (!glfwInit()) {
			return false;
		}

		// OpenGL Version 4.6 Core Profileを選択する
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// リサイズ不可
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		// ウィンドウの作成
		window_ = glfwCreateWindow(width, height, "Game", nullptr, nullptr);
		if (window_ == nullptr) {
			std::cerr << "Can't create GLFW window." << std::endl;
			return false;
		}
		glfwMakeContextCurrent(window_);
		glClearColor(0.5, 0.5, 0.5, 1.0);
		// GLEWの初期化
		if (glewInit() != GLEW_OK) {
			std::cerr << "Can't initialize GLEW." << std::endl;
			return false;
		}

		// VSyncを待つ
		glfwSwapInterval(1);

		// OpenGL エラーのコールバック
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
			glUniformMatrix4fv(model_loc_, 1, GL_FALSE, &model[0][0]);
			mesh_entity.mesh_->Draw();

		}


		//TODO: 本当にこの実装でいいの？
		//稜線描画用に，もう一度稜線描画を行うシェーダを呼び，描画命令を呼ぶ
		glUseProgram(program_edge_);

		glUniformMatrix4fv(view_projection_loc_, 1, GL_FALSE, &view_projection[0][0]);

		for (auto&& mesh_entity : mesh_entities_) {
			mesh_entity.Simulate(0.0001);
			auto model = mesh_entity.GetModelMatrix();
			glUniformMatrix4fv(model_loc_, 1, GL_FALSE, &model[0][0]);
			mesh_entity.mesh_->Draw(program_edge_);

		}
	}

}