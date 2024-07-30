#include "Node.hpp"

Node::Node() : _state(0)
{
}

Node::Node(Node const &a)
{
    *this = a;
}

Node    &Node::operator=(Node const &a)
{
    _neigh  = a._neigh;
    _id     = a._id;
    _state  = a._state;
    return *this;
}

Node::~Node()
{
}

void    Node::interact(Node *target)
{
}

void    Node::setState(double state)
{
    _state = state;
}

double  Node::getState()
{
    return _state;
}