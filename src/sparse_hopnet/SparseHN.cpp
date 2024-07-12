#include "SparseHN.hpp"

SparseHN::SparseHN(size_t ctx_len) : _ctx_len(ctx_len)
{}

SparseHN::SparseHN(std::string const &path) {
    load(path);
}

SparseHN::~SparseHN(){
}

void    SparseHN::load(std::string const &path)
{
    /* TBD */
}

void    SparseHN::train(std::vector<Node &> clamped_nodes)
{
    for (size_t i = 0; i < clamped_nodes.size(); i++)
    {
        for (size_t j = 0; i < clamped_nodes.size(); j++)
            if (j != i) clamped_nodes[i].interact(&clamped_nodes[j]);
    }
}

std::vector<std::size_t>    SparseHN::infer(std::vector<Node&> pattern, size_t out_size)
{
    /* TBD */
}