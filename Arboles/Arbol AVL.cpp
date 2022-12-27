#include <iostream>
#include <fstream>
#include <algorithm>
template <class T>
class NodoAVL
{

public:
    T m_Dato;
    NodoAVL<T> *m_pSon[2];
    int m_Height;
    int m_Factor;

public:
    NodoAVL(T d)
    {
        m_Dato = d;
        m_pSon[0] = m_pSon[1] = 0;
        m_Height = 0;
        m_Factor = 0;
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

    void Insert(T d)
    {
        InsertR(d, m_pRoot);
    }

    void Erase(T d)
    {
        EraseR(d, m_pRoot, 0);
    }

    void Search(T d)
    {
        if (m_pRoot)
        {
            NodoAVL<T> *q = FindNodo(d);
            std::ofstream g;
            g.open("TreeAVL.dot");
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
        if (m_pRoot)
        {
            std::ofstream g;
            g.open("TreeAVL.dot");
            g << "digraph A{\n";
            g << "\tRoot -> " << m_pRoot->m_Dato << ";\n";
            g << "\tRoot [shape=Mdiamond, style = filled, color = gray];\n";
            g << "}";
        }
        else
        {
            std::ofstream g;
            g.open("TreeAVL.dot");
            g << "digraph A{\n";
            g << "\tRoot -> Null;\n";
            g << "\tRoot [shape=Mdiamond, style = filled, color = gray];\n";
            g << "\tNull [shape=Mdiamond, style = filled, color = gray];\n";
            VisualizerR(m_pRoot, g);
            g << "}";
        }
    }

private:
    NodoAVL<T> *m_pRoot;

    void RDD(NodoAVL<T> *&p)
    {
        NodoAVL<T> *q = p->m_pSon[1];
        p->m_pSon[1] = q->m_pSon[0];
        q->m_pSon[0] = p;
        if (!p->m_pSon[1])
        {
            p->m_Factor = 0;
            q->m_Factor = 0;
        }
        else
        {
            if (p->m_pSon[0])
            {
                p->m_Factor = -p->m_pSon[1]->m_Factor + p->m_pSon[0]->m_Factor;
            }
            else
            {
                p->m_Factor = p->m_pSon[1]->m_Factor + 1;
            }
            p->m_Height = p->m_pSon[1]->m_Height + 1;
            q->m_Factor = -p->m_Height + q->m_pSon[1]->m_Height;
            q->m_Height = 1 + std::max(p->m_Height, q->m_pSon[1]->m_Height);
        }
        p = q;
        if (!q->m_pSon[0]->m_pSon[0] && !q->m_pSon[0]->m_pSon[1])
        {
            q->m_pSon[0]->m_Height = 0;
            q->m_Height = q->m_pSon[0]->m_Height + 1;
        }
        else
        {
            if (q->m_pSon[0]->m_pSon[0] && q->m_pSon[0]->m_pSon[1])
            {
                q->m_pSon[0]->m_Height = 1 + std::max(q->m_pSon[0]->m_pSon[0]->m_Height, q->m_pSon[0]->m_pSon[1]->m_Height);
            }
        }
    }

    void RII(NodoAVL<T> *&p)
    {
        NodoAVL<T> *q = p->m_pSon[0];
        p->m_pSon[0] = q->m_pSon[1];
        q->m_pSon[1] = p;
        if (!p->m_pSon[0])
        {
            p->m_Factor = 0;
            q->m_Factor = 0;
        }
        else
        {
            if (p->m_pSon[1])
            {
                p->m_Factor = -p->m_pSon[1]->m_Factor + p->m_pSon[0]->m_Factor;
            }
            else
            {
                p->m_Factor = p->m_pSon[0]->m_Factor + 1;
            }
            p->m_Factor = p->m_pSon[0]->m_Height + 1;
            p->m_Height = p->m_pSon[0]->m_Height + 1;
            q->m_Factor = -p->m_Height + q->m_pSon[0]->m_Height;
            q->m_Height = 1 + std::max(p->m_Height, q->m_pSon[0]->m_Height);
        }
        p = q;
        if (!q->m_pSon[1]->m_pSon[0] && !q->m_pSon[1]->m_pSon[1])
        {
            q->m_pSon[1]->m_Height = 0;
            q->m_Height = q->m_pSon[1]->m_Height + 1;
        }
        else
        {
            if (q->m_pSon[1]->m_pSon[0] && q->m_pSon[1]->m_pSon[1])
            {
                q->m_pSon[1]->m_Height = 1 + std::max(q->m_pSon[1]->m_pSon[0]->m_Height, q->m_pSon[1]->m_pSon[1]->m_Height);
            }
        }
    }

    void RDI(NodoAVL<T> *&p)
    {
        NodoAVL<T> *q = p->m_pSon[1];
        NodoAVL<T> *r = q->m_pSon[0];
        p->m_pSon[1] = r->m_pSon[0];
        q->m_pSon[0] = r->m_pSon[1];
        r->m_pSon[0] = p;
        r->m_pSon[1] = q;
        switch (r->m_Factor)
        {
        case 0:
            r->m_Factor = p->m_Factor = q->m_Factor = 0;
            r->m_Height = 1;
            p->m_Height = q->m_Height = 0;
            break;
        case 1:
            r->m_Factor = 0;
            r->m_Height = 2;
            p->m_Factor = -1;
            p->m_Height = 1;
            q->m_Factor = 0;
            q->m_Height = 1;
            break;
        case -1:
            r->m_Factor = 0;
            r->m_Height = 2;
            p->m_Factor = 0;
            p->m_Height = 1;
            q->m_Factor = 1;
            q->m_Height = 1;
            break;
        }
        p = r;
    }

    void RID(NodoAVL<T> *&p)
    {
        NodoAVL<T> *q = p->m_pSon[0];
        NodoAVL<T> *r = q->m_pSon[1];
        p->m_pSon[0] = r->m_pSon[1];
        q->m_pSon[1] = r->m_pSon[0];
        r->m_pSon[1] = p;
        r->m_pSon[0] = q;
        switch (r->m_Factor)
        {
        case 0:
            r->m_Factor = p->m_Factor = q->m_Factor = 0;
            r->m_Height = 1;
            p->m_Height = q->m_Height = 0;
            break;
        case -1:
            p->m_Factor = 1;
            p->m_Height = 1;
            q->m_Factor = 0;
            q->m_Height = 1;
            r->m_Factor = 0;
            r->m_Height = 2;
            break;
        case 1:
            p->m_Factor = 0;
            p->m_Height = 1;
            q->m_Factor = -1;
            q->m_Height = 1;
            r->m_Factor = 0;
            r->m_Height = 2;
            break;
        }
        p = r;
    }

    void InsertR(T d, NodoAVL<T> *&p)
    {
        if (!p)
        {
            p = new NodoAVL<T>(d);
            return;
        }
        if (p->m_Dato == d)
        {
            return;
        }
        InsertR(d, p->m_pSon[p->m_Dato < d]);
        if (p != m_pRoot)
        {
            if (p->m_pSon[0] && p->m_pSon[1])
            {
                if (p->m_pSon[p->m_Dato < d]->m_Factor != 0)
                {
                    p->m_Height = 1 + std::max(p->m_pSon[0]->m_Height, p->m_pSon[1]->m_Height);
                }
            }
            if ((p->m_pSon[0] && !p->m_pSon[1]) || (p->m_pSon[1] && !p->m_pSon[0]))
            {
                p->m_Height += 1;
            }
        }
        if (p->m_Dato < d)
        {
            p->m_Factor += 1;
        }
        else
        {
            p->m_Factor -= 1;
        }
        if (p->m_pSon[0] && p->m_pSon[1])
        {
            p->m_Factor = -p->m_pSon[0]->m_Height + p->m_pSon[1]->m_Height;
        }
        switch (p->m_Factor)
        {
        case 2:
            if (p->m_pSon[1]->m_Factor == 1)
            {
                RDD(p);
                break;
            }
            else
            {
                RDI(p);
                break;
            }
        case -2:
            if (p->m_pSon[0]->m_Factor == -1)
            {
                RII(p);
                break;
            }
            else
            {
                RID(p);
                break;
            }
        }
    }

    T Max(NodoAVL<T> *p)
    {
        NodoAVL<T> *q = p->m_pSon[0];
        NodoAVL<T> *r;
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

    void EraseR(T d, NodoAVL<T> *&p, NodoAVL<T> *Padre)
    {
        if (!p)
        {
            return;
        }
        if (p->m_Dato != d && (p->m_pSon[1] || p->m_pSon[0]))
        {
            EraseR(d, p->m_pSon[p->m_Dato < d], p);
        }
        if (p->m_Dato == d)
        {
            if (!p->m_pSon[0] && !p->m_pSon[1])
            {
                if (Padre)
                {
                    Padre->m_pSon[Padre->m_Dato < p->m_Dato] = p->m_pSon[1];
                }
                if (p->m_Dato == m_pRoot->m_Dato)
                {
                    m_pRoot = nullptr;
                }
                else
                {
                    delete p;
                }
            }
            else if (!p->m_pSon[0])
            {
                T aux = p->m_pSon[1]->m_Dato;
                Erase(aux);
                p->m_Dato = aux;
            }
            else if (!p->m_pSon[1])
            {
                T aux = p->m_pSon[0]->m_Dato;
                Erase(aux);
                p->m_Dato = aux;
            }
            else if (p->m_pSon[1] && p->m_pSon[0])
            {
                T Mayor = Max(p);
                Erase(Mayor);
                if (p->m_Dato == d)
                {
                    p->m_Dato = Mayor;
                }
                else if (p->m_pSon[0]->m_Dato == d)
                {
                    p->m_pSon[0]->m_Dato = Mayor;
                }
                else if (p->m_pSon[1]->m_Dato == d)
                {
                    p->m_pSon[1]->m_Dato = Mayor;
                }
            }
            return;
        }
        if (p->m_pSon[0] && p->m_pSon[1])
        {
            p->m_Height = 1 + std::max(p->m_pSon[0]->m_Height, p->m_pSon[1]->m_Height);
            p->m_Factor = -p->m_pSon[0]->m_Height + p->m_pSon[1]->m_Height;
        }
        if (!p->m_pSon[0] && !p->m_pSon[1])
        {
            p->m_Height -= 1;
            if (p->m_Factor == 1)
            {
                p->m_Factor -= 1;
            }
            else if (p->m_Factor == -1)
            {
                p->m_Factor += 1;
            }
        }
        if (p->m_pSon[1] && !p->m_pSon[0])
        {
            p->m_Factor += 1;
        }
        if (p->m_pSon[0] && !p->m_pSon[1])
        {
            p->m_Factor -= 1;
        }
        switch (p->m_Factor)
        {
        case 2:
            if (!p->m_pSon[0])
            {
                RDD(p);
                break;
            }
            else
            {
                RDI(p);
                break;
            }
        case -2:
            if (!p->m_pSon[1])
            {
                RII(p);
                break;
            }
            else
            {
                RID(p);
                break;
            }
        }
    }

    NodoAVL<T> *FindNodo(T d)
    {
        NodoAVL<T> *p = m_pRoot;
        while (p)
        {
            if (p->m_Dato == d)
            {
                return p;
            }
            p = p->m_pSon[p->m_Dato < d];
        }
    }

    void VisualizerR(NodoAVL<T> *p, std::ofstream &g)
    {
        if (p != NULL)
        {
            if (p == m_pRoot)
            {
                g << "\t" << p->m_Dato << " [style = filled, color = gray, label = \"" << p->m_Dato << "|" << p->m_Factor << "\"];\n";
            }
            if (p->m_pSon[0] != NULL)
            {
                g << "\t" << p->m_Dato << " -> " << p->m_pSon[0]->m_Dato << ";\n";
                g << "\t" << p->m_pSon[0]->m_Dato << " [style = filled, color = gray, label = \"" << p->m_pSon[0]->m_Dato << "|" << p->m_pSon[0]->m_Factor << "\"];\n";
            }
            if (p->m_pSon[1] != NULL)
            {
                g << "\t" << p->m_Dato << " -> " << p->m_pSon[1]->m_Dato << ";\n";
                g << "\t" << p->m_pSon[1]->m_Dato << " [style = filled, color = gray, label = \"" << p->m_pSon[1]->m_Dato << "|" << p->m_pSon[1]->m_Factor << "\"];\n";
            }

            VisualizerR(p->m_pSon[0], g);
            VisualizerR(p->m_pSon[1], g);
        }
    }
};
