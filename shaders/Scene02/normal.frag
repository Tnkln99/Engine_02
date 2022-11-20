#version 450 core

in GS_OUT
{
    vec4 color;
} fs_in;
in vec4 vertex_color;

out vec4 color;

void main()
{
    color = fs_in.color;
}
