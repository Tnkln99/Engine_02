#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoord;

out VS_OUT
{
    vec2 texCoord;
    vec3 normal;
    vec3 fragPos;
    vec4 fragPosLightSpace;
} vs_out;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 lightSpaceMatrix;

void main()
{
    vs_out.fragPosLightSpace = lightSpaceMatrix * modelMatrix * vec4(aPos, 1.0);
    vs_out.normal = mat3(transpose(inverse(modelMatrix))) * aNorm;
    vs_out.fragPos = vec3(modelMatrix * vec4(aPos, 1.0));
    vs_out.texCoord = aTexCoord;
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(aPos,1);
}
