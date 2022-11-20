#version 450 core

layout(vertices = 3) out;

uniform float innerTess;
uniform float outerTess;

void main()
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    if (gl_InvocationID == 0) {
        gl_TessLevelInner[0] = innerTess;
        gl_TessLevelOuter[0] = outerTess;
        gl_TessLevelOuter[1] = outerTess;
        gl_TessLevelOuter[2] = outerTess;
    }
}