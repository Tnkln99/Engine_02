#include <iostream>

#include "stb_image.h"

#include "Texture.h"
#include "../../Utils/Log.h"

Texture2D::Texture2D()
	: width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB),
	  wrapS(GL_REPEAT), wrapT(GL_REPEAT),
	  filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
	glGenTextures(1, &id);
}

void Texture2D::load(const std::string& filename)
{
	imageData = stbi_load(filename.c_str(), &width, &height, &n, 4);
    if (!imageData)
    {
        LOG(Error) << "Could not load " << filename;
    }
    if ((width & (width - 1)) != 0 || (height & (height - 1)) != 0)
    {
        LOG(Warning) << "Texture " << filename << " is not power-of-2 dimensions";
    }

    // Flip image vertically
    int width_in_bytes = width * 4;
    unsigned char *top = NULL;
    unsigned char *bottom = NULL;
    unsigned char temp = 0;
    int half_height = height / 2;

    for (int row = 0; row < half_height; row++)
    {
        top = imageData + row * width_in_bytes;
        bottom = imageData + (height - row - 1) * width_in_bytes;
        for (int col = 0; col < width_in_bytes; col++)
        {
            temp = *top;
            *top = *bottom;
            *bottom = temp;
            top++;
            bottom++;
        }
    }
}

void Texture2D::generate()
{
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        imageData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT); // GL_CLAMP_TO_EDGE
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);

    glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	delete imageData;
}

void Texture2D::use() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}
