#include "Tensor.hpp"
#include <deque>
#include <vector>
#include <map>
#include <iostream>
#include <cstddef>
#include <cmath>

typedef struct s_iclamped
{
    size_t      id;
    float       val;
} t_iclamped;

class SparseHN
{
    private :
        Tensor                         _tensor;

        SparseHN(SparseHN const &a);
        SparseHN    &operator=(SparseHN const &a);

    public :
        SparseHN();
        SparseHN(std::string const &path);
        ~SparseHN();

        /* Load or save a model */
        void    save(std::string const &path);
        void    load(std::string const &path);
        /* Train using either series of clamped nodes or item-item similarity */
        void    train(std::vector<t_iclamped> &clamped);
        /* Infer next likeliest <out_size> items from a series of user interactions */
        float  seq_energy(std::vector<t_iclamped> &clamped);
};