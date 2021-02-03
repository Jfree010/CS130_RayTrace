#include "hit.h"
#include "object.h"

vec3 Hit::Normal() const
{
    // TODO;
    vec3 norm = object->Normal(location);
    return norm;
}
