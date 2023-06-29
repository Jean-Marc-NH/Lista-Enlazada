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


template <typename T>
struct Iterator {
    Nodo<T>* it;
    void operator =(Nodo<T>* valor)
    {
        it = valor;
    }
    void operator =(T valor)
    {
        it->valor = valor;
    }

    Nodo<T>* operator++(int)
    {
        it = it->next;
        return it;
    }

    void operator +=(T v) {
        it->valor = it->valor + v;
    }

    void operator -=(T v) {
        it->valor = it->valor - v;
    }

    T operator*()
    {
        return it->valor;
    }

    bool operator<=(Nodo<T>* otro)
    {
        return it->valor <= otro->valor;
    }

    friend istream& operator>>(istream& input, Iterator D)
    {
        input >> (*D.it->valor);
        return input;
    }

};

template <typename T, typename I> struct LE {
    Nodo<T>* inicio;
    Nodo<T>* po;
    typedef I it_vector;

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

    LE<int,Iterator<int>> a;
    LE<int,Iterator<int>>::it_vector It;

    a.add(1);
    a.add(3);
    a.add(78);
    a.add(31);
    a.add(-23);
    a.add(7);

    cout << "Inicio" << " -> ";
    for (It = a.inicio; It.it; It++) {
        It -= 10;
        cout << *It << " -> ";
    }
    cout << "NULL\n";

    cout << "Inicio" << " -> ";
    for (It = a.inicio; It.it;It++) {
        It += 10;
        cout << *It << " -> ";
    }
    cout << "NULL\n";

    return 0;
}

template <typename T, typename I>
LE<T, I>::LE()
{
    po = nullptr;
    inicio = nullptr;
}

template <typename T, typename I>
void LE<T, I>::add(T v)
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

template <typename T, typename I>
void LE<T, I>::del(T v)
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

template <typename T, typename I>
bool LE<T, I>::find(T v, Nodo<T>*& pos)
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

template <typename T, typename I>
void LE<T, I>::print()
{

    for (Nodo<T>* p = inicio; p; p = p->next) {
        cout << p->valor << " ";
    }
}
