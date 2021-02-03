#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    vec3 r, v, cr, cs, c;
    double n_dot_v;

    //find reflected ray
    v = -ray.direction;
    n_dot_v = dot(normal, v.normalized());
    r = (2 * n_dot_v * normal) - v.normalized(); //reflected direction
    Ray reflected_ray(intersection_point, r.normalized());

    //cast reflected ray
    cr = world.Cast_Ray(reflected_ray, recursion_depth + 1);
    cs = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);

    color = (reflectivity * cr + (1 - reflectivity) * cs);

    //TODO; // determine the color
    return color;
}
