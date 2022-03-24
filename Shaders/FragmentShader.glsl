#version 330 core
in vec2 texCoord;

uniform sampler2D uTexture1;

out vec4 color;

void main() 
{
    color = texture(uTexture1, texCoord);
}