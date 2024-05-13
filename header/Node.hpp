/*
@author: Jean Bonadeo Dal Santo
@author: Felipe M. Fagundes
*/
#pragma once

namespace HT{
        class Node{
        private:
            char character;
            int frequency;
            Node *leftNode;
            Node *rightNode;
        public:
            Node(char _char, int _frequency, Node* _left, Node* _right);
            int getFrequency();
            Node *getLeftNode();
            Node *getRightNode();
            char getCharacter();

    };
}
