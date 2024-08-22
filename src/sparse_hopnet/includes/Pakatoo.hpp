#pragma once

#include "SparseHN.hpp"

class   Pakatoo
{
    private :
        SparseHN    _ctxhn;
        SparseHN    _seqhn;

        Pakatoo(Pakatoo const &a);
        Pakatoo &operator=(Pakatoo const &a);

    public :
        Pakatoo();
        ~Pakatoo();

        void    train(std::vector<t_iclamped> const &seq, std::vector<std::vector<t_iclamped>> const &ctx);
        float   eval(std::vector<t_iclamped> const &seq, std::vector<t_iclamped> const &ctx, size_t id);
};