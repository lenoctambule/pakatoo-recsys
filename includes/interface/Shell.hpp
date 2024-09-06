#pragma once

# include "ipc/Request.hpp"
# include "interface/Instance.hpp"

class Shell
{
    private :
        std::deque<Instance>                    _instances;
        std::deque<std::string (Shell::*)(Request &)>    _resp_functions;

        Shell(Shell const &a);
        Shell       &operator=(Shell const &a);

    public :
        Shell();
        ~Shell();

        std::string handle_request(Request &req);

        std::string ping(Request &req);
};