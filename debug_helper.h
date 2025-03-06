#include <glad/glad.h>
#include <iostream>

GLenum glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__)

void errorHandler();
void APIENTRY errorHandler(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar *msg, const void *data);
