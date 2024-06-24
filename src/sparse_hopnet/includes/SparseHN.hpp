#include "Node.hpp"
#include <deque>
#include <vector>
#include <iostream>
#include <cstddef>

typedef struct s_clamped
{
    std::size_t item_id;
    double      value;
} t_clamped;

class SparseHNN
{
    private :
        std::deque<Node>    _nodes;
        size_t              _ctx_len;

        SparseHNN(SparseHNN const &a);
        SparseHNN   &operator=(SparseHNN const &a);
        /* Get or create a node*/
        Node    *getNode(size_t id);

    public :
        SparseHNN(size_t ctx_len);
        SparseHNN(std::string const &path);
        ~SparseHNN();

        /* Load or save a model */
        void    save(std::string const &path);
        void    load(std::string const &path);
        /* Train using either series of clamped nodes or item-item similarity */
        void    train(std::vector<t_clamped> clamped_nodes);
        void    train(size_t a_1, size_t a_2, double d_w);
        /* Infer next likeliest out_size items from a series of user interactions */
        std::vector<std::size_t>    infer(std::vector<t_clamped> pattern, size_t out_size);
};