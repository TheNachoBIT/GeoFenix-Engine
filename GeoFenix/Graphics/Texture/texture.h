#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <glfw3.h>

namespace geofenix
{
	namespace graphics
	{
		class Texture
		{
		public:
			GLuint texture;
			int width;
			int	height;
			GLenum type;

			Texture();
			Texture(const char* fileName, GLenum type, GLint texUnit, int widthI, int heightI);
			~Texture();

			inline GLuint getID() const;

			void enable(const GLint tUnit);
			void disable();
		};
	}
}