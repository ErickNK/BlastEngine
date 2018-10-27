//
// Created by root on 27/10/18.
//

#ifndef BLASTENGINE_SHADEREXCEPTION_H
#define BLASTENGINE_SHADEREXCEPTION_H


#include <stdexcept>

class ShaderException: public std::runtime_error {
public:
    explicit ShaderException(const std::string &exception): std::runtime_error("<==== ShaderException ====> " + exception){}
};


#endif //BLASTENGINE_SHADEREXCEPTION_H
