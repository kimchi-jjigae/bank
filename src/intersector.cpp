#include "intersector.hpp"

bool intersects(const glm::uvec2& position, const fea::Quad& quad)
{
    glm::uvec2 qPos = (glm::uvec2)(quad.getPosition() + quad.getOrigin());
    glm::uvec2 size = (glm::uvec2)quad.getSize();
    return position.x > qPos.x && position.y > qPos.y && position.x < qPos.x + size.x && position.y < qPos.y + size.y;
}
