#include "interface/Shell.hpp"

Shell::Shell()
{
    _resp_functions.push_back(&Shell::ping);
}

Shell::~Shell()
{
}

std::string Shell::ping(Request &req)
{
    (void) req;
    return std::string("\x00Pong", 5);
}

std::string Shell::handle_request(Request &req)
{
    std::string ret;

    if (req.get_cmd_id() > _resp_functions.size())
        return std::string("\x01", 1);
    ret = (this->*(_resp_functions[req.get_cmd_id()]))(req);
    return ret;
}