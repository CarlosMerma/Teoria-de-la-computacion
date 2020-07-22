//
// Created by Familiar on 24/06/2020.
//

#include "tipos.h"
#include "ejercicio.h"

#define MAX 100
#define for(i,a,b) for(i=a;i<b; i++)

string gram[MAX][MAX]; //Para almacenar la gramática ingresada
string dpr[MAX];
int p,np;     //np-> numero de producciones

inline string concat( string a, string b) {    //concatena no terminales únicos
    int i;
    string r = a;
    for(i, 0, b.length()) {
        if (r.find(b[i]) > r.length()) {
            r += b[i];
        }
    }
    return r;
}

inline void break_gram(string a){  //separa el lado derecho de la gramática ingresada
    int i;
    p=0;
    while(a.length()){
        i=a.find("|");
        if(i>a.length()){
            dpr[p++] = a;
            a="";
        }
        else{
            dpr[p++] = a.substr(0,i);
            a = a.substr(i+1,a.length());
        }
    }
}

inline int lchomsky(string a){ //comprueba si el LHS de la gramática ingresada está en FNC
    if(a.length() == 1 && a[0] >= 'A' && a[0] <= 'Z')
        return 1;
    return 0;
}

inline int rchomsky(string a){ //comprueba si RHS de gramática está en FNC
    if (a.length() == 1 && a[0] >= 'a' && a[0] <= 'z')
        return 1;
    if (a.length() == 2 && a[0] >= 'A' && a[0] <='Z' && a[1] >= 'A' && a[1] <= 'Z')
        return 1;
    return 0;
}

inline string search_prod(string p){   //devuelve una cadena concatenada de variables que pueden producir la cadena p
    int j, k;
    string r = "";
    for(j, 0, np){
        k = 1;
        while(gram[j][k] != ""){
            if(gram[j][k] == p){
                r = concat(r,gram[j][0]);
            }
            k++;
        }
    }
    return r;
}

inline string gen_comb(string a, string b){ //crea todas las combinaciones de variables de a y b. Por ejemplo: BA * AB = {BA, BB, AA, BB}
    int i,j;
    string pri = a,re = "";
    for(i, 0, a.length()) {
        for(j, 0, b.length()) {
            pri = "";
            pri = pri + a[i] + b[j];
            re = re + search_prod(pri);        //busca si las producciones generadas pueden ser creadas o no
        }
    }
    return re;
}

int main(){
    int i, pt, j, l, k;
    string a, str, r, pr, start;
    cout << endl;
    cout << "Ingrese la variable de inicio: ";
    cin >> start;
    cout << endl;
    cout << "Numero de producciones: ";
    cin >> np;
    for(i, 0, np){
        cin >> a;
        pt = a.find("->");
        gram[i][0] = a.substr(0,pt);
        if (lchomsky(gram[i][0]) == 0){
            cout << endl;
            cout << "La gramática no está en forma de Chomsky";
            abort();
        }
        a = a.substr(pt+2, a.length());
        break_gram(a);
        for(j, 0 ,p){
            gram[i][j+1]=dpr[j];
            if (rchomsky(dpr[j]) == 0){
                cout << endl;
                cout << "La gramática no está en forma de Chomsky";
                abort();
            }
        }
    }
    string matrix[MAX][MAX],st;
    cout << endl;
    cout << "Ingrese la cadena a generar: ";
    cin >> str;
    for(i, 0, str.length()){    //Asigna valores a la diagonal principal de la matriz
        r = "";
        st = "";
        st += str[i];
        for(j, 0, np){
            k = 1;
            while(gram[j][k] != ""){
                if(gram[j][k] == st){
                    r = concat(r,gram[j][0]);
                }
                k++;
            }
        }
        matrix[i][i] = r;
    }

    for(k, 1, str.length()){    //Asigna valores a la mitad superior de la matriz.
        for(j, k, str.length()){
            r = "";
            for(l, j-k ,j){
                pr = gen_comb(matrix[j-k][l],matrix[l+1][j]);
                r = concat(r,pr);
            }
            matrix[j-k][j] = r;
        }
    }

    for(i, 0, str.length()){ //Imprime la matriz
        k = 0;
        l = str.length()-i-1;
        for(j, l, str.length()){
            cout << "|" << setw(5)<< matrix[k++][j] << "|";
        }
        cout << endl;
    }

    for(i, 0, start.length()) {
        if (matrix[0][str.length() - 1].find(start[i]) <= matrix[0][str.length() - 1].length()) {// Comprueba si el último elemento de la primera fila contiene una variable de Inicio
            cout << "Cadena generado. " << endl;
            cout << endl;
            //dibujar_arbol();
            return 0;
        }
    }
    cout <<"Gramática no generada";

    return 0;
}

