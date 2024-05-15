/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#pragma once

namespace HT{

class Node{
public:
    Node(wchar_t _char, int _frequency, Node* _left, Node* _right): character(_char), frequency(_frequency), leftNode(_left), rightNode(_right){}

    [[nodiscard]] int getFrequency() const noexcept { return frequency; } /// Inline
    [[nodiscard]] Node *getLeftNode() const noexcept { return leftNode; } /// Inline
    [[nodiscard]] Node *getRightNode() const noexcept { return rightNode; } /// Inline
    [[nodiscard]] wchar_t getCharacter() const noexcept { return character; } /// Inline

private:
    wchar_t character;
    int frequency;
    Node *leftNode, *rightNode;
};

}

