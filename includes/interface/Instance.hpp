#pragma once

#include "core/SparseHN.hpp"

typedef struct s_utrack
{
    size_t                  sid;
    std::vector<t_iclamped> ratings;
} t_utrack;

class   Instance
{
    private :
        std::unordered_map<size_t, t_utrack>    _users;

        Instance(Instance const &a);
        Instance &operator=(Instance const &a);

    public :
        SparseHN                                cf_graph;

        Instance();
        ~Instance();

        void    stream_train(size_t uid, t_iclamped &clamped);
        float   stream_eval(size_t uid, size_t id);
        void    batch_train(std::vector<t_iclamped> const &seq, std::vector<std::vector<t_iclamped>> const &ctx);

        void    save(std::string const &path);
};