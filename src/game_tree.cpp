#include "game_tree.h"

GameTree::GameTree(int numActions) : numActions(numActions) 
{
    root = std::make_unique<Node>(NodeType::PlayerNode, numActions);
}

void GameTree::BuildTree(std::unique_ptr<Node>& node, int depth, int maxDepth, int numActions)
{
    if(depth == maxDepth)
    {
        node->type = NodeType::TerminalNode;
        node->utility = this->CalculateUtility();
        return;
    }
    NodeType childType = (depth % 2 == 0) ? NodeType::PlayerNode : NodeType::OpponentNode;
    for(int i = 0; i < numActions; i++)
    {
        std::unique_ptr<Node> child = std::make_unique<Node>(childType, numActions);
        node->children.push_back(std::move(child));
        BuildTree(node->children.back(), depth + 1, maxDepth, numActions);
    }
}

double GameTree::CalculateUtility()
{
    return 0.0;
}

