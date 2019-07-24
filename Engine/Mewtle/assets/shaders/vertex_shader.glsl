#version 330 core
layout(location = 0) in vec3 positionVector;
layout(location = 1) in vec3 normalVector;
layout(location = 2) in vec2 uvVector;

uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;

out vec3 positions;
out vec3 normals;
out vec2 uvCoords;

void main(){
    positions = vec3(mvMatrix * vec4(positionVector, 1.0f));
    normals = vec3(mvMatrix * vec4(normalVector, 0.0f));
    uvCoords = uvVector;
    gl_Position = mvpMatrix * vec4(positionVector, 1.0f);
}
