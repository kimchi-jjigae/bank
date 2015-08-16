#pragma once
#include <random>

int32_t randomWaitTime() //1-5 minutes
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>dis(1,5);
    return dis(gen) * 3600;
}
