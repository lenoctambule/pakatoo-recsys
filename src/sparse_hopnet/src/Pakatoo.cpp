#include "Pakatoo.hpp"

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
        sid = _seqhn.stream_create();
        ut = &_uid_to_sid[uid];
        ut->sid = sid;
        _seqhn.stream_train(sid, clamped);
        
    }
    else
    {
        ut = &ite->second;
        _seqhn.stream_train(ut->sid, clamped);
    }
    ut->ratings.push_back(clamped);
}

void    Pakatoo::train_batch(std::vector<t_iclamped> const &seq, std::vector<std::vector<t_iclamped>> const &ctx)
{
    _seqhn.batch_train(seq);
    for (size_t i = 0; i < ctx.size(); i++)
        _ctxhn.batch_train(ctx[i]);
}

float   Pakatoo::eval(size_t uid, size_t id)
{
    return _seqhn.eval(_uid_to_sid[uid].ratings, id);
}