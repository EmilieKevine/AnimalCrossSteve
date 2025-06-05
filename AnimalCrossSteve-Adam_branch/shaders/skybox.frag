#version 330 core



uniform samplerCube skybox;
in vec3 TexCoords;
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;   // extra in variable, since we need the light position in view space we calculate this in the vertex shader

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{   

    vec3 baseColor = lightColor;

    // Si la texture contient des données valides, on l’utilise
    vec3 texColor = texture(skybox, TexCoords).rgb;
    if (texColor != vec3(0.0)) {
        baseColor = texColor;
    }

    // ambient
    float ambient_strengh = 0.2;
    vec3 ambient = ambient_strengh * baseColor;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos); // TODO calculate light direction
    float diff = dot(norm,lightDir); // TODO calculate correct diffuse strength
    vec3 diffuse = diff * baseColor;
    
    // specular
    float specularStrength = 0.3;
    vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * baseColor;   // TODO calculate corrcet specular color

    vec3 result = (ambient + diffuse + specular); // TODO apply ambient, diffuse and specular to object color


    FragColor = vec4(result, 1.0);
    //FragColor = texture(skybox, TexCoords);
}