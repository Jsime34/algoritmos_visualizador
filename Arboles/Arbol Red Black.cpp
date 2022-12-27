#include <iostream>
#include <fstream>
template <class T>
class NodoRB
{
public:
    T m_Dato;
    NodoRB<T> *m_pSon[2];
    NodoRB<T> *m_pDad;
    bool m_Color;
    NodoRB(T d)
    {
        m_Dato = d;
        m_pSon[0] = m_pSon[1] = 0;
        m_Color = 0;
        m_pDad = 0;
    }
};

template <class T>
class TreeRB
{

public:
    TreeRB()
    {
        m_pRoot = nullptr;
    }

    void Add(T d)
    {

        if (!m_pRoot)
        {
            m_pRoot = new NodoRB<T>(d);
            Caso01(m_pRoot);
            return;
        }
        else
        {
            NodoRB<T> *p = m_pRoot;
            NodoRB<T> *q = p;
            while (p)
            {
                q = p;
                if (p->m_Dato == d)
                    return;
                p = p->m_pSon[p->m_Dato < d];
            }
            NodoRB<T> *&r = q->m_pSon[q->m_Dato < d];
            r = new NodoRB<T>(d);
            r->m_pDad = Padre(r);
            Caso01(r);
        }
    }

    bool Erase(T d)
    {
        return Erase_R(d, m_pRoot);
    }

    void Search(T d)
    {
        if (m_pRoot)
        {
            NodoRB<T> *q = FindNodo(d);
            std::ofstream g;
            g.open("TreeRB.dot");
            g << "digraph A{\n";
            VisualizerR(m_pRoot, g);
            g << "\tCurrent -> " << q->m_Dato << ";\n";
            g << "\tCurrent [shape=Mdiamond, style = filled, color = yellow];\n";
            g << "}";
            g.close();
        }
    }

    void Visualizer()
    {
        std::ofstream g;
        g.open("TreeRB.dot");
        g << "digraph A{\n";
        VisualizerR(m_pRoot, g);
        g << "}";
        g.close();
    }

private:
    NodoRB<T> *m_pRoot;

    NodoRB<T> *Padre(NodoRB<T> *p)
    {
        if (p == m_pRoot)
        {
            return 0;
        }
        T d = p->m_Dato;
        NodoRB<T> *q = m_pRoot;
        while (q->m_pSon[q->m_Dato < d]->m_Dato != p->m_Dato)
        {
            q = q->m_pSon[q->m_Dato < d];
        }
        return q;
    }

    NodoRB<T> *Tio(NodoRB<T> *q)
    {
        if (!q)
        {
            return 0;
        }
        NodoRB<T> *p = Abuelo(q);
        if (p->m_Dato < q->m_Dato)
        {
            return p->m_pSon[0];
        }
        else
        {
            return p->m_pSon[1];
        }
    }

    NodoRB<T> *Abuelo(NodoRB<T> *p)
    {
        if (p->m_pDad == m_pRoot)
        {
            return 0;
        }
        NodoRB<T> *q = p->m_pDad;
        NodoRB<T> *r = q->m_pDad;
        return r;
    }

    NodoRB<T> *Hermano(NodoRB<T> *p)
    {
        if (p == p->m_pDad->m_pSon[0])
        {
            return p->m_pDad->m_pSon[1];
        }
        else
        {
            return p->m_pDad->m_pSon[0];
        }
    }

    void RI(NodoRB<T> *&p)
    {
        NodoRB<T> *q = p->m_pSon[1];
        p->m_pSon[1] = q->m_pSon[0];
        if (q->m_pSon[0] != NULL)
        {
            q->m_pSon[0]->m_pDad = p;
        }
        q->m_pDad = p->m_pDad;
        if (p->m_pDad == nullptr)
        {
            m_pRoot = q;
        }
        else if (p == p->m_pDad->m_pSon[0])
        {
            p->m_pDad->m_pSon[0] = q;
        }
        else
        {
            p->m_pDad->m_pSon[1] = q;
        }
        q->m_pSon[0] = p;
        p->m_pDad = q;
    }

    void RD(NodoRB<T> *&p)
    {
        NodoRB<T> *q = p->m_pSon[0];
        p->m_pSon[0] = q->m_pSon[1];
        if (q->m_pSon[1] != NULL)
        {
            q->m_pSon[1]->m_pDad = p;
        }
        q->m_pDad = p->m_pDad;
        if (p->m_pDad == nullptr)
        {
            m_pRoot = p;
        }
        else if (p == p->m_pDad->m_pSon[1])
        {
            p->m_pDad->m_pSon[1] = q;
        }
        else
        {
            p->m_pDad->m_pSon[0] = q;
        }
        q->m_pSon[1] = p;
        p->m_pDad = q;
    }

    void Caso01(NodoRB<T> *&p)
    {
        if (p->m_pDad == 0)
        {
            p->m_Color = 1;
        }
        else
        {
            Caso02(p);
        }
    }

    void Caso02(NodoRB<T> *&p)
    {
        if (p->m_pDad->m_Color == 1)
        {
            return;
        }
        else
        {
            Caso03(p);
        }
    }

    void Caso03(NodoRB<T> *&p)
    {
        NodoRB<T> *tio = Tio(p), *a;
        if ((tio != nullptr) && (tio->m_Color == 0))
        {
            p->m_pDad->m_Color = 1;
            tio->m_Color = 1;
            a = Abuelo(p);
            a->m_Color = 0;
            Caso01(a);
        }
        else
        {
            Caso04(p);
        }
    }

    void Caso04(NodoRB<T> *&p)
    {
        NodoRB<T> *q = Abuelo(p);
        NodoRB<T> *r = p->m_pDad;
        if ((p == p->m_pDad->m_pSon[1]) && (p->m_pDad == q->m_pSon[0]))
        {
            RI(r);
            p = p->m_pSon[0];
        }
        else if ((p == p->m_pDad->m_pSon[0]) && (p->m_pDad == q->m_pSon[1]))
        {
            RD(r);
            p = p->m_pSon[1];
        }
        Caso05(p);
    }

    void Caso05(NodoRB<T> *&p)
    {
        NodoRB<T> *q = Abuelo(p);
        p->m_pDad->m_Color = 1;
        q->m_Color = 0;
        if ((p == p->m_pDad->m_pSon[0]) && (p->m_pDad == q->m_pSon[0]))
        {
            RD(q);
            if (q == m_pRoot)
            {
                m_pRoot = p->m_pDad;
            }
        }
        else if ((p == p->m_pDad->m_pSon[1]) && (p->m_pDad == q->m_pSon[1]))
        {
            RI(q);
            if (q == m_pRoot)
            {
                m_pRoot = p->m_pDad;
            }
        }
    }

    NodoRB<T> *Min(NodoRB<T> *&p)
    {
        if (!p->m_pSon[0])
        {
            return p;
        }
        return Min(p->m_pSon[0]);
    }

    bool Erase_R(T d, NodoRB<T> *&p)
    {
        if (p->m_Dato > d)
        {
            if (!p->m_pSon[0])
            {
                return false;
            }
            Erase_R(d, p->m_pSon[0]);
        }
        else if (p->m_Dato < d)
        {
            if (!p->m_pSon[1])
            {
                return false;
            }
            Erase_R(d, p->m_pSon[1]);
        }
        else if (p->m_Dato == d)
        {
            if (p->m_pSon[1] == nullptr)
            {
                Delete(p);
                return true;
            }
            NodoRB<T> *Small = Min(p->m_pSon[1]);
            std::swap(p->m_Dato, Small->m_Dato);
            Delete(Small);
            return true;
        }
        else
        {
            return false;
        }
    }

    void Delete(NodoRB<T> *&p)
    {
        NodoRB<T> *Hijo;
        if (!p->m_pSon[0])
        {
            Hijo = p->m_pSon[0];
        }
        else
        {
            Hijo = p->m_pSon[1];
        }
        if (Hijo != NULL)
        {
            if (!p->m_pDad && !p->m_pSon[0] && !p->m_pSon[1])
            {
                p = NULL;
                m_pRoot = p;
                return;
            }
            if (!p->m_pDad)
            {
                delete p;
                Hijo->m_pDad = NULL;
                m_pRoot = Hijo;
                m_pRoot->m_Color = 1;
                return;
            }
            if (p->m_pDad->m_pSon[0] == p)
            {
                p->m_pDad->m_pSon[0] = Hijo;
            }
            else
            {
                p->m_pDad->m_pSon[1] = Hijo;
            }
            Hijo->m_pDad = p->m_pDad;
            if (p->m_Color == 1)
            {
                if (Hijo->m_Color == 0)
                {
                    Hijo->m_Color = 1;
                }
                else
                {
                    DCaso01(Hijo);
                }
            }
        }
        p->m_pDad->m_pSon[p->m_pDad->m_Dato < p->m_Dato] = p->m_pSon[1];
        delete p;
    }

    void DCaso01(NodoRB<T> *&p)
    {
        if (p->m_pDad != NULL)
        {
            DCaso02(p);
        }
    }

    void DCaso02(NodoRB<T> *&p)
    {
        NodoRB<T> *q = Hermano(p);
        if (q->m_Color == 0)
        {
            p->m_pDad->m_Color = 0;
            q->m_Color = 1;
            if (p == p->m_pDad->m_pSon[0])
            {
                NodoRB<T> *r = p->m_pDad;
                RI(r);
            }
            else
            {
                NodoRB<T> *r = p->m_pDad;
                RD(r);
            }
        }
        DCaso03(p);
    }

    void DCaso03(NodoRB<T> *&p)
    {
        NodoRB<T> *q = Hermano(p);
        if ((p->m_pDad->m_Color == 1) && (q->m_Color == 1) && (q->m_pSon[0]->m_Color == 1) && (q->m_pSon[1]->m_Color == 1))
        {
            q->m_Color = 0;
            NodoRB<T> *r = p->m_pDad;
            DCaso01(r);
        }
        else
        {
            DCaso04(p);
        }
    }

    void DCaso04(NodoRB<T> *&p)
    {
        NodoRB<T> *q = Hermano(p);
        if ((p->m_pDad->m_Color == 0) && (q->m_Color == 1) && (q->m_pSon[0]->m_Color == 1) && (q->m_pSon[1]->m_Color == 1))
        {
            q->m_Color = 0;
            p->m_pDad->m_Color = 1;
        }
        else
        {
            DCaso05(p);
        }
    }

    void DCaso05(NodoRB<T> *&p)
    {
        NodoRB<T> *q = Hermano(p);
        if ((p == p->m_pDad->m_pSon[0]) && (q->m_Color == 1) && (q->m_pSon[0]->m_Color == 0) && (q->m_pSon[1]->m_Color == 1))
        {
            q->m_Color = 1;
            q->m_pSon[0]->m_Color = 1;
            RD(q);
        }
        else if ((p == p->m_pDad->m_pSon[1]) && (q->m_Color == 1) && (q->m_pSon[1]->m_Color == 0) && (q->m_pSon[0]->m_Color == 1))
        {
            q->m_Color = 1;
            q->m_pSon[1]->m_Color = 1;
            RI(q);
        }
        DCaso06(p);
    }

    void DCaso06(NodoRB<T> *&p)
    {
        NodoRB<T> *q = Hermano(p);
        q->m_Color = p->m_pDad->m_Color;
        p->m_pDad->m_Color = 1;
        if (p == p->m_pDad->m_pSon[0])
        {
            q->m_pSon[1]->m_Color = 1;
            RI(q);
        }
        else
        {
            q->m_pSon[0]->m_Color = 1;
            RD(q);
        }
    }

    void VisualizerR(NodoRB<T> *p, std::ofstream &g)
    {
        if (p != NULL)
        {
            if (p == m_pRoot)
            {
                g << "\t" << p->m_Dato << "[style = filled, color = black, fontcolor = white];\n";
            }
            if (p->m_pSon[0] != NULL)
            {
                g << "\t" << p->m_Dato << " -> " << p->m_pSon[0]->m_Dato << ";\n";
                if (p->m_pSon[0]->m_Color == false)
                {
                    g << "\t" << p->m_pSon[0]->m_Dato << "[style = filled, color = red, fontcolor = white];\n";
                }
                else
                {
                    g << "\t" << p->m_pSon[0]->m_Dato << "[style = filled, color = black, fontcolor = white];\n";
                }
            }
            if (p->m_pSon[1] != NULL)
            {
                g << "\t" << p->m_Dato << " -> " << p->m_pSon[1]->m_Dato << ";\n";
                if (p->m_pSon[1]->m_Color == false)
                {
                    g << "\t" << p->m_pSon[1]->m_Dato << "[style = filled, color = red, fontcolor = white];\n";
                }
                else
                {
                    g << "\t" << p->m_pSon[1]->m_Dato << "[style = filled, color = black, fontcolor = white];\n";
                }
            }
            VisualizerR(p->m_pSon[0], g);
            VisualizerR(p->m_pSon[1], g);
        }
    }
};
