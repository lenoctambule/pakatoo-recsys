#include "Pakatoo.hpp"

Pakatoo::Pakatoo()
{}

Pakatoo::~Pakatoo()
{}

void    Pakatoo::train(std::vector<t_iclamped> const &seq, std::vector<std::vector<t_iclamped>> const &ctx)
{
    _seqhn.train(seq);
    for (size_t i = 0; i < ctx.size(); i++)
        _ctxhn.train(ctx[i]);
}

float   Pakatoo::eval(std::vector<t_iclamped> const &seq, std::vector<t_iclamped> const &ctx, size_t id)
{
    float   p_ctx, p_seq;

    p_ctx = _seqhn.eval(seq, id);
    p_seq = _ctxhn.eval(ctx, 0);
    return (p_ctx + p_seq) / 2;
}