#version 330 core
layout (location = 0) in vec3 local;
layout (location = 1) in vec2 inTexCoord;

out vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() 
{
    gl_Position =  projectionMatrix * viewMatrix * modelMatrix* vec4(local, 1.0);
    texCoord = vec2(inTexCoord.x, inTexCoord.y);
}