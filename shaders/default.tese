#version 450 core
layout(triangles, equal_spacing, cw) in;

out TES_OUT{
    vec3 patchDistance;
    vec3 normalisedPos;
}tes_out;



void main()
{
    vec4 p0 = gl_TessCoord.x * gl_in[0].gl_Position;
    vec4 p1 = gl_TessCoord.y * gl_in[1].gl_Position;
    vec4 p2 = gl_TessCoord.z * gl_in[2].gl_Position;
    vec4 pos = normalize(p0 + p1 + p2);
    // setting things up
    gl_Position = pos;
}