#version 450

in vec3 pos;
in vec3 centerPos;

layout(location = 0) out vec3 fs_position;
layout(location = 1) out vec3 fs_normal;
layout(location = 2) out vec3 fs_albedo;

void main()
{
    fs_position = pos;
	fs_normal = normalize(pos - centerPos);
	fs_albedo = vec3(1, 1, 1);//texture(diffuseText, out_uv).rgb;
}