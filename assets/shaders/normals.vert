#version 450 core

layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Normal;

out VS_OUT
{
   vec4 normal;
   vec4 color;
} vs_out;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 transform;

void main()
{
   float sizeOfNormals = 0.15;
   gl_Position = proj_matrix * view_matrix * transform * vec4(Position.xyz,1.0);

   vs_out.normal = proj_matrix * view_matrix * transform * vec4(Position.xyz + Normal.xyz * sizeOfNormals, 1.0);
   vs_out.color = Position;
}
