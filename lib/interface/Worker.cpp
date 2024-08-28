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
                *(j.res) = t_result{true,_recsys->eval(j.uid, j.id)};
            _mutjobs.lock();
            _jobs.pop();
            _mutjobs.unlock();
        }
        else
            _mutjobs.unlock();
    }
}

void    Worker::addTrainingJob(size_t uid, t_iclamped &clamped)
{
    _mutjobs.lock();
    _jobs.push(t_job{.is_training=true,
                    .clamped=clamped,
                    .uid=uid,
                    .id=0,
                    .res=NULL});
    _mutjobs.unlock();
}

void    Worker::addInferenceJob(size_t uid, size_t id, t_result *res)
{
    _mutjobs.lock();
    _jobs.push(t_job{.is_training=false,
                    .clamped={0,0},
                    .uid=uid,
                    .id=id,
                    .res=res});
    _mutjobs.unlock();
}

bool    Worker::is_unemployed() {
    return _jobs.empty();
}