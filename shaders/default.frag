#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D diffuse_map;
uniform vec3 materialColor;
uniform vec3 lightPos = vec3(0.0, 1.0, 0.0);
uniform vec3 viewPos = vec3(0.0, 0.0, 3.0);

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 baseColor = materialColor;

    // Si la texture contient des données valides, on l’utilise
    vec3 texColor = texture(diffuse_map, TexCoords).rgb;
    if (texColor != vec3(0.0)) {
        baseColor = texColor;
    }

    // specular
    float specularStrength = 0.3;
    vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * baseColor;   // TODO calculate corrcet specular color

    vec3 ambient = 0.2 * baseColor;
    vec3 diffuse = diff * baseColor;
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}
