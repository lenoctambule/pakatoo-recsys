#include <vector>

template <typename T>
class Matrix
{
    private :
        std::vector<T>                      _items;
        std::vector<double>                 _adj_matrix;

    public :
        Matrix();
        ~Matrix();
};