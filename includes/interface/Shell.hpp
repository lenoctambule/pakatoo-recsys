#pragma once

# include "core/SparseHN.hpp"

class Shell
{
    private :
        SparseHN    _hnet;

        Shell(Shell const &a);
        Shell       &operator=(Shell const &a);

    public :
        Shell();
        ~Shell();

        std::string handle_request(std::string const &str);
};