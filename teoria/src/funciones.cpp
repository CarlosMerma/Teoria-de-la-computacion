//
// Created by Familiar on 25/06/2020.
//
#include "funciones.h"

void prin_level_by_level(Node* root){
    if(root== nullptr)return;
    queue<Node*> q;
    q.push(root);
    q.push(nullptr);
    while (q.size()>1){
        Node* curr = q.front();
        q.pop();
        if(curr== nullptr){
            cout << endl;
            q.push(nullptr);
            continue;
        }
        cout<< curr->key << " ";
        if(curr->left!=nullptr) q.push(curr->left);
        if(curr->right!=nullptr) q.push(curr->right);
    }
    cout << endl;
}
