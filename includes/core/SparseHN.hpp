#pragma once

# include "core/Tensor.hpp"
# include "utils.hpp"
# include <deque>
# include <vector>
# include <map>
# include <iostream>
# include <cstddef>
# include <cmath>
# include <limits>

# define TEMP_DECAY 5.4

typedef struct s_iclamped
{
    size_t      id;
    float       val;
} t_iclamped;

typedef std::deque<t_iclamped>                  t_stream;
typedef std::unordered_map<size_t, t_stream>    t_streams;

class SparseHN
{
    private :
        t_streams   _streams;
        size_t      _sc;
        float       _temp_decay;

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
        template <typename T>
        size_t  stream_init(T const &history) {
            _streams[_sc] = t_stream(history.begin(), history.end());
            return _sc++;
        }
        void    stream_train(size_t sid, t_iclamped const &n);
        void    stream_delete(size_t sid);
        void    stream_clear();

        // Inference
        float   token_energy(std::vector<t_iclamped> const &clamped,
                                size_t i,
                                size_t seq_len);
        float   seq_energy(std::vector<t_iclamped> const &clamped);
        float   eval(std::vector<t_iclamped>  const &clamped, size_t id);
};