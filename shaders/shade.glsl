#version 450

in Light
{
	vec3 pos;
	float strength;
	vec3 color;
} light;

out vec3 fs_color;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D albedoTexture;
uniform sampler2D depthTexture;

vec3 shade()
{
	vec2 uv = gl_FragCoord.xy / 1000.0;

    vec3 pos = texture(positionTexture, uv).rgb;
	
    vec3 norm = texture(normalTexture, uv).rgb;
    vec3 albedo = texture(albedoTexture, uv).rgb;

	vec3 to_light = normalize(light.pos - pos);
	float distance2 = pow(length(light.pos - pos), 2);
	
	if(light.strength / (1 + distance2) < 0.01)
		discard;

	vec3 diffuse = clamp(dot(to_light, norm), 0, 1) * light.color * albedo * light.strength / (1 + distance2);

	vec3 to_eye = -normalize(pos);
	vec3 specular = pow(clamp(dot(reflect(-to_light, norm), to_eye), 0, 1), 400) * light.color * light.strength / (1 + distance2);

	return diffuse + specular;
}

void main()
{
    fs_color = shade();
}
