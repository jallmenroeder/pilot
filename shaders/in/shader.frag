
#version 450

layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(inNormal, 1.0);
//    outColor = vec4(inTexCoord, 1.0, 1.0);
//    outColor = vec4(1., 0., 0., 1.0);
}
