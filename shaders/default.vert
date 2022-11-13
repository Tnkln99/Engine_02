#version 450 core

in vec4 Position;

out VS_OUT{
   vec4 color;
} vs_out;

uniform mat4 proj_matrix;
uniform mat4 transform;

void main()
{
   gl_Position = proj_matrix * transform * Position;
   vs_out.color = Position;
}
