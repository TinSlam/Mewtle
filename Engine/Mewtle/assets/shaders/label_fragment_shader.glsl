#version 330 core

in vec2 uvCoords;
out vec4 outputColor;

uniform sampler2D textureSampler;

void main(){
    outputColor = texture(textureSampler, uvCoords).rgba;
}