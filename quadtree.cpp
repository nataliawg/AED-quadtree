#include <iostream>
#include <vector>
#include <stdexcept>
#include <SFML/Graphics.hpp>
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

public:

    NodoQuad<T>* root;
    int limitX, limitY;

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
        //si es 0 está fuera del rango
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

    void display() {
        if (root == NULL) {
            cout << "Árbol vacío." << endl;
        }
        else {
            getStruct();
        }
    }

    // Método de búsqueda recursiva
    NodoQuad<T>* searchInTree(NodoQuad<T>* node, Punto K) {
        if (node == NULL) return NULL;

        // Si encontramos el nodo
        if (node->punto.x == K.x && node->punto.y == K.y) {
            return node;
        }

        // Si el nodo no es el que buscamos, seguimos buscando en los cuadrantes correspondientes
        int comp = compare(node->punto, K);
        if (comp == 1) return searchInTree(node->NW, K);
        else if (comp == 2) return searchInTree(node->NE, K);
        else if (comp == 3) return searchInTree(node->SW, K);
        else if (comp == 4) return searchInTree(node->SE, K);

        return NULL; // Nodo no encontrado
    }

    // Método de búsqueda
    NodoQuad<T>* search(Punto K) {
        return searchInTree(root, K);
    }

    void draw(sf::RenderWindow& window, NodoQuad<T>* node, sf::VertexArray& lines) {
        if (node == NULL) return;

        sf::CircleShape point(5);
        point.setFillColor(sf::Color::Red);
        point.setPosition(node->punto.x, node->punto.y);
        window.draw(point);

        draw(window, node->NW, lines);
        draw(window, node->NE, lines);
        draw(window, node->SW, lines);
        draw(window, node->SE, lines);
    }
};
