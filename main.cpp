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
};

template<typename T>
void merge(Nodo<T>* h1, Nodo<T>* h2) {

    Nodo<T>* p, * q, * ap, * aq;
    ap = NULL;
    p = h1;
    q = h2;
    aq = q;


    for (; p; ap = p, p = p->next)
    {
        if (!(p->valor < q->valor))
        {
            if (ap) {
                q = q->next;
                ap->next = aq;
                aq->next = p;
                aq = q;
            }
            else {
                q = q->next;
                aq->next = p;
                h1 = aq;
                aq = q;
            }
        }
    }

    h2 = NULL;
}


int main() {

    LE<int> a;
    LE<int> b;

    a.add(1);
    a.add(3);
    a.add(7);

    b.add(0);
    b.add(4);

    merge(a.inicio, b.inicio);

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
