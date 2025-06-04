#version 330 core

uniform samplerCube skybox;
in vec3 TexCoords;
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{   
    // Couleur de base provenant de la texture
    vec3 texColor = texture(skybox, TexCoords).rgb;
    
    // Calcul de l'éclairage
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    float specularStrength = 0.3;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    // Combinaison de la texture et de l'éclairage
    vec3 result = (ambient + diffuse + specular) * texColor;
    
    FragColor = vec4(result, 1.0);
}