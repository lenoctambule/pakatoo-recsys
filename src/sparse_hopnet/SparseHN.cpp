#include "SparseHN.hpp"

SparseHNN::SparseHNN(size_t ctx_len) : _ctx_len(ctx_len)
{}

SparseHNN::SparseHNN(std::string const &path) {
    load(path);
}

SparseHNN::~SparseHNN(){
}

void    SparseHNN::load(std::string const &path)
{
    /* TBD */
}

void    SparseHNN::train(std::vector<t_clamped> clamped_nodes)
{
    Node *curr      = NULL;
    Node *target    = NULL;

    for (size_t i = 0; i < clamped_nodes.size(); i++)
    {
        curr = getNode(clamped_nodes[i].item_id);
        for (size_t j = 0; i < clamped_nodes.size(); j++)
        {
            target = getNode(clamped_nodes[j].item_id);
            if (j != i)
            {
                
            }
        }
    }
}