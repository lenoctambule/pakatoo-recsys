#include "utils.hpp"

float   logistic(float x) {
    return 1 / (1 + std::exp(-x));
}

float   clamp(float x, float max) {
    return std::min(1.0f * max, std::max(-1.0f, x * max));
}

void    split(std::string &in, std::vector<std::string> &out)
{
    size_t  i = 0;

    out.clear();
    while (i < in.size())
    {
        i = in.find_first_of(" \n\t\v\f\r");
        out.push_back(in.substr(0,i));
        in.erase(0,i+1);
    }
}