#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;//Ia + Id + Is
    vec3 Ia, Id, Is, cds;

    //calculating ambient color
    Ia = color_ambient * world.ambient_color * world.ambient_intensity;

    for(size_t i = 0; i < world.lights.size(); ++i) {
      //check for shadows
      vec3 l = world.lights.at(i)->position - intersection_point; //light direction
      vec3 Lds= world.lights.at(i)->Emitted_Light(l);

      bool shadowed = false;
      Ray shadow_ray(intersection_point ,l);

      Hit hit;
      Object * obj = world.Closest_Intersection(shadow_ray, hit);
      double l_distance = l.magnitude();
      double h_distance = (shadow_ray.Point(hit.t) - intersection_point).magnitude();
      if(obj and world.enable_shadows) {
          shadowed = (l_distance > h_distance) ? true : false;
      }

      if(!shadowed) {//if light source is closer to intersection, add light
        //calculating diffuse color
        double n_dot_l = dot(normal, l.normalized());
        Id = color_diffuse * Lds * std::max(n_dot_l, 0.0);

        //calculating specular color
        vec3 r = 2.0 * dot(normal, -l) * normal + l;
        double v_dot_r = dot(ray.direction, r.normalized());
        double alpha_power = std::max(v_dot_r, 0.0);
        Is = color_specular * Lds * std::pow(alpha_power, specular_power);

        cds += Id + Is;
      }
    }

    color = Ia + cds;
    //TODO; //determine the color
    return color;
}

/*
Phong_Shader(ray, intersection_point, normal recursion_depth)
  //Here's what you need to calculate:
  Ia: ambient color
  Id: diffuse color * light * max(dot(n ,l), 0)
  Is: specular color * light * max(dot(v, r)^specular_power, 0)
    //make sure dot(v,r) is positive, otherwise ignore it
    //color variables can be found in renderworld and phong_shader files

  //find all vectors (dont forget to normalize these for calculations)
  v: opposite of ray direction
  l: direction of light from intersection_point
  n: normal
  r: reflected direction //2 * dot(n, l) * n - l

  for (all lights)//look at renderworld and light files for variables and functions
    find l
    check for shadows
      //create a ray from the intesection point
      //use Closest_Intersection
      //if light is blocked, move on to next light
    calculate light
      //use Emitted_Light function
      //DO NOT pass in a normalized vector into function
    calculate Id (diffuse color)
    calculate Is (specular color)
      //if dot(v, r) < 0, specular color = 0
    add Is and Id
  add total specular and diffuse color to ambient color
*/
