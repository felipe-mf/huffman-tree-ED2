/*
@author: Jean Bonadeo Dal Santo
@author: Felipe M. Fagundes
*/
#include "../../../header/Node.hpp"
HT::Node::Node(char _char, int _frequency, Node* _left, Node* _right): character(_char), frequency(_frequency), leftNode(_left), rightNode(_right){

}

int HT::Node::getFrequency(){
    return this->frequency;
}

HT::Node* HT::Node::getLeftNode(){
    return this->leftNode;
}
HT::Node* HT::Node::getRightNode(){
    return this->rightNode;
}

char HT::Node::getCharacter(){
    return character;
}
