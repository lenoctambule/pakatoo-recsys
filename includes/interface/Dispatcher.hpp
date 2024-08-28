#pragma once

#include "core/Pakatoo.hpp"
#include "interface/Worker.hpp"
#include <thread>
#include <stack>

class Dispatcher
{
    private:
        Pakatoo                     _recsys;
        std::vector<Worker>         _inference_workers;
        std::deque<std::thread>     _threads;
        Worker                      _training_worker;

        Dispatcher();
        Dispatcher(Dispatcher const &a);
        Dispatcher  &operator=(Dispatcher const &a);

    public:
        Dispatcher(ushort a);
        ~Dispatcher();

        void    init();
        void    join();
        size_t  dispatch_eval(size_t uid, size_t id);
        void    dispatch_training(size_t uid, t_iclamped &clamped);
};