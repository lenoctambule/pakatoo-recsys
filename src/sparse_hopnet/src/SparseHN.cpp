#include "SparseHN.hpp"

SparseHN::SparseHN() : _tensor(1)
{
}

SparseHN::SparseHN(std::string const &path) : _tensor(1)
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

static float vlr(float w, float x, float d)
{
    return std::exp(-std::abs(w) * d);
}

void    SparseHN::train(std::vector<t_iclamped> const &clamped)
{
    size_t seq_len = clamped.size();

    for (int i = 0; i < seq_len; i++)
    {
        for (int j = 0; j < seq_len; j++)
        {
            if (i == j)
                continue ;
            std::vector<float> &w   = _tensor.get(clamped[i].id, clamped[j].id);
            float              dx   = (i - j) / (float) seq_len;
            w[0]                    +=  vlr(w[0], clamped[i].val * clamped[j].val, 5.0f) * clamped[i].val * clamped[j].val;
        }
    }
}

float   SparseHN::token_energy(std::vector<t_iclamped> &clamped,
                                int i,
                                size_t seq_len)
{
    float   E  = 0;

    for (int j = 0; j < seq_len; j++)
    {
        if (i == j)
            continue;
        std::vector<float> w   = _tensor.get_dup(clamped[i].id, clamped[j].id);
        float              dx   = (i - j) / (float) seq_len;
        if (w[1] == 0)
            continue;
        E                       += (w[0] * clamped[i].val * clamped[j].val);
    }
    return E / seq_len;
}

float   SparseHN::seq_energy(std::vector<t_iclamped> &clamped)
{
    size_t  seq_len = clamped.size();
    float   E = 0;
    float   q = 0;

    for (int i = 0; i < seq_len; i++)
        E += token_energy(clamped, i, seq_len);
    return E;
}

float   SparseHN::eval(std::vector<t_iclamped> const &clamped, size_t id)
{
    std::vector<t_iclamped> seq(clamped);
    float                   pre_E, post_E;

    seq.push_back(t_iclamped{.id=id, .val=1});
    pre_E = seq_energy(seq);
    seq[seq.size()-1].val = -1;
    post_E = seq_energy(seq);
    return exp(post_E) / (exp(post_E) + exp(pre_E));
}

size_t  SparseHN::infer(std::vector<t_iclamped> &clamped)
{
    size_t max_id = 0;
    float  max_E = std::numeric_limits<float>::min();
    float  E = 0;
    std::vector<t_iclamped> seq(clamped);

    seq.push_back(t_iclamped{.id=0, .val=1});
    for (size_t id = 0; id < _tensor.size(); id++)
    {
        seq[seq.size()-1].id = id;
        E = seq_energy(seq);
        if (E > max_E)
        {
            max_E       = E;
            max_id      = id;
        }
    }
    return max_id;
}

