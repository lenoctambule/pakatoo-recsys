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
    return (*this);
}

Node::~Node()
{
}

void    Node::interact(Node *target)
{
    auto ite    = _neigh.find(target);
    double d_w  = LR * this->getState() * target->getState();

    if (ite == _neigh.end())
        _neigh[target]  = d_w;
    else
        ite->second     += d_w;
}

void    Node::setState(double state) { _state = state; }

double  Node::getState() { return _state; }