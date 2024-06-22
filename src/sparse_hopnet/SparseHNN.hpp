#include "Node.hpp"
#include <deque>
#include <vector>
#include <iostream>
#include <cstddef>

typedef struct s_uinteract
{
    std::size_t item_id;
    double      value;
} t_uinteract;

class SparseHNN
{
    private :
        std::deque<Node>    _nodes;

    public :
        SparseHNN();
        SparseHNN(SparseHNN const &a);
        ~SparseHNN();
        SparseHNN   &operator=(SparseHNN const &a);

        /* Save the model to be loaded later*/
        void        save(std::string const &path);
        /* Load a saved model*/
        void        load(std::string const &path);

        /* Train using either series of clamped nodes or item-item similarity */
        void                        train(std::vector<t_uinteract> clamped_nodes);
        void                        train(size_t a_1, size_t a_2, double d_w);

        /* Infer next likeliest out_size items from a series of user interactions */
        std::vector<std::size_t>    infer(std::vector<t_uinteract> pattern, size_t out_size);
};