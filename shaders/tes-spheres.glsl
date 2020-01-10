#version 450

layout(quads) in;

layout(std140) uniform FrameParams
{
	mat4 view;
	mat4 proj;
};

patch in Sphere
{
    vec3 pos;
    float radius;
} sphere;

smooth out vec3 pos;
smooth out vec3 centerPos;

out Light
{
	flat vec3 pos;
	flat float strength;
	flat vec3 color;
} light;

const float Pi = 3.141592654;

void main()
{
    vec2 uv = vec2(-2.0 * Pi * gl_TessCoord.x, gl_TessCoord.y * Pi - Pi / 2.0);
	
	light.color = vec3(1, 1, 1);
	light.strength = 0.01 * sphere.radius * sphere.radius;

    light.pos = (view * vec4(sphere.pos + sphere.radius * vec3( cos(uv.y)*cos(uv.x), sin(uv.y), cos(uv.y)*sin(uv.x) ), 1)).xyz;
    gl_Position = proj * vec4(light.pos, 1);
}