#include "SparseHN.hpp"

SparseHN::SparseHN(size_t ctx_len) : _ctx_len(ctx_len)
{
}

SparseHN::SparseHN(std::string const &path)
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

void    SparseHN::train(std::vector<t_iclamped> clamped_nodes)
{
    for (size_t i = 0; i < clamped_nodes.size(); i++)
    {
        for (size_t j = 0; j < clamped_nodes.size(); j++)
        {
            Node &a = _nodes[clamped_nodes[i].id];
            Node &b = _nodes[clamped_nodes[j].id];

            a.setState(clamped_nodes[i].val);
            b.setState(clamped_nodes[j].val);
            if (j != i)
            {
                a.interact(&b);
                b.interact(&a);
            }
        }
    }
}

std::vector<std::size_t>    SparseHN::infer(std::vector<Node&> pattern, size_t out_size)
{
    /* TBD */
}