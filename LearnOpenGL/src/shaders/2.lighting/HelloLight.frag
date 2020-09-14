#version 450 core
in vec3 worldNormal;
in vec3 worldPos;

out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientStrength;
uniform int specularGloss;

void main()
{
   // ambient
   vec3 ambient = ambientStrength * objectColor;
   
   // diffuse
   vec3 worldNormal = normalize(worldNormal);
   vec3 lightDir = normalize(lightPos - worldPos);
   vec3 diffuse = max(dot(worldNormal, lightDir), 0.0) * lightColor;

   // specular phone
   vec3 viewDir = normalize(viewPos - worldPos);
   vec3 reflectDir = reflect(-lightDir, worldNormal);
   vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), specularGloss) * lightColor * 0.5;

   fragColor = vec4((ambient + diffuse + specular) * objectColor, 1.0f);
}