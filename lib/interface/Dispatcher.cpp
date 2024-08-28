#include "interface/Dispatcher.hpp"

Dispatcher::Dispatcher(ushort n_threads) :
    _inference_workers(n_threads, Worker(&_recsys)),
    _training_worker(&_recsys)
{
}

Dispatcher::~Dispatcher() {
    join();
}

static void start_worker(Worker *worker) {
    worker->init();
}

void    Dispatcher::init()
{
    _pool.push_back(std::thread(start_worker, &_training_worker));
    for (size_t i = 0; i < _inference_workers.size(); i++)
        _pool.push_back(std::thread(start_worker, &_inference_workers[i]));
}

void    Dispatcher::join()
{
    for (size_t i = 0; i < _pool.size(); i++)
        _pool[i].join();
}

void    Dispatcher::dispatch_training(size_t uid, t_iclamped &clamped) {
    _training_worker.addTrainingJob(uid, clamped);
}

void    Dispatcher::dispatch_eval(size_t uid, size_t id, t_result *res)
{
    static size_t wid = 0;

    _inference_workers[wid].addInferenceJob(uid, id, res);
    ++wid %= _inference_workers.size();
}

bool    Dispatcher::is_training() {
    return !_training_worker.is_unemployed();
}