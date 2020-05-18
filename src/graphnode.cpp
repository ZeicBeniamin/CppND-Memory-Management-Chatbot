#include "graphedge.h"
#include "graphnode.h"

#include <iostream>

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////
    std::cout << "GraphNode Destructor\n";

    // Check if the current node handles any ChatBot object
    if (_chatBot != nullptr) {
        // std::cout << "Attempting ChatBot deletion\n";
        delete _chatBot;
        // std::cout << "Attempting ChatBot invalidation\n";
        _chatBot = nullptr;
    }

    // std::cout << "GraphNode Destructor, leaving ...\n";

    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

/// MODIFIED - receive unique_ptr instead of raw pointer to GraphEdge
void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge)
{
    _childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot *chatbot)
{
    _chatBot = chatbot;
    // The change is made visible in both places
    _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{  
    newNode->MoveChatbotHere(_chatBot);
    _chatBot = nullptr; // invalidate pointer at source
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////

    /// MODIFIED - `get` pointer to edge
    return _childEdges[index].get();

    ////
    //// EOF STUDENT CODE
}