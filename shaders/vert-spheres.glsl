#version 450

out Sphere
{
    vec3 pos;
    float radius;
} sphere;

const uint div = 100;
const float wraps = 10;

const float Pi = 3.141592654;

void main()
{
    float x = wraps * gl_VertexID / (div - 1);
	float y = x / wraps - 0.2;
	
	vec2 uv = vec2(2 * Pi * x, Pi / 2 - Pi * y / 2);
    sphere.pos = 5.0 * vec3( cos(uv.y)*cos(uv.x), sin(uv.y), cos(uv.y)*sin(uv.x) );
    sphere.radius = 10.0;
	
	//sphere.pos = vec3(0, 0, 6);
	//sphere.radius = 9;
}
