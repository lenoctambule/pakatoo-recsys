#include "Tensor.hpp"
#include <vector>
#include <iostream>

Tensor::Tensor(size_t depth, bool is_symmetric) :
                                _tensor(),
                                _default(depth, 0),
                                _depth(depth),
                                _ec(0),
                                _emax(0),
                                _is_symmetric(is_symmetric)
{
}

Tensor::~Tensor()
{
}

size_t                  Tensor::size() const { return _tensor.size(); }
size_t                  Tensor::getDepth() const { return _depth; }
double                  Tensor::getSparsity() const {
    return ((double)_ec * 2) / ((_emax + 1) * (_emax + 1)) ;
}

static void                 sort_coordinates(size_t &x, size_t &y)
{
    size_t  tmp;

    tmp      = x;
    x        = std::min(x, y);
    y        = std::max(tmp, y);
}

std::vector<float>          &Tensor::get_or_create(size_t x, size_t y)
{
    if (_is_symmetric)
        sort_coordinates(x, y);
    _emax = _emax < x ? x : (_emax < y ? y : _emax);
    if (x >= _tensor.size())
        _tensor.resize(x + 1);
    auto    line = _tensor[x].find(y);
    if (line == _tensor[x].end())
        return _ec++, (_tensor[x][y] = std::vector<float>(_depth, 0.0));
    return (line->second);
}

const std::vector<float>    &Tensor::get(size_t x, size_t y) const
{
    if (_is_symmetric)
        sort_coordinates(x, y);
    if (x >= _tensor.size())
        return _default;
    auto    line = _tensor[x].find(y);
    if (line == _tensor[x].end())
        return _default;
    return (line->second);
}

std::vector<float>      &Tensor::operator()(size_t x, size_t y) {
    return get_or_create(x, y);
}

void                    Tensor::save_adj(std::ofstream &out, size_t idx)
{
    size_t  len = _tensor[idx].size();

    out.write(reinterpret_cast<const char *>(&idx), std::streamsize(sizeof(size_t)));
    out.write(reinterpret_cast<const char *>(&len), std::streamsize(sizeof(size_t)));
    for (auto ite = _tensor[idx].begin(); ite != _tensor[idx].end(); ite++)
    {
        out.write(reinterpret_cast<const char *>(&ite->first), std::streamsize(sizeof(size_t)));
        for (size_t i = 0; i < ite->second.size(); i++)
            out.write(reinterpret_cast<const char *>(&ite->second[i]), std::streamsize(sizeof(float)));
    }
}

void                    Tensor::save(std::string const &path)
{
    std::ofstream       out;
    std::stringstream   filename;
    size_t              n_tokens;

    out.open(path, std::fstream::out);
    if (!out.is_open())
        throw std::runtime_error("Could not open or create file.");
    out.write(FSIG, 4);
    out.write(reinterpret_cast<const char *>(&_depth), std::streamsize(sizeof(size_t)));
    n_tokens = _tensor.size();
    out.write(reinterpret_cast<const char *>(&n_tokens), std::streamsize(sizeof(size_t)));
    for (size_t i = 0; i < _tensor.size(); i++)
        save_adj(out, i);
}

void                Tensor::load_adj(std::ifstream &in)
{
    size_t              self_id;
    size_t              len;
    size_t              target_id;
    std::vector<float>  w;
    char                sbuf[8];
    char                fbuf[4];

    in.read(sbuf, sizeof(size_t));
    self_id = *reinterpret_cast<size_t *>(sbuf);
    in.read(sbuf, sizeof(size_t));
    len = *reinterpret_cast<size_t *>(sbuf);
    w.resize(_depth);
    for (size_t i = 0; i < len; i++)
    {
        in.read(sbuf, sizeof(size_t));
        target_id = *reinterpret_cast<size_t *>(sbuf);
        for (size_t j = 0; j < _depth; j++)
        {
            in.read(fbuf, sizeof(float));
            w.push_back(*reinterpret_cast<float *>(fbuf));
        }
        _tensor[self_id][target_id] = w;
        w.clear();
    }
}

void                Tensor::load(std::string const &path)
{
    std::ifstream   in;
    char            buff[8];
    size_t          n_tokens;

    in.open(path, std::fstream::in);
    if (!in.is_open())
        throw std::runtime_error("could not open or create file");
    in.read(buff, 4);
    in.read(buff, sizeof(size_t));
    _depth = *reinterpret_cast<size_t *>(buff);
    in.read(buff, sizeof(size_t));
    n_tokens = *reinterpret_cast<size_t *>(buff);
    _tensor.clear();
    _tensor.resize(n_tokens);
    for (size_t i = 0; i < n_tokens; i++)
        load_adj(in);
}
