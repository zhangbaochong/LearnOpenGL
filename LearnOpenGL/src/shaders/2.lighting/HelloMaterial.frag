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

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float specularGloss;
};
uniform Material material;

void main()
{
   // ambient
   vec3 ambient = ambientStrength * material.ambient * lightColor;
   
   // diffuse
   vec3 worldNormal = normalize(worldNormal);
   vec3 lightDir = normalize(lightPos - worldPos);
   vec3 diffuse = max(dot(worldNormal, lightDir), 0.0) * lightColor * material.diffuse;

   // specular phone
   vec3 viewDir = normalize(viewPos - worldPos);
   vec3 reflectDir = reflect(-lightDir, worldNormal);
   vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), material.specularGloss) * lightColor * material.specular;

   fragColor = vec4(ambient + diffuse + specular, 1.0f);
}