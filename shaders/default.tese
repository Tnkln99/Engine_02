#version 450 core

layout(triangles, equal_spacing, cw) in;
in vec3 tcPosition[];

out vec3 tePosition;
in vec4 proj_matrix_out;
in vec4 transform_out;


out vec3 tePatchDistance;

void main()
{
vec3 p0 = gl_TessCoord.x * tcPosition[0];
vec3 p1 = gl_TessCoord.y * tcPosition[1];
vec3 p2 = gl_TessCoord.z * tcPosition[2];
tePatchDistance = gl_TessCoord;
tePosition = normalize(p0 + p1 + p2);
gl_Position = proj_matrix_out * transform_out * vec4(tePosition, 1);
}
