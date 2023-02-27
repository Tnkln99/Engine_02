#version 450 core

layout(triangles) in;

// Three lines will be generated: 6 vertices
layout(line_strip, max_vertices=6) out;

in VS_OUT
{
    vec4 normal;
    vec4 color;
} gs_in[];

out GS_OUT
{
    vec4 color;
} gs_out;


void main()
{
    for(int i=0; i< gl_MaxPatchVertices; i++)
    {
        gl_Position = gl_in[i].gl_Position;
        gs_out.color = vec4(0,0,1,1);
        EmitVertex();

        gl_Position =  gs_in[i].normal;
        gs_out.color = vec4(1,1,1,0);
        EmitVertex();

        EndPrimitive();
    }
}