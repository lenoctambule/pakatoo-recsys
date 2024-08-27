#pragma once

# include <cmath>
# include <algorithm>
# include <string>
# include <vector>

# define LINE_ERASE "\x1b[1A\x1b[2K"
# define SIGN(x) (x < 0 ? -1 : 1)

float       clamp(float x, float max);
char        *loading_loop();
void        split(std::string in, std::vector<std::string> &out, char const *sep);