#version 330 core
layout(location = 0) in vec3 positionVector;
layout(location = 1) in vec2 uvVector;

uniform mat4 mvMatrix;

out vec2 uvCoords;

void main(){
    uvCoords = uvVector;
    gl_Position = mvMatrix * vec4(positionVector, 1.0f);
}
