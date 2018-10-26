//
// Created by erick on 10/15/18.
//

#ifndef BLASTENGINE_HELPERS_H
#define BLASTENGINE_HELPERS_H

#include <GL/glew.h>
#include <iostream>

GLenum glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__)

#endif //BLASTENGINE_HELPERS_H
