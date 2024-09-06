# include "ipc/Request.hpp"

Request::~Request()
{
}

Request::Request() : _cmd_id(0),
                    _instance_id(0),
                    _len(0),
                    _parsed_header(false),
                    _finished(false)
{
}

Request::Request(Request const &a) :
                    _cmd_id(a._cmd_id),
                    _instance_id(0),
                    _len(a._len),
                    _parsed_header(a._parsed_header),
                    _finished(a._finished)
{
}

Request &Request::operator=(Request const &a)
{
    _cmd_id         = a._cmd_id;
    _instance_id    = a._instance_id;
    _len            = a._len;
    _parsed_header  = a._parsed_header;
    _finished       = a._finished;
    return *this;
}

void    Request::receive_chunk(char const *chunk, size_t n)
{
    _raw.append(chunk, n);
    if (!_parsed_header
        && _raw.size() > (sizeof(ushort) + 2 * sizeof(size_t)))
    {
        char const *ptr = _raw.c_str();
        _instance_id    = *reinterpret_cast<ushort const *>(ptr);
        _cmd_id         = *reinterpret_cast<ushort const *>(ptr += sizeof(ushort));
        _len            = *reinterpret_cast<size_t const *>(ptr += sizeof(ushort));
        _parsed_header  = true;
    }
    if (_parsed_header && _raw.size() >= _len + (2 * sizeof(ushort) + sizeof(size_t)))
        _finished = true;
}

bool    Request::trunc_sent(ssize_t n) {
    _raw.erase(0, n);
    if (_raw.size() == 0)
        return true;
    return false;
}

bool    Request::isFinished() const
{
    return _finished;
}

std::string const   &Request::get_raw() const { return _raw; }
ushort              Request::get_cmd_id() const { return _cmd_id; }
size_t              Request::get_instance_id() const { return _instance_id; }
