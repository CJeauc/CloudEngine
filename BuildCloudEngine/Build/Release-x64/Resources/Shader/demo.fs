#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec3 viewPos;


out vec4 fragColor;

uniform sampler2D diffuseTex;
uniform sampler2D specularTex;

void main()
{
    fragColor = vec4((normal * 0 + fragPos * 0 + viewPos * 0), 1);
    fragColor = mix(texture(diffuseTex, texCoord), texture(specularTex, texCoord), 0.2);
}