﻿# CMakeList.txt : CMake project for enerMesh, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10.2)

PROJECT(VulkanQuickStartLib)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}")


find_package (Vulkan)

if (UNIX)
    include_directories(
	    "include"
	    "vk_base"
	    "/usr/include/"
	    "/usr/include/freetype2/"
	    "../ThirdParty/glm-0.9.9.5/glm"
	    "../ThirdParty/glfw-3.3.2/include"
	    "../ThirdParty/tinyobjloader"
	    "/usr/local/include/eigen3/"
	    "../ThirdParty/stb"
	    "${Vulkan_INCLUDE_DIRS}"
	    "../triMesh/triMesh/include"
	    "../triMesh/stlReader/include"
    )

    list(APPEND CMAKE_CXX_FLAGS "-pthread -fPIC")
    set(GLSL_VALIDATOR "glslangValidator")
    add_definitions(-DGLFW_EXPOSE_NATIVE_X11 -D_GCC)
    set(GLFW_LIB_DIR "/usr/lib/x86_64-linux-gnu/")
    set(GLFW_LIB_NAME "glfw")
else(UNIX)
	#turn export declaration on for windows

    include_directories(
	    "include"
	    "vk_base"
	    "/usr/include/"
	    "../ThirdParty/freetype-2.10.2/include"
	    "../ThirdParty/glm-0.9.9.5/glm"
	    "../ThirdParty/glfw-3.3.2/include"
	    "../ThirdParty/tinyobjloader"
	    "../ThirdParty/eigen"
	    "../ThirdParty/stb"
	    "${Vulkan_INCLUDE_DIRS}"
	    "../triMesh/triMesh/include"
	    "../triMesh/stlReader/include"
    )

    set(GLSL_VALIDATOR "/VulkanSDK/1.2.170.0/Bin32/glslangValidator.exe")
    add_definitions(-DGLFW_EXPOSE_NATIVE_WIN32 -DVK_USE_PLATFORM_WIN32_KHR -D_WIN32 -DVQS_EXPORT_DEF -DVK_PROTOTYPES -DNOMINMAX)
    set(GLFW_LIB_DIR "../ThirdParty/glfw-3.3.2/lib-vc2019")
    set(FREE_TYPE_LIB_DER "../ThirdParty/freetype-2.10.2/x64/Release Static")
    set(GLFW_LIB_NAME "glfw3")
endif(UNIX)

set(CONFIG "x64-${CMAKE_BUILD_TYPE}")

if(${CMAKE_BUILD_TYPE} MATCHES "Release")
add_compile_definitions(VQS_RELEASE_BUILD)
endif()

link_directories (
"${GLFW_LIB_DIR}"
"${FREE_TYPE_LIB_DER}"
"../triMesh/${CMAKE_BUILD_TYPE}/"
)

add_library (
VulkanQuickStartLib SHARED
"src/tinyObjLoader.cpp"
"vk_base/VulkanTools.cpp"
"src/vk_app.cpp"
"src/vk_buffer.cpp"
"src/vk_computeStep.cpp" 
"src/vk_deviceContext.cpp"
"src/vk_image.cpp"
"src/vk_imageCopier.cpp" 
"src/vk_logger.cpp"  
"src/vk_modelPNC3f.cpp"  
"src/vk_modelPNCT3f.cpp"
"src/vk_offscreenPassBase.cpp"  
"src/vk_pipelineBase.cpp"

"src/vk_pipelinePNC3f.cpp"
"src/vk_pipelineUi.cpp"
"src/vk_pipelinePNCT3f.cpp"
"src/vk_pipelineUboGroup.cpp" 
"src/vk_pipelineUboGroupBase.cpp"
"src/vk_sceneNodeBase.cpp"
"src/vk_sceneNodePNC3f.cpp"
"src/vk_sceneNodePNCT3f.cpp"
"src/vk_sceneNodeUi.cpp"
"src/vk_shaderPool.cpp"
"src/vk_textureImage.cpp"
"src/vk_vertexTypes.cpp" 
"src/vk_ui_button.cpp" 
"src/vk_transformFunc.cpp"
"src/vk_ui_window.cpp"
"src/vk_sceneNodeImageProc.cpp"
"src/vk_main.cpp" "src/tinyObjLoader.cpp")

target_compile_features(VulkanQuickStartLib PRIVATE cxx_std_17)

target_link_libraries("VulkanQuickStartLib" 
PUBLIC Vulkan::Vulkan
PRIVATE triMesh
PRIVATE stlReader
PRIVATE freetype
PRIVATE ${GLFW_LIB_NAME}
)

# TODO: Add tests and install targets if needed.
