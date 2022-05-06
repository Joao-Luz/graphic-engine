#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  
class Shader
{
private:
    unsigned int m_id;
public:
  
    // constructor reads and builds the shader
    Shader(const char* vertex_path, const char* fragment_path);
    ~Shader();

    unsigned int id() { return m_id; }
    void set_id(unsigned int id) { m_id = id; }

    // use/activate the shader
    void use();
    // utility uniform functions
    void set_bool(const std::string& name, bool value) const;  
    void set_int(const std::string& name, int value) const;   
    void set_float(const std::string& name, float value) const;
    void set_vec2(const std::string& name, const float x, const float y) const;
    void set_vec2(const std::string& name, const float* vec2) const;
    void set_vec3(const std::string& name, const float x, const float y, const float z) const;
    void set_vec3(const std::string& name, const float* vec3) const;
    void set_vec4(const std::string& name, const float x, const float y, const float z, const float w) const;
    void set_vec4(const std::string& name, const float* vec4) const;
    void set_mat2(const std::string& name, const glm::mat2 &mat2) const;
    void set_mat3(const std::string& name, const glm::mat3 &mat3) const;
    void set_mat4(const std::string& name, const glm::mat4 &mat4) const;
};