//
// Created by root on 27/10/18.
//

#ifndef BLASTENGINE_OPENGLEXCEPTION_H
#define BLASTENGINE_OPENGLEXCEPTION_H


#include <stdexcept>

class OpenGLException: public std::runtime_error {
public:
    explicit OpenGLException(const std::string &exception): std::runtime_error("<==== OpenGLException ====> " + exception){}
};


#endif //BLASTENGINE_OPENGLEXCEPTION_H
