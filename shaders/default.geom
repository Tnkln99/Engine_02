#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

out GS_OUT{
    vec4 color;
}gs_out;

uniform float stretch = 0.7;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 transform;


void make_face(vec3 a, vec3 b, vec3 c)
{
    vec3 face_normal = normalize(cross(c - a, c - b));
    vec4 face_color = vec4(face_normal, 1.0);

    gl_Position = proj_matrix * view_matrix * transform * vec4(a, 1.0);
    gs_out.color = face_color;
    EmitVertex();

    gl_Position = proj_matrix * view_matrix * transform * vec4(b, 1.0);
    gs_out.color = face_color;
    EmitVertex();

    gl_Position = proj_matrix * view_matrix * transform * vec4(c, 1.0);
    gs_out.color = face_color;
    EmitVertex();

    EndPrimitive();
}

void main(void)
{
    int n;
    vec3 a = gl_in[0].gl_Position.xyz;
    vec3 b = gl_in[1].gl_Position.xyz;
    vec3 c = gl_in[2].gl_Position.xyz;

    vec3 d = (a + b) * stretch;
    vec3 e = (b + c) * stretch;
    vec3 f = (c + a) * stretch;

    a *= (2.0 - stretch);
    b *= (2.0 - stretch);
    c *= (2.0 - stretch);

    make_face(a, d, f);
    make_face(d, b, e);
    make_face(e, c, f);
    make_face(d, e, f);

    EndPrimitive();
}