#include "interface/Worker.hpp"

Worker::~Worker()
{
}

Worker::Worker(Pakatoo *recsys) : _recsys(recsys)
{
}

Worker::Worker(Worker const &a) : _recsys(a._recsys)
{
}

Worker &Worker::operator=(Worker const &a)
{
    _recsys = a._recsys;
    return *this;
}

void    Worker::init()
{
    while (true)
    {
        _mutjobs.lock();
        if (!_jobs.empty())
        {
            t_job   j = _jobs.top();
            _mutjobs.unlock();
            if (j.is_training)
                _recsys->train_stream(j.uid, j.clamped);
            else
                _recsys->eval(j.uid, j.id);
            _mutjobs.lock();
            _jobs.pop();
        }
        _mutjobs.unlock();
    }
}

void    Worker::addTrainingJob(size_t uid, t_iclamped &clamped)
{
    _mutjobs.lock();
    _jobs.push(t_job{.is_training=true,
                    .clamped=clamped,
                    .uid=uid,
                    .id=0});
    _mutjobs.unlock();
}

void    Worker::addInferenceJob(size_t uid, size_t id)
{
    _mutjobs.lock();
    _jobs.push(t_job{.is_training=false,
                    .clamped={0,0},
                    .uid=uid,
                    .id=id});
    _mutjobs.unlock();
}