#version 400

in VertexData
{
	vec3 out_norm;
	vec3 out_pos;
	vec2 out_uv;
};

layout(location = 0) out vec3 fs_position;
layout(location = 1) out vec3 fs_normal;
layout(location = 2) out vec3 fs_albedo;

uniform sampler2D diffuseText;

void main()
{
	fs_position = out_pos;
	fs_normal = normalize(out_norm);
	fs_albedo = texture(diffuseText, out_uv).rgb;
}
