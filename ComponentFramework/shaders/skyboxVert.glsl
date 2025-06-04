#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec4 inVertex;

layout(location = 0) uniform mat4 projectionMatrix;
layout(location = 1) uniform mat4 orientationMatrix;

out vec3 textureCoords;


void main() {
    textureCoords = vec3(inVertex);

    gl_Position = projectionMatrix * orientationMatrix * inVertex;
}