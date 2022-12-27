#include <iostream>
#include <fstream>

template <class T>
class NodoAB
{
public:
    T m_Dato;
    NodoAB<T> *m_pSon[2];
    NodoAB(T d)
    {
        m_Dato = d;
        m_pSon[0] = m_pSon[1] = 0;
    }
};
template <class T>
class Tree
{

public:
    Tree()
    {
        m_pRoot = nullptr;
    }
    void Add(T d)
    {
        if (!m_pRoot)
        {
            m_pRoot = new NodoAB<T>(d);
            return;
        }
        else
        {
            NodoAB<T> *p = m_pRoot;
            NodoAB<T> *q = p;
            while (p)
            {
                q = p;
                if (p->m_Dato == d)
                    return;
                p = p->m_pSon[p->m_Dato < d];
            }
            NodoAB<T> *&r = q->m_pSon[q->m_Dato < d];
            r = new NodoAB<T>(d);
        }
    }

    void Erase(T d)
    {
        if (m_pRoot)
        {
            NodoAB<T> *p = m_pRoot;
            NodoAB<T> *pErase;
            while (p)
            {
                if (p->m_Dato == d)
                {
                    pErase = p;
                }
                p = p->m_pSon[p->m_Dato < d];
            }
            if (pErase != m_pRoot)
            {
                p = m_pRoot;
                if (!pErase->m_pSon[1] && !pErase->m_pSon[0])
                {
                    while (p->m_pSon[p->m_Dato < d]->m_Dato != d)
                    {
                        p = p->m_pSon[p->m_Dato < d];
                    }
                    p->m_pSon[p->m_Dato < d] = pErase->m_pSon[0];
                    delete pErase;
                }
                else if (!pErase->m_pSon[1])
                {
                    T aux = pErase->m_pSon[0]->m_Dato;
                    Erase(aux);
                    pErase->m_Dato = aux;
                }
                else if (!pErase->m_pSon[0])
                {
                    T aux = pErase->m_pSon[1]->m_Dato;
                    Erase(aux);
                    pErase->m_Dato = aux;
                }
                else if (pErase->m_pSon[1] && pErase->m_pSon[0])
                {
                    T Max = Mayor(pErase);
                    Erase(Max);
                    pErase->m_Dato = Max;
                }
            }
            else
            {
                m_pRoot = nullptr;
            }
        }
    }

    void Search(T d)
    {
        if (m_pRoot)
        {
            NodoAB<T> *p = m_pRoot;
            NodoAB<T> *q;
            while (p)
            {
                if (p->m_Dato == d)
                {
                    q = p;
                }
                p = p->m_pSon[p->m_Dato < d];
            }
            std::ofstream g;
            g.open("TreeBinary.dot");
            g << "digraph A{\n";
            g << "\tRoot -> " << m_pRoot->m_Dato << ";\n";
            g << "\tRoot [shape=Mdiamond, style = filled, color = gray];\n";
            VisualizerR(m_pRoot, g);
            g << "\t" << q->m_Dato << "[style = filled, color = yellow, fontcolor = black];\n";
            g << "\tCurrent -> " << q->m_Dato << ";\n";
            g << "\tCurrent [shape=Mdiamond, style = filled, color = yellow];\n";
            g << "}" << std::endl;
            g.close();
        }
    }

    void Visualizer()
    {
        if (m_pRoot)
        {
            std::ofstream g;
            g.open("TreeBinary.dot");
            g << "digraph A{\n";
            g << "\tRoot -> " << m_pRoot->m_Dato << ";\n";
            g << "\tRoot [shape=Mdiamond, style = filled, color = gray];\n";
            VisualizerR(m_pRoot, g);
            g << "}";
            g.close();
        }
        else
        {
            std::ofstream g;
            g.open("TreeBinary.dot");
            g << "digraph A{\n";
            g << "\tRoot -> Null;\n";
            g << "\tRoot [shape=Mdiamond, style = filled, color = gray];\n";
            g << "\tNull [shape=Mdiamond, style = filled, color = gray];\n";
            g << "}";
        }
    }

private:
    NodoAB<T> *m_pRoot;

    T Mayor(NodoAB<T> *p)
    {
        NodoAB<T> *q = p->m_pSon[0];
        NodoAB<T> *r;
        if (q->m_pSon[1])
        {
            while (q->m_pSon[1])
            {
                r = q->m_pSon[1];
                q = q->m_pSon[1];
            }
            return r->m_Dato;
        }
        else
        {
            return q->m_Dato;
        }
    }

    void VisualizerR(NodoAB<T> *p, std::ofstream &g)
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
                g << "\t" << p->m_pSon[0]->m_Dato << "[style = filled, color = black, fontcolor = white];\n";
            }
            if (p->m_pSon[1] != NULL)
            {
                g << "\t" << p->m_Dato << " -> " << p->m_pSon[1]->m_Dato << ";\n";
                g << "\t" << p->m_pSon[1]->m_Dato << "[style = filled, color = black, fontcolor = white];\n";
            }
            VisualizerR(p->m_pSon[0], g);
            VisualizerR(p->m_pSon[1], g);
        }
    }
};
