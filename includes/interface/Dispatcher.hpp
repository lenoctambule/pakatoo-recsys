#pragma once

#include "core/Pakatoo.hpp"
#include "interface/Worker.hpp"
#include <thread>
#include <stack>

class Dispatcher
{
    private:
        std::vector<Worker>         _threads;
        std::stack<float>           _eval_jobs;
        std::stack<size_t>          _training_jobs;
        Pakatoo                     _recsys;

        Dispatcher(Dispatcher const &a);
        Dispatcher  &operator=(Dispatcher const &a);

    public:
        Dispatcher();
        ~Dispatcher();

        size_t  dispatch_eval(size_t uid, size_t id);
        void    dispatch_training(size_t uid, t_iclamped &clamped);
};