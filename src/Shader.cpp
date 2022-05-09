#include "Shader.h"

Shader::Shader(const char* vertex_path, const char* fragment_path)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream vertex_shader_file;
    std::ifstream fragment_shader_file;
    
    // open files
    vertex_shader_file.open(vertex_path);
    if (vertex_shader_file.fail()) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << vertex_path << std::endl;
    } else {
        std::stringstream vertex_shader_stream;
        vertex_shader_stream << vertex_shader_file.rdbuf();
        vertex_shader_file.close();
        vertex_code = vertex_shader_stream.str();
    }

    fragment_shader_file.open(fragment_path);
    if (fragment_shader_file.fail()) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << fragment_path << std::endl;
    } else {
        std::stringstream fragment_shader_stream;
        fragment_shader_stream << fragment_shader_file.rdbuf();
        fragment_shader_file.close();
        fragment_code = fragment_shader_stream.str();
    }

    const char* vertex_shader_code = vertex_code.c_str();
    const char* fragment_shader_code = fragment_code.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    
    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_shader_code, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::fragment::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
    // shader Program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);
    // print linking errors if any
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

void Shader::use() 
{ 
    glUseProgram(m_id);
}

void Shader::set_bool(const std::string& name, bool value) const
{         
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value); 
}
void Shader::set_int(const std::string& name, int value) const
{ 
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value); 
}
void Shader::set_float(const std::string& name, float value) const
{ 
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value); 
}

void Shader::set_vec2(const std::string& name, const float x, const float y) const
{
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y); 
}

void Shader::set_vec2(const std::string& name, const glm::vec2 &vec2) const
{
    glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &vec2[0]); 
}

void Shader::set_vec3(const std::string& name, const float x, const float y, const float z) const
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z); 
}

void Shader::set_vec3(const std::string& name, const glm::vec3 &vec3) const
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &vec3[0]); 
}

void Shader::set_vec4(const std::string& name, const float x, const float y, const float z, const float w) const
{
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}

void Shader::set_vec4(const std::string& name, const glm::vec4 &vec4) const
{
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &vec4[0]); 
}

void Shader::set_mat2(const std::string& name, const glm::mat2 &mat2) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat2[0][0]);
}

void Shader::set_mat3(const std::string& name, const glm::mat3 &mat3) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat3[0][0]);
}

void Shader::set_mat4(const std::string& name, const glm::mat4 &mat4) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
}