/*****************************************************************
 *   Author: Tyanna Prince
 *   Date: 07/15/2023
 *   Description: An enhancement of my cs330 OpenGL project where I added functionality such as charater movement,
 *  directional lighting, and shadow mapping, a cubemap, and joystick support.
 *  copyright (c) 2023 Tyanna Prince
 *  version 2.0
 *****************************************************************/

#ifndef TEXT_H
#define TEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>

#include <string>
#include <map>

#include "../memory/vertexmemory.hpp"
#include "../rendering/shader.h"

typedef struct {
	unsigned int	textureId;	// texture id storing character
	glm::ivec2		size;		// size of char
	glm::ivec2		bearing;	// distance from origin to top left of char
	unsigned int	advance;	// distance from origin to next origin (1/64th pixels)
} Character;

class TextRenderer {
public:
	TextRenderer();
	TextRenderer(int height);

	bool loadFont(FT_Library& ft, std::string path);

	void render(Shader shader, std::string text, float x, float y, glm::vec2 scale, glm::vec3 color);

	void cleanup();

private:
	int height;

	std::map<char, Character> chars;

	ArrayObject VAO;
};

#endif