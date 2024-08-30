#pragma once

#include <iostream>

class Request
{
    private :
        std::string     _raw;
        u_char          _cmd_id;
        size_t          _len;
        bool            _parsed_header;

    public :
        Request();
        Request(Request const &a);
        ~Request();
        Request &operator=(Request const &a);

        void    receive_chunk(char *chunk, size_t n);
};