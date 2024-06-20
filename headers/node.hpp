/**
    @authors: Jean Bonadeo Dal Santo
              Felipe M. Fagundes
*/
#pragma once

namespace HT{

class node{
public:
    node(wchar_t _char, int _frequency, node* _left, node* _right) noexcept : character(_char), frequency(_frequency), leftnode(_left), rightnode(_right){}

    node() {};

    [[nodiscard]] int get_frequency() const noexcept { return frequency; } /// Inline
    [[nodiscard]] node *get_leftnode() const noexcept { return leftnode; } /// Inline
    [[nodiscard]] node *get_rightnode() const noexcept { return rightnode; } /// Inline
    [[nodiscard]] wchar_t get_character() const noexcept { return character; } /// Inline

private:
    wchar_t character;
    int frequency;
    node *leftnode, *rightnode;
};

}

