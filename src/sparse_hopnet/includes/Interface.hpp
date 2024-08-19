#pragma once

# include "SparseHN.hpp"

class Interface
{
    private :
        SparseHN    _hnet;

        Interface(Interface const &a);
        Interface       &operator=(Interface const &a);

    public :
        Interface();
        ~Interface();

        void    handle_request(std::string const &str);
};