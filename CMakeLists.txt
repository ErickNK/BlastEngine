cmake_minimum_required(VERSION 3.12)
project(BlastEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        src/Common/math3d.cpp
        src/Physics/Colliders/AxisAlignedBoundingBox.cpp
        src/Physics/Colliders/BoundingSphere.cpp
        src/Physics/Colliders/Collider.cpp
        src/Physics/Colliders/Plane.cpp
        src/Physics/Objects/PhysicsObject.cpp
        src/Physics/PhysicsEngine.cpp
        src/Rendering/SkyBox.cpp
        src/Rendering/Camera/Camera.cpp
        src/Rendering/Lighting/DirectionalLight.cpp
        src/Rendering/Material.cpp
        src/Rendering/Mesh.cpp
        src/Rendering/Lighting/PointLight.cpp
        src/Rendering/Shaders/Shader.cpp
        src/Rendering/Lighting/SpotLight.cpp
        src/Rendering/Texture.cpp
        src/Core/Window.cpp
        src/Common/math3d.h
        src/Common/referenceCounter.h
        src/Physics/Objects/PhysicsObject.h
        src/Physics/PhysicsEngine.h
        src/Physics/Colliders/AxisAlignedBoundingBox.h
        src/Physics/Colliders/BoundingSphere.h
        src/Physics/Colliders/Collider.h
        src/Physics/Colliders/IntersectData.h
        src/Physics/Colliders/Plane.h
        src/Rendering/SkyBox.h
        src/Rendering/Camera/Camera.h
        src/Common/CommonValues.h
        src/Rendering/Lighting/DirectionalLight.h
        src/Rendering/Material.h
        src/Rendering/Mesh.h
        src/Rendering/Lighting/PointLight.h
        src/Rendering/Shaders/Shader.h
        src/Rendering/Lighting/SpotLight.h
        src/Rendering/Texture.h
        src/Rendering/Transform.h
        src/Core/Window.h
        src/Core/CoreEngine.cpp
        src/Core/CoreEngine.h
        src/Common/Time.cpp
        src/Common/Time.h
        src/Common/Util.cpp
        src/Common/Util.h
        src/Core/Game.cpp
        src/Core/Game.h
        src/Core/Input.h
        src/Rendering/RenderingEngine.cpp
        src/Rendering/RenderingEngine.h
        src/Common/ProfileTimer.h
        src/Common/ProfileTimer.cpp
        src/Rendering/Shaders/DirectionalLightShadowMapShader.cpp
        src/Rendering/Shaders/DirectionalLightShadowMapShader.h
        src/Rendering/Shaders/ForwardAmbientShader.cpp
        src/Rendering/Shaders/ForwardAmbientShader.h
        src/Rendering/Shaders/ForwardDirectionalLightShader.cpp
        src/Rendering/Shaders/ForwardDirectionalLightShader.h
        src/Rendering/Shaders/ForwardPointLightShader.cpp
        src/Rendering/Shaders/ForwardPointLightShader.h
        src/Rendering/Shaders/ForwardSpotLightShader.cpp
        src/Rendering/Shaders/ForwardSpotLightShader.h
        src/Rendering/Terrain/Terrain.cpp
        src/Rendering/Terrain/Terrain.h
        src/Rendering/Shaders/TerrainShader.cpp
        src/Rendering/Shaders/TerrainShader.h
        src/Animation/Joint.cpp
        src/Animation/Joint.h
        src/Animation/AnimatedEntity.cpp
        src/Animation/AnimatedEntity.h
        src/Rendering/Loaders/MeshedLoader.cpp
        src/Rendering/Loaders/MeshedLoader.h
        src/Rendering/Shaders/FogShader.cpp
        src/Rendering/Shaders/FogShader.h
        src/Core/Components/RenderingComponents/FogComponent.h
        src/Rendering/Fog.h
        src/Core/Entities/LightEntity.cpp
        src/Core/Entities/LightEntity.h
        src/Core/Components/RenderingComponents/LightComponent.h
        src/Core/Entities/MeshedEntity.cpp
        src/Core/Entities/MeshedEntity.h
        src/Core/Components/RenderingComponents/MeshedRendererComponent.h
        src/Core/Scene.cpp
        src/Core/Scene.h
        src/Core/Entities/EffectEntity.cpp
        src/Core/Entities/EffectEntity.h
        src/Rendering/Camera/FPSCamera.cpp
        src/Rendering/Camera/FPSCamera.h
        src/Core/Components/RenderingComponents/TerrainRendererComponent.h
        src/Core/Components/Behaviours/PlayerMovement.h
        src/Rendering/Transform.cpp
        src/Core/Components/Attachment/TPSCameraAttachment.h
        src/Rendering/Camera/TPSCamera.cpp
        src/Rendering/Camera/TPSCamera.h
        src/Core/Components/Attachment/TPSCameraAttachment.cpp
        src/Physics/Colliders/TerrainCollider.h
        src/Rendering/TextureAtlas.cpp
        src/Rendering/TextureAtlas.h
        src/Rendering/GUI/GUITexture.cpp
        src/Rendering/GUI/GUITexture.h
        src/Rendering/GUI/GUIMesh.cpp
        src/Rendering/GUI/GUIMesh.h
        src/Core/Components/RenderingComponents/GUIRendererComponent.h
        src/Core/Entities/GUIEntity.cpp
        src/Core/Entities/GUIEntity.h
        src/Rendering/GUI/GUIMaterial.cpp
        src/Rendering/GUI/GUIMaterial.h
        src/Rendering/Shaders/GUIShader.cpp
        src/Rendering/Shaders/GUIShader.h
        src/Rendering/Loaders/GUILoader.cpp
        src/Rendering/Loaders/GUILoader.h
        src/Rendering/GUI/GUICamera.cpp
        src/Rendering/GUI/GUICamera.h
        src/Core/Components/RenderingComponents/ShadowRendererComponent.h
        src/Core/Components/RenderingComponents/SkyBoxRendererComponent.h
        src/Rendering/Shaders/SkyBoxShader.h
        src/Rendering/Shaders/SkyBoxShader.cpp
        src/Core/Components/Behaviours/SkyBoxEffectsComponent.h
        src/Core/Components/EntityComponent.h
        src/Core/MousePicker.cpp
        src/Core/MousePicker.h
        src/Physics/Colliders/TerrainCollider.cpp
        src/Physics/Collisions/Collision.cpp
        src/Physics/Collisions/Collision.h
        src/Physics/Colliders/Point.cpp
        src/Physics/Colliders/Point.h
        src/Physics/Colliders/Line.cpp
        src/Physics/Colliders/Line.h
        src/Core/Entities/Entity.cpp
        src/Core/Entities/Entity.h
        src/Physics/Forces/Force.cpp
        src/Physics/Forces/Force.h
        src/Physics/Objects/RigidBody.cpp
        src/Physics/Objects/RigidBody.h
        src/Physics/Objects/TerrainBody.cpp
        src/Physics/Objects/TerrainBody.h
        src/Core/Components/Behaviours/LightRotationComponent.h
        src/Rendering/Loaders/AnimatedLoader.cpp
        src/Rendering/Loaders/AnimatedLoader.h
        src/Animation/Animation.h
        src/Animation/JointTransform.h
        src/Animation/KeyFrame.h
        src/Animation/AnimationComponent.h
        src/Rendering/Shaders/AnimationShader.cpp
        src/Rendering/Shaders/AnimationShader.h
        src/Rendering/PostProcessing/Screen.cpp
        src/Rendering/PostProcessing/Screen.h
        src/Rendering/Shaders/PostProcessingScreenShader.h
        src/Rendering/PostProcessing/FrameBufferObject.cpp
        src/Rendering/PostProcessing/FrameBufferObject.h
        src/Rendering/Primitives/Water.h
        src/Rendering/Primitives/Water.cpp
        src/Core/Components/RenderingComponents/WaterRendererComponent.h
        src/Rendering/Shaders/WaterShader.h
        src/Rendering/Lighting/Shadow.h
        src/Rendering/Camera/QuatCamera.h
        src/Animation/AnimatedMesh.cpp
        src/Animation/AnimatedMesh.h
        src/Core/Components/RenderingComponents/AnimatedRendererComponent.h
        src/Rendering/Loaders/AnimationLoader.cpp
        src/Rendering/Loaders/AnimationLoader.h
        src/Core/Components/Attachment/Attachment.h
        include/stb_image.h
        include/stb_image.c
        src/BlastEngine.h
        src/Core/Components/RenderingComponents/DifferedRenderingComponent.h
        src/Rendering/Shaders/DifferedShader.h
        src/Rendering/DifferedRendering/DifferedScreen.cpp
        src/Rendering/DifferedRendering/DifferedScreen.h
        src/Common/Helpers.h) # which files should be compiled

set(TEST_FILES
        test/TestGame/Scenes/TestScene.cpp
        test/TestGame/Scenes/TestScene.h
        test/TestGame/Scenes/ShadingScene.h
        test/TestGame/components/SphereMovement.h
        test/TestGame/TestGame.h
        test/TestGame/main.cpp src/Common/Helpers.cpp)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)


add_executable(BlastEngine ${SOURCE_FILES} ${TEST_FILES}) # which files should produce executables

target_include_directories(BlastEngine PRIVATE include)

target_link_libraries(BlastEngine ${CONAN_LIBS} ${OPENGL_LIBRARIES})