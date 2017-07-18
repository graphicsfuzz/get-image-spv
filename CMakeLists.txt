cmake_minimum_required(VERSION 2.8)
set(VULKAN_SDK_PATH /home/dan/VulkanSDK/1.0.46.0/x86_64)

project(get-image-spv)
# -- Build dependencies -- #
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/deps)
execute_process(
COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} ${CMAKE_SOURCE_DIR}/deps -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/deps
)
execute_process(
COMMAND ${CMAKE_COMMAND} --build . --config ${CMAKE_BUILD_TYPE}
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/deps
)
execute_process(
COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=../install -DBUILD_TYPE=${CMAKE_BUILD_TYPE} -P cmake_install.cmake
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/deps
)
# -- End build dependencies -- #


find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

link_directories(${VULKAN_SDK_PATH}/lib)

add_executable(get_image_spv main.cpp lodepng.cpp)
target_link_libraries(get_image_spv  glfw vulkan)
target_compile_definitions(get_image_spv PUBLIC -DNDEBUG)
target_include_directories(get_image_spv PUBLIC ${VULKAN_SDK_PATH}/include)

install(TARGETS get_image_spv
    DESTINATION bin
)


set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS )
