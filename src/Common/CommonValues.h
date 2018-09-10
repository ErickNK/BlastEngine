//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_COMMONVALUES_H
#define MORDEROPENGLUDEMYTUTORIAL_COMMONVALUES_H

#include <GL/glew.h>
#include "../Rendering/stb_image.h"

const int MAX_POINT_LIGHTS = 3, 
	MAX_SPOT_LIGHTS = 3, 
	MAX_MATERIALS_TEXTURES = 3, 
	MAX_GLOBAL_TEXTURE_UNITS = 16, 
	MAX_DRAWING_TEXTURE_UNITS = 16;

/**
 * Uniforms used
 * */
enum ShaderType{
	BASIC_SHADER,

	DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER,
	OMNI_DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER,
	SKY_BOX_SHADER,

	FORWARD_AMBIENT_SHADER,
    FORWARD_DIRECTIONAL_LIGHT_SHADER,
    FORWARD_POINT_LIGHT_SHADER,
    FORWARD_SPOT_LIGHT_SHADER,

	FOG_SHADER,

	NUM_SHADER_TYPES
};

enum LightType{
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    SPOT_LIGHT,

    NUM_LIGHT_TYPES
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

	GLint shadow_map_u;
	GLint light_space_u;
};

/**
 * All point light uniforms that shader holds
 * */
struct PointLightUniforms{
    LightUniforms base;

    GLint position_u;

	GLint shadow_map_u;
	GLint light_space_u;

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

	GLint shadow_map_u;
	GLint light_space_u;

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
