#version 450 core
layout(triangles, equal_spacing, cw) in;

out TES_OUT{
    vec4 color;
}tes_out;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 transform;

void main()
{
    vec4 p0 = gl_TessCoord.x * gl_in[0].gl_Position;
    vec4 p1 = gl_TessCoord.y * gl_in[1].gl_Position;
    vec4 p2 = gl_TessCoord.z * gl_in[2].gl_Position;

    vec4 pos = normalize(p0 + p1 + p2);
    gl_Position = proj_matrix * view_matrix * transform * pos;

    tes_out.color = pos;
}