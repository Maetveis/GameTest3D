#version 450

in VertexData
{
	vec2 uv;
};

out vec3 fs_color;

struct Light
{
	vec3 pos;
	vec3 color;
	float strength;
};

layout(std140) uniform LightParams
{
	Light lights[10];
	uint lightCount;
};

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D albedoTexture;

vec3 shadeFrom(Light light)
{
    vec3 pos = texture(positionTexture, uv).rgb;
    vec3 norm = texture(normalTexture, uv).rgb;
    vec3 albedo = texture(albedoTexture, uv).rgb;

	vec3 to_light = normalize(light.pos - pos);
	float distance2 = length(light.pos - pos);

	vec3 diffuse = clamp(dot(to_light, norm), 0, 1) * light.color * albedo * light.strength / distance2;

	vec3 to_eye = normalize(pos);
	vec3 specular = pow(clamp(dot(reflect(-to_light, norm), to_eye), 0, 1), 10) * 0.8 * light.color * light.strength / distance2;

	return diffuse + specular;//light.strength * light.color;
}

void main()
{
    vec3 color = vec3(0.0);
	for(uint i = 0; i < lightCount; ++i)
	{
		color += shadeFrom(lights[i]);
	}

    fs_color = color;
}