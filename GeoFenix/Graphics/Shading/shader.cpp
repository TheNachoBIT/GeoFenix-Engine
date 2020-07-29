#include "shader.h"

namespace geofenix
{
	namespace graphics
	{
		Shader::Shader(const char* vertexPathMajor, const char* fragmentPathMajor, const char* vertexPathMinor, const char* fragmentPathMinor)
			: vertPath(vertexPathMajor), fragPath(fragmentPathMajor), vertPathMinor(vertexPathMinor), fragPathMinor(fragmentPathMinor)
		{
			shaderID = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(shaderID);
		}

		bool useMinor;
		GLuint Shader::load()
		{

			prog = glCreateProgram();
			GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

			GLuint vertShaderMin = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragShaderMin = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertString = File::Read(vertPath);
			std::string fragmentString = File::Read(fragPath);

			std::string vertStringMin = File::Read(vertPathMinor);
			std::string fragmentStringMin = File::Read(fragPathMinor);

			const char* vertexSource = vertString.c_str();
			const char* fragmentSource = fragmentString.c_str();

			const char* vertexSourceMin = vertStringMin.c_str();
			const char* fragmentSourceMin = fragmentStringMin.c_str();

			glShaderSource(vertShader, 1, &vertexSource, NULL);
			glCompileShader(vertShader);

			GLint result;
			glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);

			//Mayor
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertShader, length, &length, &error[0]);
				std::cout << "Error compiling vertex shader :C >> " << &error[0] << std::endl;
				glDeleteShader(vertShader);
				useMinor = true;
			}

			glShaderSource(fragShader, 1, &fragmentSource, NULL);
			glCompileShader(fragShader);

			glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragShader, length, &length, &error[0]);
				std::cout << "Error compiling fragment shader :C >> " << &error[0] << std::endl;
				glDeleteShader(fragShader);
				useMinor = true;
			}

			//Minor

			if (useMinor)
			{
				glShaderSource(vertShaderMin, 1, &vertexSourceMin, NULL);
				glCompileShader(vertShaderMin);

				glGetShaderiv(vertShaderMin, GL_COMPILE_STATUS, &result);

				if (result == GL_FALSE)
				{
					GLint length;
					glGetShaderiv(vertShaderMin, GL_INFO_LOG_LENGTH, &length);
					std::vector<char> error(length);
					glGetShaderInfoLog(vertShaderMin, length, &length, &error[0]);
					std::cout << "Error compiling vertex shader :C >> " << &error[0] << std::endl;
					glDeleteShader(vertShaderMin);
					return 0;
				}

				glShaderSource(fragShaderMin, 1, &fragmentSourceMin, NULL);
				glCompileShader(fragShaderMin);

				glGetShaderiv(fragShaderMin, GL_COMPILE_STATUS, &result);

				if (result == GL_FALSE)
				{
					GLint length;
					glGetShaderiv(fragShaderMin, GL_INFO_LOG_LENGTH, &length);
					std::vector<char> error(length);
					glGetShaderInfoLog(fragShaderMin, length, &length, &error[0]);
					std::cout << "Error compiling fragment shader :C >> " << &error[0] << std::endl;
					glDeleteShader(fragShaderMin);
					return 0;
				}
			}

			if (!useMinor)
			{
				glAttachShader(prog, vertShader);
				glAttachShader(prog, fragShader);

				glLinkProgram(prog);
				glValidateProgram(prog);

				glDeleteShader(vertShader);
				glDeleteShader(fragShader);
			}
			else
			{
				glAttachShader(prog, vertShaderMin);
				glAttachShader(prog, fragShaderMin);

				glLinkProgram(prog);
				glValidateProgram(prog);

				glDeleteShader(vertShaderMin);
				glDeleteShader(fragShaderMin);
			}

			return prog;
		}

		GLint Shader::getUniformLocation(const GLchar* name) const
		{
			if (uniformLocationCache.find(name) != uniformLocationCache.end())
				return uniformLocationCache[name];

			GLint location = glGetUniformLocation(shaderID, name);
			uniformLocationCache[name] = location;
			return location;
		}

		void Shader::setUniform1f(const GLchar* name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform1i(const GLchar* name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniform2f(const GLchar* name, const glm::vec2 vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniform3f(const GLchar* name, const glm::vec3 vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4f(const GLchar* name, const glm::vec4 vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
		}

		void Shader::enable() const
		{
				glUseProgram(shaderID);
		}

		void Shader::disable() const
		{
				glUseProgram(0);
		}
	}
}