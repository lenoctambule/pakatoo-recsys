#pragma once

# include "core/Pakatoo.hpp"
# include <stack>
# include <unistd.h>

typedef struct s_job
{
    bool        is_training;
    t_iclamped  clamped;
    size_t      uid;
    size_t      id;
} t_job;

class Worker
{
    private:
        Pakatoo             &_recsys;
        std::stack<t_job>   _jobs;

        Worker();
    public:
        Worker(Pakatoo &recsys);
        Worker(Worker const &a);
        Worker &operator=(Worker const &a);
        ~Worker();

        void    operator()();
        void    addTrainingJob(size_t uid, t_iclamped &clamped);
        void    addInferenceJob(size_t uid, size_t id);
};