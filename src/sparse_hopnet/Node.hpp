#include <deque>
#include <cstddef>

typedef struct s_neigh
{
    Node    *item;
    double  w;
} t_neigh;

class   Node
{
    private :
        std::deque<t_neigh>  _neigh;

        Node(Node const &a);
        Node &operator=(Node const &a);

    public :
        Node();
        ~Node();

        void    setNeigh(size_t target, double w);
        t_neigh getNeigh(size_t id);
};