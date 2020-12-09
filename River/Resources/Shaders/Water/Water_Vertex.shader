#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

// sends out to the geometry shader
out VS_OUT{
	vec2 TexCoord;
	vec4 position;
} vs_out;


void main()
{
    //gl_Position = mvp * vec4(aPos, 1.0);
    vs_out.position = vec4(aPos, 1.0f);
	vs_out.TexCoord = aTexCoord;
	//TexCoord = aTexCoord;
	//vs_out.position = aPos;
}