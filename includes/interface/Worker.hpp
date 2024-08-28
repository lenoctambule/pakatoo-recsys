#pragma once

# include "core/Pakatoo.hpp"
# include <stack>

typedef struct s_job
{

} t_job;

class Worker
{
    private:
        Pakatoo             &_recsys;
        std::stack<t_job>   _jobs;

    public:
        Worker(Pakatoo &recsys);
        Worker(Worker const &a);
        Worker &operator=(Worker const &a);
        ~Worker();

        void    operator()();
        void    addTrainingJob(size_t uid, t_iclamped &clamped);
        void    addInferenceJob(size_t uid, size_t id);
};