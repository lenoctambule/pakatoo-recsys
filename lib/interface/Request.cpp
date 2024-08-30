# include "interface/Request.hpp"

Request::~Request()
{
}

Request::Request() : _cmd_id(0),
                    _len(0),
                    _parsed_header(false)
{
}

Request::Request(Request const &a) :
                    _cmd_id(a._cmd_id),
                    _len(a._len),
                    _parsed_header(a._parsed_header)
{
}

Request &Request::operator=(Request const &a)
{
    _cmd_id = a._cmd_id;
    _len = a._len;
    _parsed_header = a._parsed_header;
    return *this;
}

void    Request::receive_chunk(char *chunk, size_t n)
{
    _raw.append(chunk, n);
    if (!_parsed_header && 
        _raw.size() > (sizeof(u_char) + sizeof(size_t)))
    {
        _len = *reinterpret_cast<size_t const *>(_raw.c_str());
        _cmd_id = *reinterpret_cast<u_char const *>(_raw.c_str() + sizeof(size_t));
    }
}