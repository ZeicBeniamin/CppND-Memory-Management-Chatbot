#include "graphedge.h"
#include "graphnode.h"

#include <iostream>

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode() {}

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

void GraphNode::MoveChatbotHere(ChatBot chatbot)
{
    _chatBot = std::move(chatbot);

    // The change is made visible in both places
    /// Since chatBot has been moved, the pointer to it must be updated
    /// in chatLogic

    // Because "exclusive ownership" was chosen as the copying policy in the

    // _chatBot.UpdateChatBotInChatLogic();
    _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(std::move(_chatBot));
    /// COMMENTED OUT - chatBot is no longer a pointer
    /// Its lifetime will be handled by the node wich contains it
    /// Resources will be invalidated at move
    // _chatBot = nullptr; // invalidate pointer at source
}

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    /// MODIFIED - `get` pointer to edge
    return _childEdges[index].get();
}