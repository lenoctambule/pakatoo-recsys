#include "SparseHN.hpp"

SparseHN::SparseHN(size_t ctx_len) : _ctx_len(ctx_len),
                                    _tensor(1)
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

void    SparseHN::train(std::vector<t_iclamped> &clamped)
{
    size_t seq_len = clamped.size();

    for (size_t i = 0; i < seq_len; i++)
    {
        for (size_t j = 0; j < seq_len; j++)
        {
            if (i == j)
                continue ;
            if (clamped[i].id >= _tensor.size() || clamped[j].id >= _tensor.size())
                continue ;
            std::vector<double> &w = _tensor.get(clamped[i].id, clamped[j].id);
            double              dx = (i - j) / (double)seq_len;
            w[0] += std::tanh(1 / dx) * LR;
        }
    }
}

double  SparseHN::seq_energy(std::vector<t_iclamped> &clamped)
{
    size_t  seq_len = clamped.size();
    double  energy = 0;

    for (int i = 0; i < seq_len; i++)
    {
        for (int j = 0; j < seq_len; j++)
        {
            if (i == j)
                continue;
            std::vector<double> &w = _tensor.get(clamped[i].id, clamped[j].id);
            double              dx = (i - j) / (double) seq_len;
            energy += dx * w[0];
        }
    }
    return energy;
}
