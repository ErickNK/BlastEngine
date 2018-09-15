cmake_minimum_required(VERSION 3.12)
project(MorderOpenGLUdemyTutorial)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Common/math3d.cpp
        Physics/Colliders/AxisAlignedBoundingBox.cpp
        Physics/Colliders/BoundingSphere.cpp
        Physics/Colliders/Collider.cpp
        Physics/Colliders/Plane.cpp
        Physics/PhysicsObject.cpp
        Physics/PhysicsEngine.cpp
        Rendering/Lighting/ShadowMap.cpp
        Rendering/SkyBox.cpp
        Rendering/stb_image.c
        Rendering/Camera/Camera.cpp
        Rendering/Lighting/DirectionalLight.cpp
        Rendering/Lighting/Light.cpp
        Rendering/Material.cpp
        Rendering/Mesh.cpp
        Rendering/obj_loader.cpp
        Rendering/Lighting/PointLight.cpp
        Rendering/Shaders/Shader.cpp
        Rendering/Lighting/SpotLight.cpp
        Rendering/Texture.cpp
        Core/Window.cpp
        Common/math3d.h
        Common/referenceCounter.h
        Physics/PhysicsObject.h
        Physics/PhysicsEngine.h
        Physics/Colliders/AxisAlignedBoundingBox.h
        Physics/Colliders/BoundingSphere.h
        Physics/Colliders/Collider.h
        Physics/Colliders/IntersectData.h
        Physics/Colliders/Plane.h
        Rendering/Lighting/ShadowMap.h
        Rendering/SkyBox.h
        Rendering/stb_image.h
        Rendering/Camera/Camera.h
        Common/CommonValues.h
        Rendering/Lighting/DirectionalLight.h
        Rendering/Lighting/Light.h
        Rendering/Material.h
        Rendering/Mesh.h
        Rendering/obj_loader.h
        Rendering/Lighting/PointLight.h
        Rendering/Shaders/Shader.h
        Rendering/Lighting/SpotLight.h
        Rendering/Texture.h
        Rendering/Transform.h
        Core/Window.h
        main.cpp
        Rendering/Lighting/OmniShadowMap.cpp
        Rendering/Lighting/OmniShadowMap.h
        Core/CoreEngine.cpp Core/CoreEngine.h
        Common/Time.cpp Common/Time.h
        Common/Util.cpp Common/Util.h
        Core/Game.cpp Core/Game.h
        Core/Input.h
        Rendering/RenderingEngine.cpp Rendering/RenderingEngine.h
        Common/ProfileTimer.h Common/ProfileTimer.cpp
        Core/Components/RenderingComponents/MeshedComponent.h
        Rendering/Shaders/DirectionalLightShadowMapShader.cpp Rendering/Shaders/DirectionalLightShadowMapShader.h
        Game/SlickDriveGame.cpp Game/SlickDriveGame.h
        Rendering/Shaders/ForwardAmbientShader.cpp Rendering/Shaders/ForwardAmbientShader.h
        Rendering/Shaders/ForwardDirectionalLightShader.cpp Rendering/Shaders/ForwardDirectionalLightShader.h
        Rendering/Shaders/ForwardPointLightShader.cpp Rendering/Shaders/ForwardPointLightShader.h
        Rendering/Shaders/ForwardSpotLightShader.cpp Rendering/Shaders/ForwardSpotLightShader.h
        Rendering/Terrain/Terrain.cpp Rendering/Terrain/Terrain.h
        Rendering/Shaders/TerrainShader.cpp Rendering/Shaders/TerrainShader.h
        #        Rendering/Animation/Joint.cpp Rendering/Animation/Joint.h
#        Rendering/Animation/AnimatedGameObject.cpp Rendering/Animation/AnimatedGameObject.h
        Rendering/Loaders/MeshedLoader.cpp Rendering/Loaders/MeshedLoader.h
        Rendering/Shaders/FogShader.cpp Rendering/Shaders/FogShader.h
        Core/Components/RenderingComponents/FogComponent.h Rendering/Fog.h
        Core/Entities/LightEntity.cpp Core/Entities/LightEntity.h
        Core/Components/RenderingComponents/LightComponent.h
        Core/Entities/MeshedEntity.cpp Core/Entities/MeshedEntity.h
        Core/Components/RenderingComponents/MeshedRendererComponent.h
        Core/Scene.cpp Core/Scene.h
        Game/Scenes/TestScene.cpp Game/Scenes/TestScene.h Core/Entities/EffectEntity.cpp Core/Entities/EffectEntity.h Core/Components/RenderingComponents/EffectComponent.h Rendering/Camera/FPSCamera.cpp Rendering/Camera/FPSCamera.h Core/Components/RenderingComponents/TerrainRendererComponent.h Core/Components/Behaviours/PlayerMovement.h Rendering/Transform.cpp Core/Components/Attachment/TPSCameraAttachment.h Rendering/Camera/TPSCamera.cpp Rendering/Camera/TPSCamera.h Core/Components/Attachment/TPSCameraAttachment.cpp Core/Components/CollusionDetection/TerrainCollusionDetection.h Rendering/TextureAtlas.cpp Rendering/TextureAtlas.h) # which files should be compiled

add_executable(MorderOpenGLUdemyTutorial ${SOURCE_FILES}) # which files should produce executables

# ASSIMP
find_package(ASSIMP REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIR})
link_directories(${ASSIMP_LIBRARY_DIRS})
if(NOT ASSIMP_FOUND)
    message(ERROR "ASSIMP not found!")
endif(NOT ASSIMP_FOUND)

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
link_directories(${GLEW_LIBRARY_DIRS})
if(NOT GLEW_FOUND)
    message(ERROR "GLEW not found!")
endif(NOT GLEW_FOUND)

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIR})
link_directories(${GLFW_LIBRARY_DIRS})
if(NOT GLFW_FOUND)
    message(ERROR "GLFW not found!")
endif(NOT GLFW_FOUND)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)

target_link_libraries(MorderOpenGLUdemyTutorial ${GLFW_LIBRARIES} ${ASSIMP_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})