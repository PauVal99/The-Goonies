#ifndef _COLLISION_BOX
#define _COLLISION_BOX

#include <glm/glm.hpp>

using namespace std;

struct CollisionBox
{
    glm::ivec2 min;
    glm::ivec2 max;
};


#endif // _COLLISION_BOX


