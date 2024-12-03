#ifndef GAME_TREE_H
#define GAME_TREE_H

#include "node.h"
#include <functional>

class GameTree 
{
public:
    std::unique_ptr<Node> root;

    GameTree(int numActions);

    void BuildTree(std::unique_ptr<Node> node, int depth, int maxDepth, int numActions);

    ~GameTree();
private:
    void DeleteTree(std::unique_ptr<Node> node);

    double CalculateUtility();

    int numActions;
};



#endif