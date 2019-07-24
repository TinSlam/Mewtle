#version 330 core

in vec3 positions;
in vec4 colors;

out vec4 outputColor;

void main(){
	outputColor = colors;
}