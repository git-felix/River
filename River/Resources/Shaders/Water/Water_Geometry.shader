#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT
{
	vec2 TexCoord;
	vec4 position;
} gs_in[];

uniform mat4 mvp;
out vec2 TexCoord;

void generate(int index)
{
	gl_Position = mvp * gs_in[index].position;
	TexCoord = gs_in[index].TexCoord;
	EmitVertex();
}

void main()
{
	for (int i = 0; i < gs_in.length(); i++)
	{
		generate(i);
	}
	EndPrimitive();
}

