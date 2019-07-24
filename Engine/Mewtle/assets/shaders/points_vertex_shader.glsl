#version 330 core
layout(location = 0) in vec3 positionVector;

uniform float alphaValue;
uniform vec3 colorVector;
uniform mat4 mvpMatrix;

out vec3 positions;
out vec4 colors;

void main(){
	colors = vec4(colorVector, alphaValue);
	gl_Position = mvpMatrix * vec4(positionVector, 1.0f);
}
