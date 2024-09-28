#pragma once

# include "ipc/Request.hpp"
# include "interface/Instance.hpp"

class Shell
{
    private :
        std::deque<Instance>                            _instances;
        std::deque<std::string (Shell::*)(Request &)>   _resp_functions;

        Shell(Shell const &a);
        Shell       &operator=(Shell const &a);

    public :
        Shell();
        ~Shell();

        std::string handle_request(Request &req);

        std::string ping(Request &req);
        std::string create_instance(Request &req);
        std::string stream_train(Request &req);
        std::string stream_delete(Request &req);
        std::string stream_init(Request &req);
        std::string eval(Request &req);
        std::string save(Request &req);
};

std::string message_serialize(u_char code, std::string const &body);