#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <memory>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
	// Holds the id of the texture object, used for all texture operations to reference to this particlar texture
	GLuint id;

	// Hold loaded data
	unsigned char * imageData;

	// Texture image dimensions
	int width, height; // Width and height of loaded image in pixels

	int n;

	// Texture Format
	GLuint internalFormat; // Format of texture object
	GLuint imageFormat;	// Format of loaded image

	// Texture configuration
	GLuint wrapS;	 // Wrapping mode on S axis
	GLuint wrapT;	 // Wrapping mode on T axis
	GLfloat filterMin; // Filtering mode if texture pixels < screen pixels
	GLfloat filterMax; // Filtering mode if texture pixels > screen pixels

	// Constructor (sets default texture modes)
	Texture2D();

	// Load texture file
	void load(const std::string& filename);

	// Generates texture from image data
	//void generate(SDL_Surface *surface);
	void generate();


//	void generate(std::unique_ptr<SDL_Surface, SdlSurfaceDestroyer> &surface);

	// Binds the texture as the current active GL_TEXTURE_2D texture object
	void use() const;
};

#endif
