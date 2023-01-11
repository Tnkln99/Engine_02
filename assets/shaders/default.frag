#version 450 core

in VS_OUT
{
    vec3 normal;
    vec3 fragPos;
} fs_in;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;

#define max_light_count 5
uniform Light light[max_light_count];

uniform vec3 viewPos;

out vec4 color;

void main()
{
    vec3 result = vec3(0);
    for(int i = 0; i < max_light_count; i ++){
        // ambient
        vec3 ambient  = light[i].ambient * material.ambient;

        // diffuse
        vec3 norm = normalize(fs_in.normal.xyz);
        vec3 lightDir = normalize(light[i].position - fs_in.fragPos);
        float diff = max(dot(norm, -lightDir), 0.0);
        vec3 diffuse  = light[i].diffuse * (diff * material.diffuse);

        // specular
        vec3 viewDir = normalize(fs_in.fragPos - viewPos);
        vec3 reflectDir = reflect(lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light[i].specular * (spec * material.specular);
        result += ambient + diffuse + specular;
    }

    color = vec4(result, 1.0);
}
