#version 450 core

in VS_OUT
{
    vec2 texCoord;
    vec3 normal;
    vec3 fragPos;
    vec4 fragPosLightSpace;
} fs_in;

struct Light {
    vec3 position;
    vec3 color;
};

out vec4 FragColor;

// material information
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float shininess;

uniform layout (binding=0) sampler2D texture_diffuse1;
uniform layout (binding=1) sampler2D texture_specular1;

uniform int diffuseTextureUsing=0;
uniform int specularTextureUsing=0;

uniform vec3 viewPos;

#define max_light_count 5
uniform Light light[max_light_count];

layout (binding=2) uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir, vec3 normal)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main()
{
    vec3 result = vec3(0);
    for(int i = 0; i < max_light_count; i ++){
        // ambient
        vec3 ambient  = light[i].color * ambient;

        // diffuse
        vec3 norm = normalize(fs_in.normal.xyz);
        vec3 lightDir = normalize(light[i].position - fs_in.fragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light[i].color * (diff * diffuse);
        if(diffuseTextureUsing == 1) {
            diffuse = light[i].color * (diff * vec3(texture(texture_diffuse1, fs_in.texCoord)));
        }

        // specular
        vec3 viewDir = normalize(viewPos - fs_in.fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        vec3 specular = light[i].color * (spec * specular);
        if(specularTextureUsing == 1) {
            specular = light[i].color * (spec * vec3(texture(texture_specular1, fs_in.texCoord)));
        }

        // to test phong shader:
        //result += ambient + diffuse + specular;
        // for shadow mapping
        float shadow = ShadowCalculation(fs_in.fragPosLightSpace, lightDir, norm);
        //result += ambient + (1.0 - shadow) * (diffuse + specular);
        result += ambient + (1.0 - shadow) * (diffuse + specular);
        //for normal mapping:
        //result = fs_in.normal * 0.5 + 0.5;
    }
    FragColor = vec4(result,1.0f);
    //FragColor = texture(texture_diffuse1, fs_in.texCoord);
}
