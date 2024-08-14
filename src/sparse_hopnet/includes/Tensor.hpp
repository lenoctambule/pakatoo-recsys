#pragma once

# include <vector>
# include <deque>
# include <unordered_map>
# include <cstddef>
# include <fstream>
# include <sstream>
# include <sys/stat.h>

# define FSIG "PK2\00"

typedef std::unordered_map<size_t, std::vector<float>>   adj_t;
typedef std::deque<adj_t>                                tensor_t;

class Tensor
{
    private :
        tensor_t    _tensor;
        size_t      _depth;

        Tensor();
        Tensor(Tensor const &a);
        Tensor  &operator=(Tensor const &a);

        void    save_adj(std::string const &path, std::ofstream &out, size_t idx);
        void    load_adj(std::ifstream &in);

    public :
        Tensor(size_t _depth);
        ~Tensor();

        size_t                  size();
        size_t                  getDepth();

        std::vector<float>      &get(size_t x, size_t y);
        std::vector<float>      &operator()(size_t x, size_t y);
        void                    save(std::string const &path);
        void                    load(std::string const &path);
};