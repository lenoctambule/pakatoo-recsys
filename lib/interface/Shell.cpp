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
}

Shell::~Shell()
{
}

std::string Shell::create_instance(Request &req)
{
    (void) req;
    _instances.resize(_instances.size() + 1);
    return message_serialize(0, "Success");
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
    ret = (this->*(_resp_functions[req.get_cmd_id()]))(req);
    return ret;
}