#include "Node.hpp"

Node::Node() {
}

Node::Node(Node const &a)
{
    *this = a;
}

Node    &Node::operator=(Node const &a)
{
    _neigh = a._neigh;
    return *this;
}

Node::~Node()
{
}

void    Node::interact(Node *target)
{
    
}

