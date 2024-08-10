#include "SparseHN.hpp"

SparseHN::SparseHN() : _tensor(1)
{
}

SparseHN::SparseHN(std::string const &path) : _tensor(2)
{
    load(path);
}

SparseHN::~SparseHN()
{
}

void    SparseHN::save(std::string const &path) {
    _tensor.save(path);
}


void    SparseHN::load(std::string const &path) {
    _tensor.load(path);
}

static float   clamp(float x)
{
    return std::min(1.0f, std::max(-1.0f, x));
}

void    SparseHN::train(std::vector<t_iclamped> &clamped)
{
    size_t seq_len = clamped.size();

    for (int i = 0; i < seq_len; i++)
    {
        for (int j = 0; j < seq_len; j++)
        {
            if (i == j)
                continue ;
            std::vector<float> &w   = _tensor.get(clamped[i].id, clamped[j].id);
            float              dx   = (i - j) / (float)seq_len;
            w[0]                    += clamp(1 / dx);
            w[1]                    += clamped[i].val * clamped[j].val;
        }
    }
}

float   SparseHN::token_energy(std::vector<t_iclamped> &clamped,
                                int i,
                                size_t seq_len)
{
    float   energy  = 0;
    for (int j = 0; j < seq_len; j++)
    {
        if (i == j)
            continue;
        std::vector<float> &w  = _tensor.get(clamped[i].id, clamped[j].id);
        float              dx  = (i - j) / (float)seq_len;
        energy                  += w[0] * dx * clamp(w[1] * clamped[i].val * clamped[j].val);
    }
    return energy;
}

float   SparseHN::seq_energy(std::vector<t_iclamped> &clamped)
{
    size_t  seq_len = clamped.size();
    float  energy = 0;
    float  q = 0;

    for (int i = 0; i < seq_len; i++)
        energy += token_energy(clamped, i, seq_len);
    return energy;
}


