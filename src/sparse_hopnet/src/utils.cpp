#include "utils.hpp"

#include <sstream>

void    split(std::string in, std::vector<std::string> &out, char const *sep)
{
    std::stringstream ss (in);
    std::string item;

    out.clear();
    while (getline (ss, item, sep[0])) {
        out.push_back(item);
    }
}

float   clamp(float x, float max)
{
    return std::max(std::min(x, max), -1 * max);
}