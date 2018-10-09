#version 400

const int MAX_JOINTS_PER_MESH = 50;//max joints allowed in a skeleton
const int MAX_WEIGHTS_PER_VERTEX = 4;//max number of joints that can affect a vertex

//constants --------------------------------------

const int MAX_CLIP_PLANES = 6;

//---------------------------------------------------------

//Attribute Pointers --------------------------------------

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 color;
layout (location = 4) in ivec4 joint_ids;
layout (location = 5) in vec4 weights;

//---------------------------------------------------------

//Output(Varying) variables -------------------------------

out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vFragPos;
out vec4 vCol;

/* Position of the fragment relative to the light */
out vec4 vDirectionalLightSpacePosition;

out gl_PerVertex{
        vec4 gl_Position;
        float gl_ClipDistance[MAX_CLIP_PLANES];
};

//---------------------------------------------------------

//Lighting ------------------------------------------------

uniform mat4 directionalLightSpace;

//---------------------------------------------------------

//Uniform variables ---------------------------------------

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform mat3 normalMatrix;

uniform bool hasFakeLighting;
uniform int textureAtlasNumOfRows;
uniform vec2 textureAtlasOffset;

uniform vec4 clipPlanes[MAX_CLIP_PLANES];
uniform mat4 jointTransforms[MAX_JOINTS_PER_MESH];

//---------------------------------------------------------

void main(){

    /**
     * MAIN processing of our point/vertex from worldSpace -> viewSpace -> clipSpace
     * then display it.
     * */

    vec4 totalLocalPos = vec4(0.0);
    vec4 totalNormal = vec4(0.0);

    for(int i = 0; i < MAX_WEIGHTS_PER_VERTEX ; i++){

        mat4 jointTransform = jointTransforms[joint_ids[i]];

        vec4 posePosition = jointTransform * vec4(position, 1.0);
        totalLocalPos += posePosition * weights[i];

        vec4 worldNormal = jointTransform * vec4(normal, 0.0);
        totalNormal += worldNormal * weights[i];

    }

    vec4 worldPosition = model * totalLocalPos;
    vec4 viewPosition = view * worldPosition;
    vec4 clipPosition = projection * viewPosition;

    gl_Position = clipPosition;

    /**
     * Clip planes
     * */
    for (int i = 0; i < MAX_CLIP_PLANES; i++){
        gl_ClipDistance[i] = dot(worldPosition,clipPlanes[i]);
    }

    //Check for fake lighting
    vec3 actualNormal = totalNormal;
    if(hasFakeLighting){
        actualNormal = vec3(0.0,1.0,0.0);
    }

    /**
     * Calculate for texture Atlas
     * */
    vTexCoord = (texCoord/textureAtlasNumOfRows) + textureAtlasOffset;

    /**
     * Directly pass the diffuse color of each vertex
     * */
    vCol = color;

    /**
     * The normal is just a direction from the vertex. The position of the vertex is
     * the origin of the normal. If we rotate the vertex the direction might change, if
     * we scale the vertex the direction might also change, but moving the vertex will not
     * change the direction. We multiply with model to apply transformation and disable translation(moving).
     *
     * We inverse and transpose to avoid scaling skewing our normal direction, thus accounting for
     * non-uniform scaling. We then convert to mat3 to disable translation. The mat3 will multiplication
     * will return a vec3 which is what we want.
     * */
    vNormal = normalMatrix * actualNormal;

    /**
     * We need the world position of a vertex/Fragment. This is the position after transformation
     * has been applied only. The positions of other fragments will be interpolated as values are
     * sent to the fragment shader.
     *
     * We apply swizzling (vec4).xyz to get a vec3.
     * */
    vFragPos = (model * totalLocalPos).xyz;

    /**
    * We need the world position of a vertex/Fragment relative to the lights point of view
    *(thus its lightSpaceTransform).
    *
    * */
    vDirectionalLightSpacePosition = directionalLightSpace * model * totalLocalPos;
}