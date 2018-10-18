//
// Created by erick on 8/24/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_COMMONVALUES_H
#define MORDEROPENGLUDEMYTUTORIAL_COMMONVALUES_H

#include <string>
#include <GL/glew.h>
#include <stb_image.h>

const int
	MAX_MATERIALS_TEXTURES = 3, 
	MAX_GLOBAL_TEXTURE_UNITS = 16, 
	MAX_DRAWING_TEXTURE_UNITS = 16,
    MAX_CLIP_PLANES = 6,
    MAX_JOINTS_PER_VERTEX = 3,
    MAX_JOINTS_PER_MESH = 50,
    MAX_DIRECTIONAL_LIGHTS = 3,
    MAX_POINT_LIGHTS = 3,
    MAX_SPOT_LIGHTS = 3;

const std::string SHADER_DIRECTORY = "../res/shaders/";

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
    WATER_SHADER,
    TERRAIN_SHADER,
    GUI_SHADER,
    POST_PROCESSING_SCREEN_SHADER,
    DIFFERED_GEOMETRYPASS_RENDERING_SHADER,
    DIFFERED_LIGHTPASS_RENDERING_SHADER,

    NO_SHADER,

	NUM_SHADER_TYPES
};

enum LightType{
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    SPOT_LIGHT,

    NUM_LIGHT_TYPES
};

enum TextureTypeEnum {
    SHADOW_MAP_TEXTURE,
	DIFFUSE_TEXTURE,
	DIFFUSE_TEXTURE_ATLAS,
	SPECULAR_TEXTURE,
	SPECULAR_TEXTURE_ATLAS,
    MATERIAL_TEXTURE,
    POSITION_TEXTURE,
    DEPTH_TEXTURE,
	BACKGROUND_TEXTURE,
	R_TEXTURE,
	G_TEXTURE,
	B_TEXTURE,
	BLEND_MAP_TEXTURE,
	HEIGHT_MAP_TEXTURE,
	GUI_TEXTURE,
	WATER_REFLECTION_TEXTURE,
	WATER_REFRACTION_TEXTURE,
	WATER_REFRACTION_DEPTH_TEXTURE,
	WATER_REFLECTION_DEPTH_BUFFER,
	DU_DV_MAP,
    NORMAL_MAP
};

enum SkyBoxTypes: unsigned int{
	DAY_SKYBOX,
	NIGHT_SKYBOX,

	NUM_SKYBOX_TYPES
};

enum ColliderType{
    TYPE_BOUNDINGSPHERE,
    TYPE_AABB,
    TYPE_PLANE,
    TYPE_TERRAIN,
    TYPE_POINT,
    TYPE_LINE,

    NUM_TYPES
};

enum ComponentTypes{
	MESHED_RENDERER_COMPONENT,
	RIGID_BODY_COMPONENT,
	PLAYER_MOVEMENT,
	FOG_COMPONENT,
	GUI_RENDERER_COMPONENT,
	LIGHT_COMPONENT,
	SHADOW_RENDERER_COMPONENT,
	SKYBOX_RENDERER_COMPONENT,
	TERRAIN_RENDERER_COMPONENT,
	SKYBOX_EFFECTS_COMPONENT,
	TPS_CAMERA_ATTACHEMENT,
    TERRAIN_BODY_COMPONENT,
    ANIMATION_COMPONENT,
    ANIMATED_RENDERER_COMPONENT,
    WATER_RENDERER_COMPONENT,

    LIGHT_ROTATION_COMPONENT,

	NONE,

	NUM_COMPONENT_TYPES
};


enum FBO_Options{
    TYPE,
    TEXTURE_TYPE,
    RENDER_BUFFER_TYPE,
    INTERNAL_COMPONENT_FORMAT,
    EXTERNAL_COMPONENT_FORMAT,
    DATA_VALUE_FORMAT,
    ATTACHMENT_TYPE,
    ENABLE_WRAP_FILTER,
    WRAP_FILTER,
    ENABLE_OVERLAY_FILTER,
    OVERLAY_FILTER,
    HEIGHT,
    WIDTH,

    NUM_FBO_OPTIONS
};

/**
 * Buffers
 * */
enum MeshBuffers{
    POSITION_VB,
    NORMAL_VB,
    TEXCOORD_VB,
    COLOR_VB,
    INDEX_VB,
    JOINT_IDS_VB,
    JOINT_WEIGHTS_VB,
    NUM_BUFFERS
};

enum MaterialOptions{
    TRANSPARENCY,
    FAKE_LIGHTING,

    NUM_MATERIAL_OPTIONS
};
#endif //MORDEROPENGLUDEMYTUTORIAL_COMMONVALUES_H
