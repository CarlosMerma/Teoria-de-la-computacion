//
// Created by Familiar on 25/06/2020.
//

#ifndef TEORIA_ARBOL_H
#define TEORIA_ARBOL_H

struct Node{
    string key;
    Node* left;
    Node* right;
    Node(string k){
        key = k;
        left = right = nullptr;
    }
};

#endif //TEORIA_ARBOL_H
