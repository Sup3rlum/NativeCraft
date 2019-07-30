#include "Texture.h"


Texture::Texture(const char* _path)
{
	glGenTextures(1, &_handle);
	glBindTexture(GL_TEXTURE_2D, _handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int _width, _height, _channels;

	_dataInternal = stbi_load(_path, &_width, &_height, &_channels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _dataInternal);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(_dataInternal);
}