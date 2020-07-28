#pragma once
#include <iostream>
#include <glm.hpp>
#include <vec2.hpp>
#include <GL/glew.h>
#include <vector>
#include <gtc/type_ptr.hpp>
#include "../../FileSystem/file.h"
#include <unordered_map>

namespace geofenix
{
	namespace graphics
	{
		class Shader
		{
		public:
			GLuint prog;

			GLuint shaderID;
			const char* vertPath;
			const char* fragPath;
			mutable std::unordered_map<std::string, GLint> uniformLocationCache;

			Shader(const char* vertexPath, const char* fragmentPath);
			~Shader();

			GLint getUniformLocation(const GLchar* name) const;

			void setUniform1f(const GLchar* name, float value);
			void setUniform1i(const GLchar* name, int value);
			void setUniform2f(const GLchar* name, const glm::vec2 vector);
			void setUniform3f(const GLchar* name, const glm::vec3 vector);
			void setUniform4f(const GLchar* name, const glm::vec4 vector);
			void setUniformMat4(const GLchar* name, const glm::mat4& matrix);

			void enable() const;
			void disable() const;

			GLuint load();
		};
	}
}
