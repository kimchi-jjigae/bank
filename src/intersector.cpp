#include "intersector.hpp"
#include <iostream>

bool intersects(const glm::ivec2& position, const fea::Quad& quad)
{
    glm::ivec2 qPos = (glm::ivec2)(quad.getPosition() - quad.getOrigin());
    glm::ivec2 size = (glm::ivec2)quad.getSize();
    return position.x > qPos.x && position.y > qPos.y && position.x < qPos.x + size.x && position.y < qPos.y + size.y;
}
