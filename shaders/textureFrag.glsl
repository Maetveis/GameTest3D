#version 400

in VertexData
{
	vec3 out_norm;
	vec3 out_pos;
	vec2 out_uv;
};

layout(location = 0) out vec4 fs_out_col;

struct Light
{
	vec3 pos;
	vec3 color;
	float strength;
};

layout(std140) uniform MaterialParams
{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float sE;
};

layout(std140) uniform LightParams
{
	Light lights[10];
	uint lightCount;
};

uniform sampler2D diffuseText;

vec3 shadeFrom(Light light)
{
	vec3 to_light = normalize(light.pos - out_pos);
	float distance2 = length(light.pos - out_pos);
	vec3 norm = normalize(out_norm);

	vec3 diffuse = (clamp(dot(to_light, norm), 0, 1) + .1) * light.color * texture(diffuseText, out_uv).rgb * light.strength / distance2;

	vec3 to_eye = normalize(-out_pos);
	vec3 specular = pow(clamp(dot(reflect(-to_light, norm), to_eye), 0, 1), sE) * Ks * light.color * light.strength / distance2;

	return diffuse + specular;
}

void main()
{
	vec3 color = Ka;

	for(uint i = 0; i < lightCount; ++i)
	{
		color += shadeFrom(lights[i]);
	}

	fs_out_col = vec4(color, 1);
}
