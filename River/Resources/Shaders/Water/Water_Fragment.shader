#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float deltaTime;


void main()
{
	vec4 _texture = texture(ourTexture, vec2(TexCoord.x + deltaTime, TexCoord.y) );
	_texture[3] = 0.7f;
	FragColor = _texture;
}