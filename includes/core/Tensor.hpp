#pragma once

# include <vector>
# include <deque>
# include <unordered_map>
# include <cstddef>
# include <fstream>
# include <sstream>
# include <iostream>
# include <sys/stat.h>

# define FSIG "PK2\00"

typedef std::unordered_map<size_t, std::vector<float>>  adj_t;
typedef std::unordered_map<size_t, adj_t>               tensor_t;

class Tensor
{
    private :
        tensor_t            _tensor;
        std::vector<float>  _default;
        size_t              _depth;
        size_t              _ec;
        size_t              _emax;
        bool                _is_symmetric;

        Tensor();
        Tensor(Tensor const &a);
        Tensor  &operator=(Tensor const &a);

        void    save_adj(std::ofstream &out, size_t idx);
        void    load_adj(std::ifstream &in);

    public :
        Tensor(size_t _depth, bool is_symmetric);
        ~Tensor();

        size_t                  size() const;
        size_t                  getDepth() const;
        double                  getSparsity() const;

        std::vector<float>          &get_or_create(size_t x, size_t y);
        const std::vector<float>    &get(size_t x, size_t y) const;
        std::vector<float>          &operator()(size_t x, size_t y);
        void                        save(std::string const &path);
        void                        load(std::string const &path);
};