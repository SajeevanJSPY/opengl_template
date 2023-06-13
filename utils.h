#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void printShaderLog(unsigned int shader) {
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

    if (len > 0) {
        log = (char *)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        printf("Shader info log: %s\n", log);
        free(log);
    }
}

void printProgramLog(int prog) {
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char *)malloc(len);
        glGetProgramInfoLog(prog, len, &chWrittn, log);
        printf("Program Info log: %s\n", log);
        free(log);
    } 
}

bool checkOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        printf("glError: %d\n", glErr);
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}

const char *vshaderSource = 
    "#version 450 core\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(0.f, 0.f, 0.f, 1.f);\n"
    "}\0";

const char *fshaderSource = 
    "#version 450 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

unsigned int createShaderSource() {
    signed int vertCompiled;
    signed int fragCompiled;
    signed int linked;

    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);
    glCompileShader(vShader);

    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1) {
        printf("vertex compilation failed\n");
        printShaderLog(vShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &fragCompiled);
    if (vertCompiled != 1) {
        printf("fragment compilation failed\n");
        printShaderLog(vShader);
    }

    unsigned int vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        printf("linking failed\n");
        printProgramLog(vfProgram);
    }

    return vfProgram;
}

