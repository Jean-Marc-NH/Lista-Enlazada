#include <iostream>
using namespace std;

template <typename T> struct Nodo {
    T valor;
    Nodo<T>* next;

    Nodo(T v, Nodo<T>* n = nullptr) {
        next = n;
        valor = v;
    }
};

template <typename T> struct LE {
    Nodo<T>* inicio;
    Nodo<T>* po;

    LE();
    void add(T);
    void del(T);
    bool find(T, Nodo<T>*&);
    void print();
    Nodo<T>* nodo();
};

template<typename T>
void merge(Nodo<T>* l1, Nodo<T>* l2) {

    Nodo<T>* tmp = l1;

    for (Nodo<T>* i = l1; i; tmp = i, i = i->next) {
        for (Nodo<T>* j = l2; j && j->valor < i->valor; j = j->next) {
            if (!(tmp == l1)) {
                tmp->next = j;
                l2 = l2->next;
                j->next = i;
            }
            else {
                l1 = l2;
                l2 = l2->next;
                j->next = i;
                i->next = l2;
            }
        }
    }

}


int main() {

    LE<int> a;
    LE<int> b;

    a.add(1);
    a.add(3);
    a.add(7);

    b.add(0);
    b.add(4);

    merge(a.nodo(), b.nodo());

    a.print();

    return 0;
}

template <typename T>
LE<T>::LE()
{
    po = nullptr;
    inicio = nullptr;
}

template <typename T>
void LE<T>::add(T v)
{

    if (!find(v, po)) {
        if (!po) {
            inicio = new Nodo<T>(v, inicio);
        }
        else {
            po->next = new Nodo<T>(v, po->next);
        }
    }
}

template <typename T>
void LE<T>::del(T v)
{
    Nodo<T>* tmp;
    if (find(v, po)) {
        if (po) {
            tmp = po->next;
            po->next = tmp->next;
            delete tmp;
        }
        else {
            tmp = inicio;
            inicio = tmp->next;
            delete tmp;

        }
    }
}

template <typename T>
bool LE<T>::find(T v, Nodo<T>*& pos)
{

    pos = nullptr;
    bool res = false;

    for (Nodo<T>* p = inicio; p && p->valor <= v; pos = p, p = p->next) {
        if (p->valor == v) {
            res = true;
            break;
        }
    }

    return res;
}

template <typename T>
void LE<T>::print()
{

    for (Nodo<T>* p = inicio; p; p = p->next) {
        cout << p->valor << " ";
    }
}

template <typename T>
Nodo<T>* LE<T>::nodo() {
    return inicio;
}
