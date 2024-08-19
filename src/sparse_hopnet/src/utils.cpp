#include "utils.hpp"

void    split(std::string &in, std::vector<std::string> &out, char const *sep)
{
    size_t  i = 0;

    out.clear();
    while (i < in.size())
    {
        i = in.find_first_of(sep);
        out.push_back(in.substr(0,i));
        in.erase(0,i+1);
    }
}