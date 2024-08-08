#include "Tensor.hpp"
#include <vector>
#include <iostream>

Tensor::Tensor(size_t depth) : _depth(depth),
                                _tensor()
{
}

Tensor::~Tensor()
{
}

size_t                  Tensor::size() { return _tensor.size(); }
size_t                  Tensor::getDepth() { return _depth; }

std::vector<double>     &Tensor::get(size_t x, size_t y)
{
    if (x >= _tensor.size())
        _tensor.resize(x + 1);
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

void                    Tensor::save_adj(std::string const &path, std::ofstream &out, size_t idx)
{
    size_t  len = _tensor[idx].size();

    out.write(reinterpret_cast<const char *>(&len), std::streamsize(sizeof(size_t)));
    for (auto ite = _tensor[idx].begin(); ite != _tensor[idx].end(); ite++)
    {
        out.write(reinterpret_cast<const char *>(&ite->first), std::streamsize(sizeof(size_t)));
        for (size_t i = 0; i < ite->second.size(); i++)
            out.write(reinterpret_cast<const char *>(&ite->second[i]), std::streamsize(sizeof(double)));
    }
}

void                    Tensor::save(std::string const &path)
{
    std::ofstream       out;
    std::stringstream   filename;

    out.open(path, std::fstream::out);
    if (!out.is_open())
        throw std::runtime_error("Could not open or create file.");
    out << FSIG;
    out.write(reinterpret_cast<const char *>(&_depth), std::streamsize(sizeof(size_t)));
    for (size_t i = 0; i < _tensor.size(); i++)
        save_adj(filename.str(), out, i);
}

void                Tensor::load(std::string const &path)
{
    
}
