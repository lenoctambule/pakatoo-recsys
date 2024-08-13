#include "SparseHN.hpp"

SparseHN::SparseHN() : _tensor(2)
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

static float   clamp(float x, float max)
{
    return std::min(1.0f * max, std::max(-1.0f, x * max));
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
            w[0]                    += clamp(1 / dx, 1);
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
        std::vector<float> &w   = _tensor.get(clamped[i].id, clamped[j].id);
        float              dx   = (i - j) / (float)seq_len;
        energy                  += w[0] * dx * clamp( clamped[i].val * clamped[j].val * w[1], 1.0f);
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

size_t  SparseHN::infer(std::vector<t_iclamped> &clamped)
{
    size_t max_id = 0;
    float  max_energy = std::numeric_limits<float>::min();
    float  energy = 0;
    std::vector<t_iclamped> seq(clamped);

    seq.push_back(t_iclamped{.id=0, .val=1});
    for (size_t id = 0; id < _tensor.size(); id++)
    {
        seq[seq.size()-1].id = id;
        energy = token_energy(seq, seq.size()-1, seq.size());
        if (energy > max_energy)
        {
            max_energy  = energy;
            max_id      = id;
        }
    }
    clamped.push_back(t_iclamped{.id=max_id, .val=1});
    return max_id;
}

