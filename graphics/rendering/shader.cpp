/*****************************************************************
 *   Author: Tyanna Prince
 *   Date: 07/15/2023
 *   Description: An enhancement of my cs330 OpenGL project where I added functionality such as charater movement,
 *  directional lighting, and shadow mapping, a cubemap, and joystick support.
 *  copyright (c) 2023 Tyanna Prince
 *  version 2.0
 *****************************************************************/

#include "Shader.h"

#include <stdio.h>
#include <fstream>

/*
    constructors
*/

// default
Shader::Shader() {}

// initialize with paths to vertex and fragment shaders
Shader::Shader(bool includeDefaultHeader, const char* vertexShaderPath, const char* fragShaderPath, const char* geoShaderPath) {
    generate(includeDefaultHeader, vertexShaderPath, fragShaderPath, geoShaderPath);
}

/*
    process functions
*/

/**
 * Compiles a shader, attaches it to a program, and deletes it afterwards.
 *
 * @param id the ID of the program to attach the shader to
 * @param includeDefaultHeader whether to include the default shader header
 * @param path the path to the shader file
 * @param type the type of shader to compile
 *
 * @throws ErrorType if there was an error compiling the shader or attaching it to the program
 */
void compileAndAttach(GLuint id, bool includeDefaultHeader, const char* path, GLuint type) {
    if (!path) {
        return;
    }

    GLuint shader = Shader::compileShader(includeDefaultHeader, path, type);
    glAttachShader(id, shader);
    glDeleteShader(shader);
}

// generate using vertex and frag shaders
void Shader::generate(bool includeDefaultHeader, const char* vertexShaderPath, const char* fragShaderPath, const char* geoShaderPath) {
    id = glCreateProgram();

    // compile and attach shaders
    compileAndAttach(id, includeDefaultHeader, vertexShaderPath, GL_VERTEX_SHADER);
    compileAndAttach(id, includeDefaultHeader, fragShaderPath, GL_FRAGMENT_SHADER);
    compileAndAttach(id, includeDefaultHeader, geoShaderPath, GL_GEOMETRY_SHADER);
    glLinkProgram(id);

    // linking errors
    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char* infoLog = (char*)malloc(512);
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "Linking error:" << std::endl << infoLog << std::endl;
    }
}

// activate shader
void Shader::activate() {
    glUseProgram(id);
}

// cleanup
void Shader::cleanup() {
    glDeleteProgram(id);
}

/*
    set uniform variables
*/

/**
 * Sets a boolean value for a given shader parameter.
 *
 * @param name The name of the shader parameter.
 * @param value The boolean value to be set.
 *
 * @throws ErrorType If there was an error setting the boolean value.
 */
void Shader::setBool(const std::string& name, bool value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

/**
 * Sets an integer value for a shader uniform variable.
 *
 * @param name The name of the shader uniform variable.
 * @param value The integer value to be set.
 *
 * @throws ErrorType Description of the error that can be thrown.
 */
void Shader::setInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

/**
 * Sets a float value for the specified uniform variable in the shader.
 *
 * @param name the name of the uniform variable
 * @param value the float value to set
 *
 * @throws ErrorType if the uniform variable does not exist or if there is an error setting the value
 */
void Shader::setFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

/**
 * Set three float values in the shader.
 *
 * @param name the name of the uniform variable
 * @param v1 the first float value
 * @param v2 the second float value
 * @param v3 the third float value
 *
 * @throws ErrorType if there is an error setting the uniform value
 */
void Shader::set3Float(const std::string& name, float v1, float v2, float v3) {
    glUniform3f(glGetUniformLocation(id, name.c_str()), v1, v2, v3);
}

/**
 * Sets a vec3 uniform in the shader program.
 *
 * @param name the name of the uniform variable
 * @param v the vector to set as the uniform value
 *
 * @throws std::runtime_error if the uniform variable does not exist or is not a vec3
 */
void Shader::set3Float(const std::string& name, glm::vec3 v) {
    glUniform3f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z);
}

