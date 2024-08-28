#pragma once

# include "core/SparseHN.hpp"

class Parser
{
    private :
        SparseHN    _hnet;

        Parser(Parser const &a);
        Parser       &operator=(Parser const &a);

    public :
        Parser();
        ~Parser();

        void    handle_request(std::string const &str);
};