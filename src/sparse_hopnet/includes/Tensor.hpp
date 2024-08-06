#pragma once
# include <vector>
# include <cstddef>
# define SIZEINC 4096

typedef std::vector<std::vector<std::vector<double>>> tensor_t;

class Tensor
{
    private :
        tensor_t    _tensor;
        size_t      _N;
        size_t      _depth;

        Tensor();

    public :
        Tensor(size_t _depth);
        ~Tensor();

        size_t                  size();
        size_t                  getDepth();

        std::vector<double>     &get(size_t x, size_t y);
        std::vector<double>     &operator()(size_t x, size_t y);
        void                    extend();
};