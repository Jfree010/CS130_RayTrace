#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
void Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
  //calculating variables for quadratic formula
  vec3 temp = ray.endpoint - center;
  double a = dot(ray.direction, ray.direction);
  double b = 2 * dot(ray.direction, temp);
  double c = dot(temp, temp) - (radius * radius);
  double t0, t1 = -1;

  //potential intersections
  Hit close, far;
  close.object = this;
  far.object = this;

  double discrim = (b * b) - (4 * a * c);

  if(discrim >= 0) { //if discriminant < 0, then there is no intersection
    if(discrim == 0) { //if discriminant = 0, then there is 1 (possible) intersection
      t0 = (-b) / (2 * a);
      t1 = t0;
    } else { //there are 2 (possible) intersections
      double d = sqrt(discrim);
      t0 = (-b + d) / (2 * a);
      t1 = (-b - d) / (2 * a);
    }
    if (t0 > t1) { //ensures t0 <= t1
      double tTemp = t0;
      t0 = t1;
      t1 = tTemp;
    }
    if(t1 >= 0) { //if t1 < 0, there is no intersection
      if(discrim == 0) { //tangent to sphere; hits: (close)
        close.t = t0;
        close.location = ray.Point(t0);
        close.ray_exiting = 0;
        hits.push_back(close);
      } else {
        if(t0 < 0) { //inside sphere; hits: (small_t, far)
          close.t = small_t;
          close.location = ray.Point(small_t);
          close.ray_exiting = 0;
          hits.push_back(close);

          far.t = t1;
          far.location = ray.Point(t1);
          far.ray_exiting = 1;
          hits.push_back(far);
        } else { //enters and exits sphere; hits: (close, far)
          close.t = t0;
          close.location = ray.Point(t0);
          close.ray_exiting = 0;
          hits.push_back(close);

          far.t = t1;
          far.location = ray.Point(t1);
          far.ray_exiting = 1;
          hits.push_back(far);
        }
      }
    }

  }
    // TODO;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    normal = point - center;
    normal = normal.normalized();
    // TODO; // compute the normal direction
    return normal;
}

// set this->bounding_box so that it contains the sphere as tightly as possible.
void Sphere::Update_Bounding_Box()
{
    TODO;
    infinite_box=false;
}
