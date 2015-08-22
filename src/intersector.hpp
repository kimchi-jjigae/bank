#pragma once
#include "glm.hpp"
#include <fea/render2d.hpp>

bool intersects(const glm::ivec2& position, const fea::Quad& quad);
