#version 450 core

layout (location = 0) in vec4 Position;

out VS_OUT
{
    vec4 color;
} vs_out;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 transform;

uniform vec3 light_color;

void main()
{
    gl_Position = proj_matrix * view_matrix * transform * vec4(Position.xyz,1.0);
    vs_out.color = vec4(light_color,1);
}