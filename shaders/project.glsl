#version 400

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_norm;
layout(location = 2) in vec2 in_uv;

out VertexData
{
	vec3 out_norm;
	vec3 out_pos;
	vec2 out_uv;
};

uniform mat4 model;

layout(std140) uniform FrameParams
{
	mat4 view;
	mat4 proj;
};

void main()
{
	vec4 pos = view * model * vec4(in_pos, 1);
	//No non-uniform scales because of this
	out_norm = (view * model * vec4(in_norm, 0)).xyz;
	gl_Position = proj * pos;

	out_pos = pos.xyz;
	out_uv = in_uv;
}
