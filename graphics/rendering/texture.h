/*****************************************************************
 *   Author: Tyanna Prince
 *   Date: 07/15/2023
 *   Description: An enhancement of my cs330 OpenGL project where I added functionality such as charater movement,
 *  directional lighting, and shadow mapping, a cubemap, and joystick support.
 *  copyright (c) 2023 Tyanna Prince
 *  version 2.0
 *****************************************************************/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "scene.h"

#include <stb/stb_image.h>

/*
    class to represent texture
*/

class Texture {
public:
    /*
        constructor
    */

    // initialize with name
    Texture(std::string name);

    // initialize with image path and type
    Texture(std::string dir, std::string path, aiTextureType type);

    // generate texture id
    void generate();

    // load texture from path
    void load(bool flip = true);

    void allocate(GLenum format, GLuint width, GLuint height, GLenum type);

    static void setParams(GLenum texMinFilter = GL_NEAREST,
        GLenum texMagFilter = GL_NEAREST,
        GLenum wrapS = GL_REPEAT,
        GLenum wrapT = GL_REPEAT);

    // bind texture id
    void bind();

    void cleanup();

    /*
        texture object values
    */
    
    // texture id
    unsigned int id;
    // texture type
    aiTextureType type;
    // name
    std::string name;
    // directory of image
    std::string dir;
    // name of image
    std::string path;
};

#endif