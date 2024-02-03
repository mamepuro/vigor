#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "application.h"
#include "Block.h"

//ブロックのIDを初期化する
int game::Block::mID = 0;

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

int main() {
    game::Application app;
    return app.Run() ? 0 : -1;
}