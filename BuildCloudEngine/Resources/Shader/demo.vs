#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in vec3 vNormal;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
out vec3 viewPos;

uniform mat4 model;

layout (std140) uniform CameraData
{
    vec3 position;
    mat4 view;
    mat4 projection;
};

void main()
{
    gl_Position = projection * view * model * vec4(vPosition, 1.0);
    texCoord = vTexCoord;
    normal = mat3(transpose(inverse(model))) * vNormal;
    fragPos = vec3(model * vec4(vPosition, 1.0));
    viewPos = position;
}