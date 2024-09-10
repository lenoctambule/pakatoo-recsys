#include "interface/Instance.hpp"

Instance::Instance()
{}

Instance::~Instance()
{}

void    Instance::stream_train(size_t uid, t_iclamped &clamped)
{
    size_t      sid;
    t_utrack    *ut;

    auto ite = _users.find(uid);
    if (ite == _users.end())
    {
        sid = cf_graph.stream_create();
        ut = &_users[uid];
        ut->sid = sid;
        cf_graph.stream_train(sid, clamped);
    }
    else
    {
        ut = &ite->second;
        cf_graph.stream_train(ut->sid, clamped);
    }
}

void    Instance::batch_train(std::vector<t_iclamped> const &seq, std::vector<std::vector<t_iclamped>> const &ctx)
{
	(void) ctx;
    cf_graph.batch_train(seq);
}

float   Instance::stream_eval(size_t uid, size_t id)
{
    return cf_graph.eval(_users[uid].ratings, id);
}

void    Instance::save(std::string const &path) {
    cf_graph.save(path);
}