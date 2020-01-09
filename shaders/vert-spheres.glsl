#version 450

out Sphere
{
    vec3 pos;
    float radius;
} sphere;

void main()
{
    vec3 mult = vec3(gl_VertexID / 10, gl_VertexID % 100, gl_VertexID);
    sphere.pos = mult * vec3(0.5);
    sphere.radius = .5;
}