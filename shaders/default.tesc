#version 450 core

layout(vertices = 3) out;

in vec3 vPosition[];
out vec3 tcPosition[];

void main()
{
    tcPosition[gl_InvocationID] = vPosition[gl_InvocationID];
    if (gl_InvocationID == 0) {
        gl_TessLevelInner[0] = 4.0;
        gl_TessLevelOuter[0] = 4.0;
        gl_TessLevelOuter[1] = 4.0;
        gl_TessLevelOuter[2] = 4.0;
    }
}