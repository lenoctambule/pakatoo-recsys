#include "Node.hpp"
#include "Tensor.hpp"
#include <deque>
#include <vector>
#include <iostream>
#include <cstddef>

typedef struct s_iclamped
{
    size_t      id;
    double      val;
} t_iclamped;

typedef struct s_sclamped
{
    std::string token;
    double      val;
} t_sclamped;

class SparseHN
{
    private :
        std::deque<Node>               _nodes;
        Tensor                         _tensor;
        size_t                         _ctx_len;

        SparseHN(SparseHN const &a);
        SparseHN    &operator=(SparseHN const &a);
        /* Get or create a node */
        Node        *get_or_create(size_t id);

    public :
        SparseHN(size_t ctx_len);
        SparseHN(std::string const &path);
        ~SparseHN();

        /* Load or save a model */
        void    save(std::string const &path);
        void    load(std::string const &path);
        /* Train using either series of clamped nodes or item-item similarity */
        void    train(std::vector<t_iclamped> clamped_nodes);
        /* Infer next likeliest <out_size> items from a series of user interactions */
        std::vector<std::size_t>    infer(std::vector<Node&> pattern, size_t out_size);
};