#include "core/SparseHN.hpp"

SparseHN::SparseHN() : 
    _sc(0),
    _temp_decay(TEMP_DECAY),
    tensor(1, true)
{
}

SparseHN::SparseHN(std::string const &path) :
    _sc(0),
    _temp_decay(TEMP_DECAY),
    tensor(1, true)
{
    load(path);
}

SparseHN::~SparseHN()
{
}

void    SparseHN::save(std::string const &path) {
    tensor.save(path);
}

void    SparseHN::load(std::string const &path) {
    tensor.load(path);
}

static float vlr(float w, float d)
{
    return std::exp(-std::abs(w) * d);
}

void    SparseHN::update_interaction(t_iclamped const &a, t_iclamped const &b)
{
    std::vector<float> &w   = tensor.get_or_create(a.id, b.id);
    w[0]                    += vlr(w[0], _temp_decay) * a.val * b.val;
}

void    SparseHN::batch_train(std::vector<t_iclamped> const &clamped)
{
    size_t seq_len  = clamped.size();

    for (size_t i = 0; i < seq_len; i++)
        for (size_t j = i + 1; j < seq_len; j++)
            update_interaction(clamped[i], clamped[j]);
}

size_t  SparseHN::stream_create()
{
    _streams[_sc] = t_stream();
    return _sc++;
}

void    SparseHN::stream_delete(size_t sid) {
    _streams.erase(sid);
}

void    SparseHN::stream_train(size_t sid, t_iclamped const &n)
{
    auto    ite = _streams.find(sid);
    if (ite == _streams.end())
        throw std::out_of_range("Invalid stream id.");
    t_stream &s = ite->second;
    for (auto ite = s.begin(); ite != s.end(); ite++)
        update_interaction(n, *ite);
    s.push_back(n);
}

void    SparseHN::stream_clear() {
    _streams.clear();
}

float   SparseHN::token_energy(std::vector<t_iclamped> const &clamped,
                                size_t i,
                                size_t seq_len)
{
    float   E  = 0;

    for (size_t j = 0; j < seq_len; j++)
    {
        if (i == j)
            continue;
        const std::vector<float> &w = tensor.get(clamped[i].id, clamped[j].id);
        E                           += (w[0] * clamped[i].val * clamped[j].val);
    }
    return E;
}

float   SparseHN::seq_energy(std::vector<t_iclamped> const &clamped)
{
    size_t  seq_len = clamped.size();
    float   E = 0;

    for (size_t i = 0; i < seq_len; i++)
        E += token_energy(clamped, i, seq_len);
    return E / seq_len;
}


/*
This function computes the relative probability between the system
with the id token added and without
P = norm(E_x) = norm(4 * \sum_{x \in P} W_ij * x_i)
*/
float   SparseHN::eval(std::vector<t_iclamped> const &clamped, size_t id)
{
    float                   d_E = 0;
    float                   tmp = 0;

    for (size_t i = 0; i < clamped.size(); i++)
    {
        const std::vector<float> &w = tensor.get(clamped[i].id, id);
        d_E                         += w[0] * clamped[i].val;
    }
    d_E = (d_E) / (clamped.size() + 1);
    tmp = std::exp(4 * d_E);
    return tmp / (tmp + 1);
}