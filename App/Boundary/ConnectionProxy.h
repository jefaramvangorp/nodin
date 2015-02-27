#ifndef APP_BOUNDARY_CONNECTIONPROXY_H_
#define APP_BOUNDARY_CONNECTIONPROXY_H_

// STD.
#include <string>

class ConnectionProxy
{
public:
    ConnectionProxy(const std::string& outputNodeID, int outputIndex,
                    const std::string& inputNodeID, int inputIndex)
        : output_node_id_(outputNodeID)
        , input_node_id_(inputNodeID)
        , output_index_(outputIndex)
        , input_index_(inputIndex)
    {}

    const std::string& outputNodeID() const { return output_node_id_; }
    int outputIndex() const { return output_index_; }
    const std::string& inputNodeID() const { return input_node_id_; }
    int inputIndex() const { return input_index_; }

private:

    std::string output_node_id_;
    std::string input_node_id_;
    int output_index_;
    int input_index_;
};

#endif // APP_BOUNDARY_CONNECTIONPROXY_H_
