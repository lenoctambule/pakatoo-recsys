#include "interface/Worker.hpp"

Worker::~Worker()
{
}

Worker::Worker(Pakatoo &recsys) : _recsys(recsys)
{
}

Worker::Worker(Worker const &a) : _recsys(a._recsys)
{
    (void) a;
}

Worker &Worker::operator=(Worker const &a)
{
    (void) a;
    return *this;
}

void    Worker::operator()()
{
    std::cerr << "Worker started." << std::endl;
    while (true)
    {
        if (!_jobs.empty())
        {
            t_job &j = _jobs.top();
            if (j.is_training)
                _recsys.train_stream(j.uid, j.clamped);
            else
                _recsys.eval(j.uid, j.id);
        }
        usleep(50);
    }
    std::cerr << "Worker stopped." << std::endl;
}

void    Worker::addTrainingJob(size_t uid, t_iclamped &clamped)
{
    _jobs.push(t_job{.is_training=true,
                    .clamped=clamped,
                    .uid=uid,
                    .id=0});
}

void    Worker::addInferenceJob(size_t uid, size_t id)
{
    _jobs.push(t_job{.is_training=false,
                    .clamped={0,0},
                    .uid=uid,
                    .id=id});
}