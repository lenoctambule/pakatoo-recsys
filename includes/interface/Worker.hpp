#pragma once

# include "core/Pakatoo.hpp"
# include <stack>
# include <unistd.h>
# include <future>

typedef struct s_result
{
    bool    state;
    float   res;
} t_result;

typedef struct s_job
{
    bool        is_training;
    t_iclamped  clamped;
    size_t      uid;
    size_t      id;
    t_result    *res;
} t_job;

class Worker
{
    private:
        Pakatoo                 *_recsys;
        std::mutex              _mutjobs;
        std::stack<t_job>       _jobs;
        size_t                  _id;
        static size_t           _cid;

        Worker();
    public:
        Worker(Pakatoo *recsys);
        Worker(Worker const &a);
        Worker &operator=(Worker const &a);
        ~Worker();

        void    init();
        void    addTrainingJob(size_t uid, t_iclamped &clamped);
        void    addInferenceJob(size_t uid, size_t id, t_result *res);
        bool    is_unemployed();
};