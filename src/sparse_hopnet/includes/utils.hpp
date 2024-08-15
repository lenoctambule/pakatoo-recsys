#pragma once

# include <cmath>
# include <algorithm>
# include <string>
# include <vector>

# define SIGN(x) (x < 0 ? -1 : 1)
float   logistic(float x);
float   clamp(float x, float max);
void    split(std::string &in, std::vector<std::string> &out);