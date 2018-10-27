//
// Created by erick on 10/21/18.
//

#include <cassert>
#include <fmt/format.h>
#include "Helpers.h"
#include "../Core/Exceptions/OpenGLException.h"

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    if ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        throw OpenGLException(fmt::format(R"(Type: "{}", Filename: "{}", Line: ({}))", error, file, line));
    }

    return errorCode;
}