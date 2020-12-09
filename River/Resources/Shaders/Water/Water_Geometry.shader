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

uniform vec3 ripple_center;
uniform float deltaTime;


void generate(int index)
{
	// if if close to coordinate radius
	vec4 updated_coord = gs_in[index].position;

	float radius = 2;
	float distance = distance(ripple_center, vec3(updated_coord[0], updated_coord[1], updated_coord[2]));
	
	if( distance <= radius ){
		float y = distance + (deltaTime * 20);
		if (y > 180)
		{
			y = 180;
		}
		updated_coord[1] = sin(y);
	}

	//updated_coord[1] += deltaTime;
	gl_Position = mvp * updated_coord;
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

