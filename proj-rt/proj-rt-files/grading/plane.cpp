#include "plane.h"
#include "ray.h"
#include <cfloat>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
void Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    //TODO;
    double t0, numerator, denominator;
    vec3 pointIntersection = x1 - ray.endpoint;
    numerator = dot(pointIntersection, normal);
    denominator = dot(ray.direction, normal);
    Hit planeHit, zeroHit;
    planeHit.object = this;
    zeroHit.object = this;

    if(denominator != 0) {//there might be an intersection
      t0 = numerator / denominator;
      if(t0 >= 0) {//there is an intersection
        if(t0 == 0) {//endpoint of ray is intersection; hit: (small_t, small_t)
          zeroHit.t = small_t;
          zeroHit.location = ray.Point(small_t);
          zeroHit.ray_exiting = 0;
          hits.push_back(zeroHit);

          planeHit.t = small_t;
          planeHit.location = ray.Point(small_t);
          planeHit.ray_exiting = 1;
          hits.push_back(planeHit);
        } else {//hit: (planeHit)
          planeHit.t = t0;
          planeHit.location = ray.Point(t0);
          planeHit.ray_exiting = 1;
          hits.push_back(planeHit);
        }
      }
    }


}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}

void Plane::Update_Bounding_Box()
{
    bounding_box.Make_Full();
    infinite_box=true;
}
