#include <map>
# include <cstddef>

# define LR 0.3

class   Node
{
    private :
        std::map<Node *, double>    _neigh;
        size_t                      _id;
        double                      _state;

    public :
        Node();
        ~Node();
        Node(Node const &a);
        Node &operator=(Node const &a);

        void    setState(double state);
        double  getState();
        void    interact(Node *target);
        double  E();
};