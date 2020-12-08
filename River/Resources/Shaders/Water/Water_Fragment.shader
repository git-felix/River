#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float deltaTime;

void main()
{
    FragColor = texture(ourTexture, TexCoord + deltaTime);
}