/**
 * Sets a 4-component float value for the specified uniform variable in the shader.
 *
 * @param name the name of the uniform variable
 * @param v1 the first float value
 * @param v2 the second float value
 * @param v3 the third float value
 * @param v4 the fourth float value
 *
 * @throws ErrorType if an error occurs during the operation
 */
void Shader::set4Float(const std::string& name, float v1, float v2, float v3, float v4) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), v1, v2, v3, v4);
}

/**
 * Sets a 4-component float value for a shader uniform variable.
 *
 * @param name The name of the uniform variable.
 * @param color The 4-component float value to set.
 *
 * @throws ErrorType If there is an error setting the uniform value.
 */
void Shader::set4Float(const std::string& name, aiColor4D color) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), color.r, color.g, color.b, color.a);
}

/**
 * Sets a 4 component float vector uniform in the shader program.
 *
 * @param name the name of the uniform variable in the shader program
 * @param v the 4 component float vector to set
 *
 * @throws ErrorType if the uniform does not exist or is not a 4 component float vector
 */
void Shader::set4Float(const std::string& name, glm::vec4 v) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), v.x, v.y, v.z, v.w);
}

/**
 * Sets a 3x3 matrix uniform in the shader program.
 *
 * @param name the name of the uniform variable
 * @param val the value of the matrix
 *
 * @throws ErrorType if the uniform variable does not exist or if an OpenGL error occurs
 */
void Shader::setMat3(const std::string& name, glm::mat3 val) {
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

/**
 * Sets a 4x4 matrix uniform value in the shader.
 *
 * @param name the name of the uniform variable
 * @param val the matrix value to set
 *
 * @throws ErrorType if the uniform variable does not exist or if an error occurs while setting the value
 */
void Shader::setMat4(const std::string& name, glm::mat4 val) {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

/*
    static
*/

// compile shader program
GLuint Shader::compileShader(bool includeDefaultHeader, const char* filePath, GLuint type) {
    // create shader from file
    GLuint ret = glCreateShader(type);
    GLchar* shader = loadShaderSrc(includeDefaultHeader, filePath);
    glShaderSource(ret, 1, &shader, NULL);
    glCompileShader(ret);
    free(shader);

    // catch compilation error
    int success;
    glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
    if (!success) {
        char* infoLog = (char*)malloc(512);
        glGetShaderInfoLog(ret, 512, NULL, infoLog);
        std::cout << "Error with shader comp." << filePath << ":" << std::endl << infoLog << std::endl;
    }

    return ret;
}

// stream containing default headers
std::stringstream Shader::defaultHeaders;

// load into default header
void Shader::loadIntoDefault(const char* filepath) {
    char *fileContents = Shader::loadShaderSrc(false, filepath);

    Shader::defaultHeaders << fileContents;

    free(fileContents);
}

// clear default header (after shader compilation)
void Shader::clearDefault() {
    Shader::defaultHeaders.clear();
}

// load string from file
char *Shader::loadShaderSrc(bool includeDefaultHeader, const char* filePath) {
    std::string fullPath = Shader::defaultDirectory + '/' + filePath;

    FILE* file = NULL;
    fopen_s(&file, fullPath.c_str(), "rb");
    if (!file) {
        std::cout << "Could not open " << filePath << std::endl;
        return NULL;
    }

    // move cursor to the end
    fseek(file, 0L, SEEK_END);
    // get length
    int len = ftell(file);
    // return to beginning
    fseek(file, 0, SEEK_SET);

    // read
    char* ret = NULL;
    int cursor = 0;
    if (includeDefaultHeader) {
        // copy header and advance cursor to read into space after default header
        cursor = Shader::defaultHeaders.str().size();
        ret = (char*)malloc(cursor + len + 1);
        memcpy_s(ret, cursor + len + 1, Shader::defaultHeaders.str().c_str(), cursor);
    }
    else {
        ret = (char*)malloc(len + 1);
    }
    // read from file
    fread(ret + cursor, 1, len, file);
    ret[cursor + len] = 0; // terminator

    return ret;
}