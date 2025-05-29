#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
in vec3 position;

out vec2 frag_tex_coords;

void main() {
    gl_Position = projection * view * model * vec4(position, 1);
    


    // Calculating spherical texture coordinates
    //There's a bug on a meridian that I haven't managed to correct
    vec3 normPos = normalize(position);
    const float pi = 3.14159265359;
    
    // Calculating longitude (u) with atan
    float u = 0.5 - atan(normPos.z, normPos.x) / (2.0 * pi);
    
    // Calculating latitude (v)
    float v = 0.5 - asin(normPos.y) / pi; 
  
    
    frag_tex_coords = vec2(u, v);

    //Basic version :
    //frag_tex_coords = position.xy;
}