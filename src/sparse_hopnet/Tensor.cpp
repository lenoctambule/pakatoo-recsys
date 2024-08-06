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
                                ),
                                _N(SIZEINC)
{
}

Tensor::~Tensor()
{
}

size_t                  Tensor::size() { return _N; }
size_t                  Tensor::getDepth() { return _depth; }

std::vector<double>     &Tensor::get(size_t x, size_t y)
{
    return (_tensor[y][x]);
}

std::vector<double>     &Tensor::operator()(size_t x, size_t y)
{
    return get(x, y);
}

void                    Tensor::extend()
{
    for (auto ite = _tensor.begin(); ite != _tensor.end(); ite++)
        ite->resize(ite->size() + SIZEINC);
    _N += SIZEINC;
}
