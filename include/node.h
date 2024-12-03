#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>

enum class NodeType {PlayerNode, OpponentNode, BucketNode, TerminalNode};

struct Node
{
    NodeType type;
    std::vector<double> regrets;                    // regret value for each action (Call, raise, fold, check)
    std::vector<double> strategy;                   // frequency for each action
    std::vector<std::unique_ptr<Node>> children;    
    double utility;                                 // payout, only applicable at terminal node

    // initializes a uniform strategy, call, raise, fold
    Node(NodeType t, int numActions) 
        : type(t), regrets(numActions, 0.0), 
          strategy(numActions, (t == NodeType::PlayerNode) ? 1.0 / numActions : 0.0),
          utility(0.0) {}

    ~Node() = default;
    

};

#endif