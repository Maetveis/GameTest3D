#version 450

in VertexData
{
	vec2 uv;
};

out float fs_ambient;

layout(std140) uniform KernelBlock {
	vec3 samples[64];
};

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2DShadow depthTexture;

uniform sampler2D rotTexture;

uniform float sampleRadius;
uniform mat4 proj;

void main()
{
	vec3 pos = texture(positionTexture, uv).rgb;
	vec3 norm = normalize(texture(normalTexture, uv).rgb);
	
	vec3 tangent = texture(rotTexture, gl_FragCoord.xy / textureSize(rotTexture, 0)).rgb;
	tangent = normalize(tangent - dot(tangent, norm) * norm);
	
	mat3 TNB = mat3(tangent, norm, cross(tangent, norm));
	
	float occlusion = 0.0;
	for(uint i = 0; i < samples.length(); ++i) {
		vec3 samplePos = pos + sampleRadius * TNB * samples[i];
		vec4 sampleScreen = proj * vec4(samplePos, 1);
		sampleScreen = 0.5 * (sampleScreen / sampleScreen.w) + 0.5;
		occlusion += texture(depthTexture, sampleScreen.xyz);
	}

	fs_ambient = /*1.0 -*/ occlusion / samples.length();
}
