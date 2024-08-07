#include "Tensor.hpp"
#include <vector>
#include <iostream>

Tensor::Tensor(size_t depth) : _depth(depth),
                                _tensor(),
                                _N(SIZEINC),
                                _c(0)
{
}

Tensor::~Tensor()
{
}

size_t                  Tensor::size() { return _N; }
size_t                  Tensor::getDepth() { return _depth; }

std::vector<double>     &Tensor::get(size_t x, size_t y)
{
    if (x >= _c)
        this->extend();
    auto                line = _tensor[x].find(y);
    std::vector<double> *ret = NULL;

    if (line == _tensor[x].end())
        ret = &(_tensor[x][y] = std::vector<double>(_depth, 0.0));
    else
        ret = &line->second;
    return (*ret);
}

std::vector<double>     &Tensor::operator()(size_t x, size_t y) {
    return get(x, y);
}

size_t                  Tensor::extend()
{
    _tensor.resize(_c + 1);
    return (++_c);
}
