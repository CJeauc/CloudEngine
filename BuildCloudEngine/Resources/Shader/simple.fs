#version 330 core

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec3 viewPos;

in vec3 lposition;
in vec3 ldiffuse;

out vec4 fragColor;

uniform sampler2D diffuseTex;
uniform sampler2D specularTex;

void main()
{
    vec3 lightPos = lposition;
    vec3 lightColor = ldiffuse;
    float ambientStrength = 0.5f;           //should be uniform buffer world
    float specularStrength = texture(specularTex, texCoord).r;
    float shininess = 2;                   //Should Comes from material

    /*Diffuse*/
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * texture(diffuseTex, texCoord).rgb;

    /*Specular*/
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;


    vec3 ambient = ambientStrength * texture(diffuseTex, texCoord).rgb;
    vec3 result = (ambient + diffuse + specular);
    fragColor = vec4(result, 1);
}