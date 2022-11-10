#version 330 core

in vec3 position;

out VS_OUT
{
   vec4 color;
} vs_out;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;


void main(void)
{
   gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0f);
   vs_out.color = vec4(position, 1.0f) * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
   //vs_out.color = vec4(0.3,0.7,0.2,1);
}
