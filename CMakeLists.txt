cmake_minimum_required(VERSION 2.8)

if(WIN32)
	set(VULKAN_SDK_PATH D:/VulkanSDK/1.0.51.0)
	set(GLM_PATH D:/glm )
	set(GLFW3_PATH D:/glfw-3.2.1.bin.WIN64 )
else()
	set(VULKAN_SDK_PATH /home/dan/VulkanSDK/1.0.46.0/x86_64)
	set(GLM_PATH "")
	set(GLFW3_PATH "" )
endif()


project(get-image-spv)

if (UNIX)
	find_package(glfw3 REQUIRED)
	find_package(glm REQUIRED)
endif (UNIX)

link_directories(${VULKAN_SDK_PATH}/lib ${GLFW3_PATH}/lib-vc2015 )

add_executable(get_image_spv main.cpp lodepng.cpp)

if(WIN32)
    target_link_libraries(get_image_spv glfw3 vulkan-1)
else()
    target_link_libraries(get_image_spv glfw vulkan)
endif()


target_compile_definitions(get_image_spv PUBLIC )
target_include_directories(get_image_spv PUBLIC ${VULKAN_SDK_PATH}/include ${GLFW3_PATH}/include ${GLM_PATH} )

install(TARGETS get_image_spv
    DESTINATION bin
)


set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS )
