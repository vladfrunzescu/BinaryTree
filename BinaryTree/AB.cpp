#include "AB.hpp"
#include "IteratorAB.hpp"
#include <exception>
#include <string>

AB::AB() {
    /* de adaugat */
    //cap = 10;
    lg = 0;
    nodes = new Nod[cap];

    radacina = -1;
    //primLiber = 1;

    for (int i = 0; i < cap; i++)
    {
        nodes[i].dr = -1;
        nodes[i].stg = -1;
        nodes[i].pozitie = -1;
    }

}

AB::AB(const AB& ab) {
    /* de adaugat */

    radacina = ab.radacina;
    primLiber = ab.primLiber;
    lg = ab.lg;
    cap = ab.cap;
    nodes = ab.nodes;

}

AB::AB(TElem e) {
    /* de adaugat */

    AB a;
    if (lg == cap)
        resize();
    int poz = primLiber;
    a.nodes[poz].el = e;
    a.nodes[poz].stg = -1;
    a.nodes[poz].dr = -1;
    a.nodes[poz].pozitie = poz;
    a.lg++;
    actualizare(a);
}

AB::AB(const AB& st, TElem e, const AB& dr) {
    /* de adaugat */
    AB a;
    if (lg == cap)
        resize();

    int poz = primLiber;
    a.nodes[poz].el = e;
    a.nodes[poz].stg = st.nodes[radacina].pozitie;
    a.nodes[poz].dr = dr.nodes[radacina].pozitie;
    a.nodes[poz].pozitie = poz;
    a.lg++;
    actualizare(a);
}

void AB::resize()
{
    Nod* newElems = new Nod[cap * 2];
    for (int i = 0; i < cap; i++)
        newElems[i] = nodes[i];
    primLiber= cap;
    cap *= 2;
    delete[] nodes;
    nodes = newElems;

}

void AB::actualizare(AB a)
{
    while (a.nodes[primLiber].pozitie == -1)
    {
        a.primLiber++;
    }

}

AB AB::arbore(int rad) const
{

    if (nodes[rad].stg == -1)
        return AB(nodes[radacina].el);

    if (nodes[rad].dr == -1)
        return AB(nodes[radacina].el);

    AB st = arbore(nodes[rad].stg);
    TElem info = nodes[rad].el;
    AB dr = arbore(nodes[rad].dr);
    
    return AB(st, info, dr);
}

void AB::adaugaSubSt(const AB& st) {
    /* de adaugat */

    if (radacina == -1)
        throw std::exception();
    else
    {
        nodes[radacina].stg = st.nodes[radacina].pozitie;
    }
}

void AB::adaugaSubDr(const AB& dr) {
    /* de adaugat */
    if (radacina == -1)
        throw std::exception();
    else
    {
        nodes[radacina].dr = dr.nodes[radacina].pozitie;
    }

}

TElem AB::element() const {
    /* de adaugat */

    return nodes[radacina].el;
}

AB AB::stang() const {
    /* de adaugat */
    if (radacina == -1)
        throw std::exception();
    else
    {
        if (nodes[radacina].stg == -1)
            return AB();
        return  arbore(nodes[radacina].stg);
    }

}

AB AB::drept() const {
    /* de adaugat */

    if (radacina == -1)
        throw std::exception();
    else
    {
        if (nodes[radacina].dr == -1)
            return AB();
        return  arbore(nodes[radacina].dr);
    }
}

AB::~AB() {
    /* de adaugat */

    delete[]nodes;
}

bool AB::vid() const {
    /* de adaugat */

    return radacina==-1;
}


IteratorAB* AB::iterator(string s) const {
    if (s == "preordine")
        return new IteratorPreordine(*this);
    if (s == "inordine")
        return new IteratorInordine(*this);
    if (s == "postordine")
        return new IteratorPostordine(*this);
    if (s == "latime")
        return new IteratorLatime(*this);
    return nullptr;
};
