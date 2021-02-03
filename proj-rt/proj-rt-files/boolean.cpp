#include "boolean.h"
#include "algorithm"

// Determine if the ray intersects with the boolean of A and B.
void Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    //create list of hits for A and B
    std::vector<Hit> hitA;
    std::vector<Hit> hitB;

    bool insideA = false;
    bool insideB = false;
    Hit empty;
    A->Intersection(ray, hitA);
    if(hitA.size() == 1 && (hitA.at(0).t != small_t)) { //intersection is tangent to sphere
      hitA.push_back(hitA.at(0));
    }
    if(hitA.at(0).t == small_t) {
      insideA = true;
    }

    B->Intersection(ray, hitB);
    if(hitB.size() == 1 && (hitB.at(0).t != small_t)) { //intersection is tangent to sphere
      hitB.push_back(hitB.at(0));
    }
    if(hitB.at(0).t == small_t) {
      insideB = true;
    }

    //hitA.insert(hitA.end(), hitB.begin(), hitB.end());

    auto lambda = [] (Hit const &h1, Hit const &h2) -> bool {
      return h1.t < h2.t;
    };

    //std::sort(hitA.begin(), hitA.end(), lambda);

    for(size_t i = 0; i < hitA.size(); ++i) {
      if(hitA.at(i).ray_exiting) {

      } else {
        insideA = true;
      }

      if(hitA.at)
    }

    TODO;
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}

void Boolean::Update_Bounding_Box()
{
    A->Update_Bounding_Box();
    B->Update_Bounding_Box();
    // Compute bounding_box from A->bounding_box and B->bounding_box.
    // Note that this should depend on the type of boolean being performed.
    TODO;
}
