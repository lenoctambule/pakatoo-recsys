#pragma once

#include <iostream>

class Request
{
    private :
        std::string     _raw;
        ushort          _cmd_id;
        ushort          _instance_id;
        size_t          _len;
        bool            _parsed_header;
        bool            _finished;

    public :
        Request();
        Request(Request const &a);
        ~Request();
        Request &operator=(Request const &a);

        void    receive_chunk(char const *chunk, size_t n);
        bool    trunc_sent(ssize_t n);

        std::string const   &get_raw() const;
        ushort              get_cmd_id() const;
        size_t              get_instance_id() const;
        bool                isFinished() const;

        friend std::ostream    &operator<<(std::ostream &s, const Request &r)
        {
            s << "cmd_id\t=" << r._cmd_id
            << "\ninst_id\t=" << r._instance_id
            << "\nlen\t=" << r._len
            << std::endl;

            return s;
        }
};

