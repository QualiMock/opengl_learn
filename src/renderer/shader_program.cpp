#include "shader_program.h"

#include <iostream>

namespace Renderer
{

	ShaderProgram::ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader)
	{
        GLint success;

        GLuint vertexShaderID;
        if(!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
        {
            std::cerr << "VERTEX_SHADER compile time error" << std::endl;
            return;
        }

        GLuint fragmentShaderID;
        if(!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
        {
            std::cerr << "FRAGMENT_SHADER compile time error" << std::endl;
            glDeleteShader(vertexShaderID);
            return;
        }

        m_ID = glCreateProgram();
	    glAttachShader(m_ID, vertexShaderID);
	    glAttachShader(m_ID, fragmentShaderID);
	    glLinkProgram(m_ID);
        
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if(!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
            std::cerr << "ERROR_SHADER: link shader error:\n" << infoLog << std::endl;

        }
        else
        {
            m_isCompiled = true;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
	}

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_ID);
    }

    void ShaderProgram::use() const
    {
        glUseProgram(m_ID);
    }

    bool ShaderProgram::createShader(const std::string &source, const GLenum shaderType, GLuint &shaderID)
    {
        const char* code = source.c_str();
        GLint success;

        shaderID = glCreateShader(shaderType);
        glShaderSource(shaderID, 1, &code, nullptr);
        glCompileShader(shaderID);

        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);

            std::cerr << "ERROR::SHADER: Compile time error:\n" << infoLog << std::endl;

            return false;
        }

        return true;
    }

    ShaderProgram &ShaderProgram::operator = (ShaderProgram &&shaderProgram) noexcept
    {
        glDeleteProgram(m_ID);
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
        
        return *this;
    }


    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
    {
        glDeleteProgram(m_ID);
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
    }
}
