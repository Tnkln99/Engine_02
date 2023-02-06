#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out VS_OUT
{
    vec3 normal;
    vec3 fragPos;
    vec4 fragPosLightSpace;
} vs_out;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 transform;
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = proj_matrix * view_matrix * transform * vec4(aPos,1);
    vs_out.fragPosLightSpace = lightSpaceMatrix * transform * vec4(aPos, 1.0);
    vs_out.normal = mat3(transpose(inverse(transform))) * aNorm;
    vs_out.fragPos = vec3(transform * vec4(aPos, 1.0));
}
