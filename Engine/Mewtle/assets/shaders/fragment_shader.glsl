#version 330 core

in vec3 positions;
in vec3 normals;
in vec2 uvCoords;

out vec4 outputColor;

uniform sampler2D textureSampler;
uniform mat4 mvMatrix;
uniform vec3 lightPosition;
uniform float ambientLighting;
uniform int lightingFlag;
uniform float lightPower;
uniform float alphaValue;

void main(){
    if(lightingFlag == 1){
        float distance = length(lightPosition - positions);

        vec3 lightVector = normalize(lightPosition - positions);

        float diffuse = max(dot(normals, lightVector), 0.0);
        diffuse = diffuse * (1.0 / (1.0 + (distance / lightPower / 24)));
        diffuse = diffuse + ambientLighting;

        outputColor = (diffuse * texture(textureSampler, uvCoords)).rgba;
    }else{
		if(alphaValue == 1){
			outputColor = texture(textureSampler, uvCoords).rgba;
		}else{
			outputColor = vec4(texture(textureSampler, uvCoords).rgb, alphaValue);
		}
    }
}