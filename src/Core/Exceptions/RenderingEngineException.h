//
// Created by root on 27/10/18.
//

#ifndef BLASTENGINE_RENDERINGENGINEEXCEPTION_H
#define BLASTENGINE_RENDERINGENGINEEXCEPTION_H


#include <stdexcept>

class RenderingEngineException: public std::runtime_error {
public:
    explicit RenderingEngineException(const std::string &exception): std::runtime_error("<==== RenderingEngineException ====> " + exception){}
};

#endif //BLASTENGINE_RENDERINGENGINEEXCEPTION_H
