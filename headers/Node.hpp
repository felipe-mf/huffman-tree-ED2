/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#pragma once

namespace HT{

class Node{
public:
    Node(char _char, int _frequency, Node* _left, Node* _right): character(_char), frequency(_frequency), leftNode(_left), rightNode(_right){}

    [[nodiscard]] int getFrequency() const noexcept { return frequency; } /// Inline
    [[nodiscard]] Node *getLeftNode() const noexcept { return leftNode; } /// Inline
    [[nodiscard]] Node *getRightNode() const noexcept { return rightNode; } /// Inline
    [[nodiscard]] char getCharacter() const noexcept { return character; } /// Inline

private:
    char character;
    int frequency;
    Node *leftNode, *rightNode;
};

}

