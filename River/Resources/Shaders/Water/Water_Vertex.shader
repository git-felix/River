#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 var_color;
uniform mat4 mvp;

void main()
{
	var_color = color;
	gl_Position = mvp * position;
};