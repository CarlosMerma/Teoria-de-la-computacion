//
// Created by Familiar on 25/06/2020.
//

#include "ejercicio.h"
#include "funciones.h"

void dibujar_arbol(){
    Node* root = new Node("           S");
    root->left = new Node("       A");
    root->left->left = new Node("   a");
    root->right = new Node("        B");
    root->right->left = new Node("         C");
    root->right->left->left = new Node("             a");
    root->right->right = new Node("    C");
    root->right->right->right = new Node("       a");
    cout << "Arbol generico " << endl;
    prin_level_by_level(root);
    cout << endl;
}
