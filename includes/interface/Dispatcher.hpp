#pragma once

#include "core/Pakatoo.hpp"
#include "interface/Worker.hpp"
#include <thread>
#include <stack>
#include <condition_variable>

class Dispatcher
{
    private:
        Pakatoo                                 _recsys;
        std::vector<Worker>                     _inference_workers;
        std::deque<std::thread>                 _pool;
        Worker                                  _training_worker;
        std::unordered_map<size_t, t_result>    _results;

        Dispatcher();
        Dispatcher(Dispatcher const &a);
        Dispatcher  &operator=(Dispatcher const &a);

    public:
        Dispatcher(ushort a);
        ~Dispatcher();

        void    init();
        void    join();
        void    dispatch_eval(size_t uid, size_t id, t_result *res);
        void    dispatch_training(size_t uid, t_iclamped &clamped);
        bool    is_training();
};