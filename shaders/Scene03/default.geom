#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

uniform float interp_frac;

out GS_OUT{
    vec4 color;
} gs_out;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 transform;

void make_face(vec3 a, vec3 b, vec3 c)
{
    vec3 face_normal = normalize(cross(c - a, c - b));
    vec4 face_color = vec4(0.2, 0.4, 0.2, 1.0) * (mat3(view_matrix * transform) * face_normal).z;

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
    vec3 a = gl_in[0].gl_Position.xyz;
    vec3 b = gl_in[1].gl_Position.xyz;
    vec3 c = gl_in[2].gl_Position.xyz;

    vec3 d = (a + b) * 0.5;
    vec3 e = (b + c) * 0.5;
    vec3 f = (c + a) * 0.5;

    vec3 aSphere = normalize(a);
    a = mix(a, aSphere, interp_frac);
    vec3 bSphere = normalize(b);
    b = mix(b, bSphere, interp_frac);
    vec3 cSphere = normalize(c);
    c = mix(c, cSphere, interp_frac);
    vec3 dSphere = normalize(d);
    d = mix(d, dSphere, interp_frac);
    vec3 eSphere = normalize(e);
    e = mix(e, eSphere, interp_frac);
    vec3 fSphere = normalize(f);
    f = mix(f, fSphere, interp_frac);

    make_face(a, d, f);
    make_face(d, b, e);
    make_face(e, c, f);
    make_face(d, e, f);

    EndPrimitive();
}