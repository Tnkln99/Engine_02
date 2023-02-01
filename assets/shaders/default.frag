#version 450 core

in VS_OUT
{
    vec3 normal;
    vec3 fragPos;
    vec4 fragPosLightPos;
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

uniform sampler2D shadowMap;

out vec4 color;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

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
        float shadow = ShadowCalculation(fs_in.fragPosLightPos);
        //result += (ambient + (1.0 - shadow) * (diffuse + specular));
        result += ambient + diffuse + specular;
    }

    color = vec4(result, 1.0);
}
