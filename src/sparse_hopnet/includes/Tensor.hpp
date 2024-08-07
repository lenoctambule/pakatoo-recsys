#pragma once
# include <vector>
# include <deque>
# include <map>
# include <cstddef>
# define SIZEINC 8192

typedef std::map<size_t, std::vector<double>>   adj_t;
typedef std::deque<adj_t>                       tensor_t;

class Tensor
{
    private :
        tensor_t    _tensor;
        size_t      _N;
        size_t      _depth;
        size_t      _c;

        Tensor();

    public :
        Tensor(size_t _depth);
        ~Tensor();

        size_t                  size();
        size_t                  getDepth();

        std::vector<double>     &get(size_t x, size_t y);
        std::vector<double>     &operator()(size_t x, size_t y);
        size_t                  extend();
};