#include "interface/Instance.hpp"

Instance::Instance()
{}

Instance::~Instance()
{}

void    Instance::stream_train(size_t uid, t_iclamped const &clamped) {
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
    ut->ratings.push_back(clamped);
}

float   Instance::stream_eval(size_t uid, size_t id) {
    return cf_graph.eval(_users[uid].ratings, id);
}

void    Instance::stream_init(size_t uid, std::deque<t_iclamped> const &clamped)
{
    _users[uid] = t_utrack{.sid=cf_graph.stream_init(clamped),
                            .ratings=std::vector<t_iclamped>(clamped.begin(), clamped.end())};
}

void    Instance::stream_delete(size_t uid)
{
    cf_graph.stream_delete(_users[uid].sid);
    _users.erase(uid);
}

void    Instance::batch_train(std::vector<t_iclamped> const &seq) {
    cf_graph.batch_train(seq);
}

void    Instance::save(std::string const &path) {
    cf_graph.save(path);
}