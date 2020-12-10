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
uniform vec3 river_flow;


uniform float currentTime;
uniform float deltaTime;
uniform float stopTime;

float getRemainder(float num, float divisor)
{
	return (num - divisor * (num / divisor));
}

void generate(int index)
{
	// if if close to coordinate radius
	vec4 updated_coord = gs_in[index].position;

	float flow_distance = distance(river_flow, vec3(updated_coord[0], updated_coord[1], updated_coord[2]));

	float y = flow_distance + (currentTime);
	updated_coord[1] = sin(y * 0.75f);

	vec3 center = ripple_center;

	float ripple_distance = distance(center, vec3(updated_coord[0], updated_coord[1], updated_coord[2]));
	float radius = 3;

	if (currentTime < stopTime)
	{
		if (ripple_distance < radius)
		{
			float deltaY = ripple_distance + (currentTime);
			updated_coord[1] += sin(deltaY * 3);
		}
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

