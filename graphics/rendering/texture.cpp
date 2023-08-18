/*****************************************************************
 *   Author: Tyanna Prince
 *   Date: 07/15/2023
 *   Description: An enhancement of my cs330 OpenGL project where I added functionality such as charater movement,
 *  directional lighting, and shadow mapping, a cubemap, and joystick support.
 *  copyright (c) 2023 Tyanna Prince
 *  version 2.0
 *****************************************************************/

#include "texture.h"

#include <iostream>

/*
    constructor
*/

Texture::Texture(std::string name)
    : name(name), type(aiTextureType_NONE) {
    generate();
}

// initialize with image path and type
Texture::Texture(std::string dir, std::string path, aiTextureType type) 
    : dir(dir), path(path), type(type) {
    generate();
}

// generate texture id
void Texture::generate() {
    glGenTextures(1, &id);
}

// load texture from path
void Texture::load(bool flip) {
    stbi_set_flip_vertically_on_load(flip);

    int width, height, nChannels;

    unsigned char* data = stbi_load((dir + "/" + path).c_str(), &width, &height, &nChannels, 0);

    GLenum colorMode = GL_RGB;
    switch (nChannels) {
    case 1:
        colorMode = GL_RED;
        break;
    case 4:
        colorMode = GL_RGBA;
        break;
    };

    if (data) {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        std::cout << "Image not loaded at " << path << std::endl;
    }

    stbi_image_free(data);
}

/**
 * Allocates a texture with the specified format, width, height, and type.
 *
 * @param format the format of the texture
 * @param width the width of the texture
 * @param height the height of the texture
 * @param type the type of the texture
 *
 * @throws ErrorType a description of the error that may occur
 */
void Texture::allocate(GLenum format, GLuint width, GLuint height, GLenum type) {
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, NULL);
}

/**
 * Sets the parameters for a texture.
 *
 * @param texMinFilter The texture minification filter.
 * @param texMagFilter The texture magnification filter.
 * @param wrapS The texture wrap mode in the S direction.
 * @param wrapT The texture wrap mode in the T direction.
 *
 * @return void
 *
 * @throws None
 */
void Texture::setParams(GLenum texMinFilter, GLenum texMagFilter, GLenum wrapS, GLenum wrapT) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texMinFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texMagFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
}

// bind texture id
void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}

/**
 * Cleans up the texture by deleting the associated OpenGL texture object.
 *
 * @param None
 *
 * @return None
 *
 * @throws None
 */
void Texture::cleanup() {
    glDeleteTextures(1, &id);
}