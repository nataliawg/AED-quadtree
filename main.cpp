#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// Basado en https://www.geeksforgeeks.org/quad-tree/

class Punto {
public:
    int x;
    int y;

    Punto(int xvalue, int yvalue) : x(xvalue), y(yvalue) {}
};

template<class T>
class NodoQuad {
public:
    Punto punto;
    T dato;
    NodoQuad* NW, * NE, * SW, * SE;
    NodoQuad(int x, int y, T data) : punto(Punto(x, y)), dato(data), NW(NULL), NE(NULL), SE(NULL), SW(NULL) {}
};

template<class T>
class QuadTree {
private:
    NodoQuad<T>* root;
    int limitX, limitY;

public:
    QuadTree(int x, int y) : limitX(x), limitY(y), root(NULL) {}

    int compare(Punto R, Punto K) {
        // Si retorna 1 es NW, si retorna 2 es NE, si es 3 SW, si es 4 es SE.

        if (R.x > K.x && R.y > K.y) {
            return 1;
        }
        else if (R.x < K.x && R.y > K.y) {
            return 2;
        }
        else if (R.x > K.x && R.y < K.y) {
            return 3;
        }
        else if (R.x < K.x && R.y < K.y) {
            return 4;
        }

        //si es 0 esta fuera del rango
        return 0;
    }

    void insertInTree(NodoQuad<T>* R, Punto K, T tag) {
        int comp = compare(R->punto, K);

        if (comp == 1) {
            if (R->NW != NULL) {
                insertInTree(R->NW, K, tag);
            }
            else {
                R->NW = new NodoQuad<T>(K.x, K.y, tag);
            }
        }
        else if (comp == 2) {
            if (R->NE != NULL) {
                insertInTree(R->NE, K, tag);
            }
            else {
                R->NE = new NodoQuad<T>(K.x, K.y, tag);
            }
        }
        else if (comp == 3) {
            if (R->SW != NULL) {
                insertInTree(R->SW, K, tag);
            }
            else {
                R->SW = new NodoQuad<T>(K.x, K.y, tag);
            }
        }
        else if (comp == 4) {
            if (R->SE != NULL) {
                insertInTree(R->SE, K, tag);
            }
            else {
                R->SE = new NodoQuad<T>(K.x, K.y, tag);
            }
        }
    }

    void insert(Punto K, T tag) {
        if (root == NULL) {
            root = new NodoQuad<T>(K.x, K.y, tag);
            cout << "Árbol estaba vacío, insertando root" << endl;
            return;
        }

        insertInTree(root, K, tag);
    }

    NodoQuad<T>* deleteNode(NodoQuad<T>* R, Punto K) {
        if (R == NULL) return NULL;

        // Si encontramos el nodo a eliminar
        if (R->punto.x == K.x && R->punto.y == K.y) {
            delete R;
            return NULL;
        }

        int comp = compare(R->punto, K);

        if (comp == 1) {
            R->NW = deleteNode(R->NW, K);
        }
        else if (comp == 2) {
            R->NE = deleteNode(R->NE, K);
        }
        else if (comp == 3) {
            R->SW = deleteNode(R->SW, K);
        }
        else if (comp == 4) {
            R->SE = deleteNode(R->SE, K);
        }

        return R;
    }

    void remove(Punto K) {
        if (root == NULL) {
            cout << "El árbol está vacío, no se puede eliminar." << endl;
            return;
        }

        root = deleteNode(root, K);
    }

    void getStruct() {
        if (!root) {
            cout << "Árbol vacío." << endl;
            return;
        }

        cout << "Raíz: " << root->dato << endl;
        if (root->NW) cout << "Raíz NW: " << root->NW->dato << endl;
        if (root->NE) cout << "Raíz NE: " << root->NE->dato << endl;
        if (root->SW) cout << "Raíz SW: " << root->SW->dato << endl;
        if (root->SE) cout << "Raíz SE: " << root->SE->dato << endl;
    }
};

int main() {
    QuadTree<char> Quadtree(127, 127);

    Punto A(70, 70);
    Punto B(20, 20);
    Punto C(100, 100);
    Punto D(60, 80);
    Punto E(5, 5);
    Punto F(50, 50);

    Quadtree.insert(A, 'A');
    Quadtree.insert(B, 'B');
    Quadtree.insert(C, 'C');
    Quadtree.insert(D, 'D');
    Quadtree.insert(E, 'E');
    Quadtree.insert(F, 'F');

    cout << "Estructura inicial del árbol:" << endl;
    Quadtree.getStruct();

    // Eliminar un nodo
    cout << "\nEliminando el nodo B (20, 20):" << endl;
    Quadtree.remove(B);
    Quadtree.getStruct();

    return 0;
}
