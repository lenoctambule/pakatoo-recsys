#pragma once

#include "SparseHN.hpp"

typedef struct s_utrack
{
    size_t                  sid;
    std::vector<t_iclamped> ratings;
} t_utrack;

class   Pakatoo
{
    private :
        SparseHN                            _ctxhn;
        SparseHN                            _seqhn;
        std::unordered_map<size_t, t_utrack>  _uid_to_sid;

        Pakatoo(Pakatoo const &a);
        Pakatoo &operator=(Pakatoo const &a);

    public :
        Pakatoo();
        ~Pakatoo();

        void    train_stream(size_t uid, t_iclamped &clamped);
        void    train_batch(std::vector<t_iclamped> const &seq, std::vector<std::vector<t_iclamped>> const &ctx);
        float   eval(size_t uid, size_t id);
};