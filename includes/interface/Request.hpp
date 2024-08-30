#pragma once

#include <iostream>

class Request
{
    private :
        std::string     _raw;
        u_char          _cmd_id;
        size_t          _instance_id;
        size_t          _len;
        bool            _parsed_header;
        bool            _finished;

    public :
        Request();
        Request(Request const &a);
        ~Request();
        Request &operator=(Request const &a);

        void    receive_chunk(char *chunk, size_t n);
        bool    isFinished() const;
};