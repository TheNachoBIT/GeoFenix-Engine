#include "texture.h"
#include "../../FileSystem/file.h"

namespace geofenix
{
	namespace graphics
	{
		Texture::Texture(){}

		Texture::Texture(const char* fileName, GLenum type, GLint texUnit, int widthI, int heightI)
			: width(widthI), height(heightI), type(type)
		{
			if (texture)
				glDeleteTextures(1, &texture);

			unsigned char* image = File::LoadImage(fileName, width, height);

			glGenTextures(1, &texture);
			glBindTexture(type, texture);

			glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			if (image)
			{
				glTexImage2D(type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
				glGenerateMipmap(type);
			}
			else
			{
				std::cout << "ERROR: Texture not loaded due to image not found: " << fileName << std::endl;
			}

			glActiveTexture(0);
			glBindTexture(GL_TEXTURE_2D, 0);
			SOIL_free_image_data(image);
		}

		Texture::~Texture()
		{
			if(!glfwTerminate)
				glDeleteTextures(GL_TEXTURE_2D, &texture);
		}

		inline GLuint Texture::getID() const
		{
			return this->texture;
		}

		void Texture::enable(const GLint tUnit)
		{
			glActiveTexture(GL_TEXTURE0 + tUnit);
			glBindTexture(type, this->texture);
		}

		void Texture::disable()
		{
			glActiveTexture(0);
			glBindTexture(type, 0);
		}
	}
}