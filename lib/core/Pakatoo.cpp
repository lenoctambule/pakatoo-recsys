#include "core/Pakatoo.hpp"

Pakatoo::Pakatoo()
{}

Pakatoo::~Pakatoo()
{}

void    Pakatoo::train_stream(size_t uid, t_iclamped &clamped)
{
    size_t      sid;
    t_utrack    *ut;

    auto ite = _uid_to_sid.find(uid);
    if (ite == _uid_to_sid.end())
    {
        sid = graph.stream_create();
        ut = &_uid_to_sid[uid];
        ut->sid = sid;
        graph.stream_train(sid, clamped);
    }
    else
    {
        ut = &ite->second;
        graph.stream_train(ut->sid, clamped);
    }
    ut->ratings.push_back(clamped);
}

void    Pakatoo::train_batch(std::vector<t_iclamped> const &seq, std::vector<std::vector<t_iclamped>> const &ctx)
{
	(void) ctx;
    graph.batch_train(seq);
}

float   Pakatoo::eval(size_t uid, size_t id)
{
    return graph.eval(_uid_to_sid[uid].ratings, id);
}

void    Pakatoo::save(std::string const &path) {
    graph.save(path);
}