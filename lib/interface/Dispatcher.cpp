#include "interface/Dispatcher.hpp"

Dispatcher::Dispatcher(ushort n_threads) :
    _inference_workers(n_threads, Worker(_recsys)),
    _training_worker(_recsys)
{
}

Dispatcher::~Dispatcher()
{
}

void    Dispatcher::init()
{
    _training_worker();
    for (size_t i = 0; i < _inference_workers.size(); i++)
        _inference_workers[i]();
}

void    Dispatcher::dispatch_training(size_t uid, t_iclamped &clamped) {
    _training_worker.addTrainingJob(uid, clamped);
}

size_t  Dispatcher::dispatch_eval(size_t uid, size_t id)
{
    size_t wid = std::rand() % _inference_workers.size();
    _inference_workers[wid].addInferenceJob(uid, id);
    return wid;
}