#version 330 core

out vec4 color;
in vec4 var_color;

uniform vec4 u_Color;

void main()
{
	color = vec4(0.0f, 1.0f, 1.0f, 1.0f);
	//color = var_color;
	//discard;
};