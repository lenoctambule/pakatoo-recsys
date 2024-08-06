#include "SparseHN.hpp"

SparseHN::SparseHN(size_t ctx_len) : _ctx_len(ctx_len),
                                    _tensor(2)
{
}

SparseHN::SparseHN(std::string const &path) : _tensor(2)
{
    load(path);
}

SparseHN::~SparseHN()
{
}

void    SparseHN::load(std::string const &path)
{
    /* TBD */
}

static double clamp(double n, double max) {
    return std::min(max, std::max(-max, n));
}

void    SparseHN::train(std::vector<t_iclamped> clamped)
{
    size_t seq_len = clamped.size();

    for (size_t i = 0; i < seq_len; i++)
    {
        for (size_t j = 0; j < seq_len; j++)
        {
            std::vector<double> &w = _tensor.get(clamped[i].id, clamped[j].id);
            double              dx = (i - j) / seq_len;
            w[0] += 1;
            w[1] += (1 / dx);
        }
    }
}

std::vector<std::size_t>    SparseHN::infer(std::vector<Node&> pattern, size_t out_size)
{
    /* TBD */
}