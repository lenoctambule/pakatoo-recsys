#include "interface/Shell.hpp"

std::string message_serialize(u_char code, std::string const &body)
{
    std::string ret;
    size_t      len = body.size();

    ret += std::string(1, code);
    ret += std::string(reinterpret_cast<const char *>(&len), sizeof(size_t));
    ret += std::string(body.c_str(), body.size());
    return ret;
}

Shell::Shell()
{
    _resp_functions.push_back(&Shell::ping);
    _resp_functions.push_back(&Shell::create_instance);
    _resp_functions.push_back(&Shell::stream_train);
    _resp_functions.push_back(&Shell::stream_delete);
    _resp_functions.push_back(&Shell::stream_init);
    _resp_functions.push_back(&Shell::eval);
}

Shell::~Shell()
{
}

static void deserialize_ts(size_t &uid, t_iclamped &clamped, Request &req)
{
    if (req.get_raw().size() != sizeof(uid) + sizeof(size_t) + sizeof(float) + 2 * sizeof(ushort) + sizeof(size_t))
        throw std::runtime_error("Invalid body");
    char const  *body = req.get_raw().c_str() + 2 * sizeof(ushort) + sizeof(size_t);
    uid         = *reinterpret_cast<const size_t *>(body);
    clamped.id  = *reinterpret_cast<const size_t *>(body += sizeof(size_t));
    clamped.val = *reinterpret_cast<const float *>(body += sizeof(size_t));
}

std::string Shell::stream_train(Request &req)
{
    std::string ret;
    size_t      uid;
    t_iclamped  clamped;
    Instance    &instance = _instances[req.get_instance_id()];

    deserialize_ts(uid, clamped, req);
    instance.stream_train(uid, clamped);
    return message_serialize(0, ret);
}

std::string Shell::stream_delete(Request &req)
{
    size_t  uid;

    if (req.get_raw().size() != sizeof(size_t) + 2 * sizeof(ushort) + sizeof(size_t))
        throw std::runtime_error("Invalid body");
    char const  *body = req.get_raw().c_str() + 2 * sizeof(ushort) + sizeof(size_t);
    uid         = *reinterpret_cast<const size_t *>(body);
    _instances[req.get_instance_id()].stream_delete(uid);
    return message_serialize(0, "Ok");
}

std::string Shell::stream_init(Request &req)
{
    std::deque<t_iclamped>  history;
    t_iclamped              tmp;
    size_t                  uid;
    char const              *end;
    char const              *ite;

    if (req.get_raw().size() < sizeof(size_t) + 2 * sizeof(ushort) + sizeof(size_t))
        throw std::runtime_error("Invalid body");
    char const  *body   = req.get_raw().c_str() + 2 * sizeof(ushort) + sizeof(size_t);
    uid                 = *reinterpret_cast<const size_t *>(body);
    body                += sizeof(size_t);
    ite                 = body;
    end                 = req.get_raw().c_str() + req.get_raw().size();
    while (ite + sizeof(t_iclamped) < end)
    {
        tmp = *reinterpret_cast<t_iclamped const *>(ite);
        history.push_back(tmp);
        ite += sizeof(t_iclamped);
    }
    _instances[req.get_instance_id()].stream_init(uid, history);
    return message_serialize(0, "Stream initialized");
}


static void deserialize_eval(size_t &uid, size_t &id, Request &req)
{
    if (req.get_raw().size() != sizeof(uid) + sizeof(id) + 2 * sizeof(ushort) + sizeof(size_t)) 
        throw std::runtime_error("Invalid body");
    char const  *body = req.get_raw().c_str() + 2 * sizeof(ushort) + sizeof(size_t);
    uid     = *reinterpret_cast<const size_t *>(body);
    id      = *reinterpret_cast<const size_t *>(body + sizeof(size_t));
}

std::string Shell::eval(Request &req)
{
    size_t      uid;
    size_t      id;
    float       eval;
    std::string ret;
    Instance    &instance = _instances[req.get_instance_id()];

    deserialize_eval(uid, id, req);
    eval = instance.stream_eval(uid, id);
    ret += std::string(reinterpret_cast<const char *>(&eval), sizeof(eval));
    return message_serialize(0, ret);
}

std::string Shell::create_instance(Request &req)
{
    (void) req;
    std::string ret;
    size_t      len = _instances.size();

    _instances.resize(len + 1);
    ret += std::string(reinterpret_cast<const char *>(&len), sizeof(size_t));
    std::cerr << "Created instance " << len << std::endl;
    return message_serialize(0, ret);
}

std::string Shell::ping(Request &req)
{
    (void) req;
    return message_serialize(0, "Pong");
}

std::string Shell::handle_request(Request &req)
{
    std::string ret;

    if (req.get_cmd_id() > _resp_functions.size())
        return message_serialize(1, "Unknown command");
    try {
        ret = (this->*(_resp_functions[req.get_cmd_id()]))(req);
    } catch (std::exception &e){
        return message_serialize(2, e.what());
    }
    return ret;
}