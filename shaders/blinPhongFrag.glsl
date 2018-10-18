#version 400

in VertexData
{
	vec3 out_norm;
	vec3 out_pos;
};

layout(location = 0) out vec4 fs_out_col;

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

layout(std140) uniform MaterialParams
{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float sE;
};

void main()
{
	vec3 ambient = Ka * lights[0].color * 0.1;
	
	vec3 to_light = normalize(lights[0].pos - out_pos);
	float distance2 = dot(lights[0].pos - out_pos, lights[0].pos - out_pos);
	vec3 norm = normalize(out_norm);
	
	vec3 diffuse = clamp(dot(to_light, norm), 0, 1) * lights[0].color * Kd * lights[0].strength / distance2;
	
	vec3 to_eye = normalize(-out_pos);
	vec3 specular = pow(clamp(dot(reflect(-to_light, norm), to_eye), 0, 1), sE) * Ks * lights[0].color * lights[0].strength;
	
	fs_out_col = vec4(ambient + diffuse + specular, 1);
}