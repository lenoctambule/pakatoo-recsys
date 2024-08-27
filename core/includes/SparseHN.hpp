#pragma once

# include "Tensor.hpp"
# include "utils.hpp"
# include <deque>
# include <vector>
# include <map>
# include <iostream>
# include <cstddef>
# include <cmath>
# include <limits>

typedef struct s_iclamped
{
    size_t      id;
    float       val;
} t_iclamped;

typedef std::deque<t_iclamped>              t_stream;
typedef std::deque<std::deque<t_iclamped>>  t_streams;

class SparseHN
{
    private :
        t_streams   _streams;
        size_t      _sc;

        SparseHN(SparseHN const &a);
        SparseHN    &operator=(SparseHN const &a);

        void        update_interaction(t_iclamped const &a, t_iclamped const &b);

    public :
        Tensor      tensor;

        SparseHN();
        SparseHN(std::string const &path);
        ~SparseHN();

        void    save(std::string const &path);
        void    load(std::string const &path);

        // Train from historical data
        void    batch_train(std::vector<t_iclamped> const &clamped);

        // Stream user interactions for online training
        size_t  stream_create();
        void    stream_train(size_t sid, t_iclamped &n);
        void    stream_clear();

        // Inference
        float   token_energy(std::vector<t_iclamped> const &clamped,
                                size_t i,
                                size_t seq_len);
        float   seq_energy(std::vector<t_iclamped> const &clamped);
        float   eval(std::vector<t_iclamped>  const &clamped, size_t id);
        size_t  infer(std::vector<t_iclamped> &clamped);
};