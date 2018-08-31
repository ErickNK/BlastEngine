//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_COMMONVALUES_H
#define MORDEROPENGLUDEMYTUTORIAL_COMMONVALUES_H

#include <GL/glew.h>

const int MAX_POINT_LIGHTS = 3, MAX_SPOT_LIGHTS = 3, MAX_MATERIALS_TEXTURES = 16;

/**
 * Uniforms used
 * */
enum ShaderUniforms : unsigned int {
    MODEL_U,
    VIEW_U,
    PROJECTION_U,
    NORMAL_MATRIX_U,

    POINT_LIGHT_COUNT_U,
    SPOT_LIGHT_COUNT_U,

    CAMERA_POSITION_U,
    CAMERA_DIRECTION_U,

    NUM_UNIFORMS
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
    GLint direction_u;
    GLint edge_u;

    GLint attenuation_constant_u;
    GLint attenuation_linear_u;
    GLint attenuation_quadratic_u;
};

/**
 * Material uniforms
 * */
struct MaterialUniforms{
	GLint diffuse_texture_u[MAX_MATERIALS_TEXTURES];
	GLint specular_texture_u[MAX_MATERIALS_TEXTURES];
	GLint diffuse_texture_count_u;
	GLint specular_texture_count_u;
    GLint specular_intensity_u;
    GLint shininess_u;
};


enum TextureTypeEnum {
	DIFFUSE_TEXTURE,
	SPECULAR_TEXTURE
};
#endif //MORDEROPENGLUDEMYTUTORIAL_COMMONVALUES_H
