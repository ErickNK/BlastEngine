//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_COMMONVALUES_H
#define MORDEROPENGLUDEMYTUTORIAL_COMMONVALUES_H

#include <GL/glew.h>

const int MAX_POINT_LIGHTS = 3, MAX_SPOT_LIGHTS = 100;

/**
 * Uniforms used
 * */
enum ShaderUniforms : unsigned int {
    MODEL_U,
    VIEW_U,
    PROJECTION_U,

    SPECULAR_INTENSITY_U,
    SPECULAR_SHININESS_U,

    POINT_LIGHT_COUNT_U,
    SPOT_LIGHT_COUNT_U,

    CAMERA_POSITION_U,

    NUM_UNIFORMS
};

/**
 * Uniforms used
 * */
enum ShaderTypes : unsigned int {
    VERTEX_SHADER,
    FRAGMENT_SHADER,
    GEOMETRY_SHADER,

    NUM_SHADERS
};

/**
 * Base for light uniforms
 * */
struct LightUniforms{
    GLint color_u;
    GLint ambient_intensity_u;
    GLint diffuse_intensity_u;
};

/**
 * Base for light uniforms
 * */
struct DirectionalLightUniforms{
    LightUniforms base;

    GLint direction_u;
};

/**
 * All point light uniforms that shader holds
 * */
struct PointLightUniforms{
    LightUniforms base;

    GLint position_u;

    GLint attenuation_constant_u;
    GLint attenuation_linear_u;
    GLint attenuation_quadratic_u;

};

/**
 * All spot light uniforms that shader holds
 * */
struct SpotLightUniforms{
    LightUniforms base;

    GLint position_u;

    GLint attenuation_constant_u;
    GLint attenuation_linear_u;
    GLint attenuation_quadratic_u;
};

#endif //MORDEROPENGLUDEMYTUTORIAL_COMMONVALUES_H
