#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 0, binding = 0) uniform UniformBufferObject0 {
	float r;
} ubo0;

layout(set = 0, binding = 1) uniform UniformBufferObject1 {
	float g;
} ubo1;

layout(set = 0, binding = 2) uniform UniformBufferObject2 {
	float b;
} ubo2;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(ubo0.r, ubo1.g, ubo2.b, 1.0);
}
