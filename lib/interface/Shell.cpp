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
    return "Pong";
}

std::string Shell::handle_request(Request &req)
{
    std::string ret;

    ret = (this->*(_resp_functions[req.get_cmd_id()]))(req);
    return ret;
}