#include <joxy/renderer/shader.hpp>

std::string read_file_as_string(const char *filepath)
{
    std::ifstream file_stream(filepath, std::ios::in);
    if (!file_stream.is_open())
    {
        std::cerr << "Could not read file " << filepath << ". File does not exist." << std::endl;
        return "";
    }
    std::string content;
    std::string line = "";
    while (!file_stream.eof())
    {
        std::getline(file_stream, line);
        content.append(line + "\n");
    }
    file_stream.close();
    return content;
}

Shader::Shader(const char *filepath, ShaderType type)
{
    this->type = type;

    if (type == ShaderType::VertexShader)
    {
        this->ID = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == ShaderType::FragmentShader)
    {
        this->ID = glCreateShader(GL_FRAGMENT_SHADER);
    }

    std::string shaderSource = read_file_as_string(filepath);
    const char *source = shaderSource.c_str();

    glShaderSource(this->ID, 1, &source, nullptr);

    glCompileShader(this->ID);

    int success;
    char info[1024];
    glGetShaderiv(this->ID, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(this->ID, 512, nullptr, info);
        if (type == ShaderType::VertexShader)
        {
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << info << std::endl;
        }
        else if (type == ShaderType::FragmentShader)
        {
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << info << std::endl;
        }
    }
}

Shader::~Shader()
{
    glDeleteShader(this->ID);
}
