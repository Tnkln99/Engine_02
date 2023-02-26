#version 450 core
#define MAX_LIGHT_COUNT 10

in VS_OUT
{
    vec2 texCoord;
    vec3 normal;
    vec3 fragPos;
    vec4 fragPosLightSpace[MAX_LIGHT_COUNT];
    int lightCount;
} fs_in;

struct Light {
    vec3 position;
    vec3 color;
    sampler2D shadowMap;
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


uniform Light light[MAX_LIGHT_COUNT];

// shadow = 1 if no shadow (result * 1 = result)
float ShadowCalculation(sampler2D shadowMap, vec4 fragPosLightSpace, vec3 lightDir, vec3 normal)
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
    // PCF some sort of gradiation
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0) {
        shadow = 0.0;
    }
    return shadow;
}

void main()
{
    vec3 radiance = vec3(0);
    float shadow = 1.0;
    for(int i = 0; i < MAX_LIGHT_COUNT; i++){
        vec3 norm = normalize(fs_in.normal.xyz);
        vec3 lightDir = normalize(light[i].position); // all the lights looking at point 0,0,0
        shadow *= (1 - ShadowCalculation(light[i].shadowMap, fs_in.fragPosLightSpace[i], lightDir, norm));
        vec3 lightIntensity = light[i].color * max(dot(norm, lightDir), 0.0);

        // diffuse
        vec3 diffuseTerm = diffuse;
        if(diffuseTextureUsing == 1) {
            diffuseTerm = vec3(texture(texture_diffuse1, fs_in.texCoord));
        }

        // specular
        vec3 viewDir = normalize(viewPos - fs_in.fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        vec3 specularTerm = spec * specular;
        if(specularTextureUsing == 1) {
            specularTerm = spec * vec3(texture(texture_specular1, fs_in.texCoord));
        }

        //to test phong shader:
        //radiance += ambient + diffuse + specular;
        //for shadow mapping
        radiance += (diffuseTerm + specularTerm) * lightIntensity;
        //debug normals
        //radiance = fs_in.normal * 0.5 + 0.5;
    }
    vec3 result = (ambient + radiance) * shadow;
    FragColor = vec4(result,1.0f);
    //FragColor = texture(texture_diffuse1, fs_in.texCoord);
}
