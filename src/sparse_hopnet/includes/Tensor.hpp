#pragma once
# include <vector>
# include <deque>
# include <map>
# include <cstddef>
# include <fstream>
# include <sstream>
# include <sys/stat.h>

# define FSIG "PK2\00"

typedef std::map<size_t, std::vector<double>>   adj_t;
typedef std::deque<adj_t>                       tensor_t;

class Tensor
{
    private :
        tensor_t    _tensor;
        size_t      _depth;

        Tensor();
        void    save_adj(std::string const &path, size_t idx);

    public :
        Tensor(size_t _depth);
        ~Tensor();

        size_t                  size();
        size_t                  getDepth();

        std::vector<double>     &get(size_t x, size_t y);
        std::vector<double>     &operator()(size_t x, size_t y);
        void                    save(std::string const &path);
        void                    load(std::string const &path);
};