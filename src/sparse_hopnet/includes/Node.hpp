#include <map>
#include <cstddef>

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
        double  E(std::deque<Node *> sample);
};