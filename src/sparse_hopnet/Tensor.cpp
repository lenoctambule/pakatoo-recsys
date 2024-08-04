#include "Tensor.hpp"
#include <vector>

Tensor::Tensor(size_t depth) : _depth(depth),
                                _tensor(SIZEINC,
                                    std::vector<std::vector<double>>
                                    (
                                        SIZEINC, std::vector<double>(
                                            depth, 0.0
                                        )
                                    )
                                )
{
}

Tensor::~Tensor()
{
}

std::vector<double>    &Tensor::get(size_t x, size_t y)
{
    return (_tensor[y][x]);
}

std::vector<double>     &Tensor::operator()(size_t x, size_t y)
{
    return get(x, y);
}

void                    Tensor::extend()
{
    /* TODO */
}
