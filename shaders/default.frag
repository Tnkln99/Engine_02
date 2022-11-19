#version 450 core

in TES_OUT{
    vec4 color;
}fs_in;

out vec4 color;

void main()
{
    color = fs_in.color;
}