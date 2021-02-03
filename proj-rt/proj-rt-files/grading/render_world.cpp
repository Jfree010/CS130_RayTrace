#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"


Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find the closest object of intersection and return the object that was
// intersected.  Record the Hit structure in hit.  If no intersection occurred,
// return NULL.  Note that in the case of a Boolean, the object returned will be
// the Boolean, but the object stored in hit will be the underlying primitive.
// Any intersection with t<=small_t should be ignored.
Object* Render_World::Closest_Intersection(const Ray& ray, Hit& hit)
{
    // TODO;
    double min_t = std::numeric_limits<double>::max();
    Object* obj = NULL;
    for(size_t k = 0; k < objects.size(); ++k) {//iterate through all objects to see if they intersect the ray
      std::vector<Hit> hitList;
      objects.at(k)->Intersection(ray, hitList);
      if(hitList.size() > 0) { //there is at least 1 intersection
        for(size_t m = 0; m < hitList.size(); ++m) { //find a hit
          if(hitList.at(m).t > small_t) {//ensure there's a hit
            if(hitList.at(m).t < min_t) {//update hit, obj, and min_t if necessary
              min_t = hitList.at(m).t;
              obj = const_cast<Object*>(hitList.at(m).object);
              hit = hitList.at(m);
            }
          }
        }
      }
    }
    if(obj != NULL) {
      return obj;
    }
    return 0;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    //TODO; // set up the initial view ray here
    Ray ray;
    vec3 direct;

    ray.endpoint = camera.position;
    direct = camera.World_Position(pixel_index) - camera.position;
    direct = direct.normalized();
    ray.direction = direct;

    vec3 color=Cast_Ray(ray, 1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    Hit hit;
    vec3 any;

    if(recursion_depth > recursion_depth_limit) {
      return any;
    }

    Object * obj = Closest_Intersection(ray, hit);
    if(obj != NULL) {
      color = obj->material_shader->Shade_Surface(ray, hit.location, hit.Normal(), recursion_depth);
    } else {
      color = this->background_shader->Shade_Surface(ray, any, any, recursion_depth);
    }
    //TODO; // determine the color here
    return color;
}
