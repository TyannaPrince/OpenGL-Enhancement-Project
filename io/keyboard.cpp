

/*****************************************************************
 *   Author: Tyanna Prince
 *   Date: 07/15/2023
 *   Description: An enhancement of my cs330 OpenGL project where I added functionality such as charater movement,
 *  directional lighting, and shadow mapping, a cubemap, and joystick support.
 *  copyright (c) 2023 Tyanna Prince
 *  version 2.0
 *****************************************************************/

#include "keyboard.h"

/*
    define initial static values
*/

// key state array (true for down, false for up)
bool Keyboard::keys[GLFW_KEY_LAST] = { 0 };
// key changed array (true if changed)
bool Keyboard::keysChanged[GLFW_KEY_LAST] = { 0 };

/*
    static callback
*/

// key state changed
void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_RELEASE) {
        if (!keys[key]) {
            keys[key] = true;
        }
    }
    else {
        keys[key] = false;
    }
    keysChanged[key] = action != GLFW_REPEAT;
}

/*
    static accessors
*/

// get key state
bool Keyboard::key(int key) {
    return keys[key];
}

// get if key recently changed
bool Keyboard::keyChanged(int key) {
    bool ret = keysChanged[key];
    // set to false because change no longer new
    keysChanged[key] = false;
    return ret;
}

// get if key recently changed and is up
bool Keyboard::keyWentDown(int key) {
    return keys[key] && keyChanged(key);
}

// get if key recently changed and is down
bool Keyboard::keyWentUp(int key) {
    return !keys[key] && keyChanged(key);
}