#include "mesh.h"


namespace game {

    std::vector<glm::vec3> Mesh::GetVertices() const {
        return vertices_;
    }
    void Mesh::SetVertices(std::vector<glm::vec3> vertices) {
        vertices_ = vertices;
        UpdateModel();
    }

    void Mesh::UpdateModel() {
        //VBOの更新を行う
        //CAUTION: GLuint bufferは対象のオブジェクトIDが入る。マジックナンバー(1などの定数)を指定すると、特定のオブジェクトの再描画のみが行われてしまうので注意すること
        glNamedBufferSubData(vao_, 0, sizeof(glm::vec3) * vertices_.size(), &vertices_[0]);
    }

    void Mesh::Draw() const {
        glBindVertexArray(vao_);
        glDrawArrays(GL_TRIANGLES, 0, size_);
    }

    void Mesh::Draw(GLuint program) const {
        glBindVertexArray(vao_);
        glDrawArrays(GL_LINES, 0, size_);
    }

    void Mesh::DrawPoints() const {
        glBindVertexArray(vao_);
        glDrawArrays(GL_POINTS, 0, size_);
    }

    Mesh::Mesh(std::vector<glm::vec3>& vertices) : size_(vertices.size()) {
        vertices_ = vertices;
        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        glGenBuffers(1, &vertices_vbo_);
        glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo_);
        glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3),
            &vertices_[0], GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Mesh::~Mesh() { Release(); }

    Mesh::Mesh(Mesh&& other) noexcept
        : size_(std::move(other.size_)),
        vao_(other.vao_),
        vertices_vbo_(other.vertices_vbo_),
        colors_vbo_(other.colors_vbo_) {
        other.vao_ = 0;

        other.vertices_vbo_ = 0;
        other.colors_vbo_ = 0;
    }

    Mesh& Mesh::operator=(Mesh&& other) noexcept {
        if (this != &other) {
            Release();

            size_ = std::move(other.size_);

            vao_ = other.vao_;
            other.vao_ = 0;

            vertices_vbo_ = other.vertices_vbo_;
            colors_vbo_ = other.colors_vbo_;
            other.vertices_vbo_ = 0;
            other.colors_vbo_ = 0;
        }

        return *this;
    }

    /*三角形メッシュ作成機能を削除
    std::unique_ptr<Mesh> Mesh::CreateTriangleMesh() {
        // 頂点位置
        const std::vector<glm::vec3> vertices = {
            glm::vec3(0.0f, 0.5f, 0.0f),
            glm::vec3(-0.5f, -0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, 0.0f),
        };
        // 頂点カラー
        const std::vector<glm::vec3> colors = {
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
        };
        return std::make_unique<Mesh>(vertices, colors);
    }
    */

    void Mesh::Release() {
        glDeleteVertexArrays(1, &vao_);
        glDeleteBuffers(1, &vertices_vbo_);
        glDeleteBuffers(1, &colors_vbo_);
    }

    std::vector<std::string> Mesh::SplitString(const std::string& s, char delim) {
        std::vector<std::string> elems(0);
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    std::shared_ptr<Mesh> Mesh::LoadObjMesh(const std::string file) {
        std::vector<unsigned int> vertex_indices;
        std::vector<glm::vec3> tmp_vertices;
        std::vector<glm::vec3> vertices;

        std::ifstream ifs(file);
        std::string line;
        if (ifs.fail()) {
            std::cerr << "Can't open obj file: " << file << std::endl;
            return nullptr;
        }
        while (getline(ifs, line)) {
            auto col = SplitString(line, ' ');

            if (col[0] == "v") {
                tmp_vertices.emplace_back(std::stof(col[1]), std::stof(col[2]),
                    std::stof(col[3]));
            }
            else if (col[0] == "f") {
                auto v1 = SplitString(col[1], '/');
                auto v2 = SplitString(col[2], '/');
                auto v3 = SplitString(col[3], '/');
                vertex_indices.emplace_back(std::stoi(v1[0]));
                vertex_indices.emplace_back(std::stoi(v2[0]));
                vertex_indices.emplace_back(std::stoi(v3[0]));
            }
        }

        for (unsigned int i = 0; i < vertex_indices.size(); i++) {
            unsigned int vertexIndex = vertex_indices[i];
            vertices.emplace_back(tmp_vertices[vertexIndex - 1]);
        }
        auto mesh = std::make_shared<Mesh>(vertices);
        mesh->vertices_ = vertices;
        return mesh;
    }

    std::shared_ptr<Mesh> Mesh::CreateTestMesh()
    {
        auto mesh = LoadObjMesh("testCloth.obj");
        return mesh;
    }

   

}  // namespace game