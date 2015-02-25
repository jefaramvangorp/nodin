#include "Node.h"

Node::Node()
    : id_("")
    , name_("")
    , num_inputs_(0)
    , num_outputs_(0)
{

}

Node::Node(const std::string& id, const std::string &name, int numInputs, int numOutputs)
    : id_(id)
    , name_(name)
    , num_inputs_(numInputs)
    , num_outputs_(numOutputs)
{

}

