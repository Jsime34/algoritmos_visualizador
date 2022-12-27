#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#define INF 99999

template <class V, class A>
class Edge_Prim;

template <class V, class A>
class Vertex_Prim
{
public:
    V m_Dato;
    bool m_Visit;
    std::list<Edge_Prim<V, A>> m_list_Edge;

    Vertex_Prim(V vertice)
    {
        m_Dato = vertice;
        m_Visit = false;
    }

    bool operator==(const Vertex_Prim<V, A> &Ve)
    {
        return m_Dato == Ve.m_Dato;
    }
};

template <class V, class A>
class Edge_Prim
{
public:
    A m_Dato;
    Vertex_Prim<V, A> *m_pVertex_Prim;

    Edge_Prim(A a, Vertex_Prim<V, A> *q = 0)
    {
        m_Dato = a;
        m_pVertex_Prim = q;
    }

    bool operator==(const Edge_Prim<V, A> &Ar)
    {
        return m_Dato == Ar.m_Dato;
    }
};

template <class V, class A>
class Graph_Prim
{
    typedef typename std::list<Vertex_Prim<V, A>>::iterator Iterator_Vertex_Prim;
    typedef typename std::list<Edge_Prim<V, A>>::iterator Iterator_Edge;

public:
    Graph_Prim(){};

    void Insert(V Vertice)
    {
        m_Graph.push_back(Vertex_Prim<V, A>(Vertice));
    };

    void Insert_Edge(V v1, V v2, A a)
    {
        Iterator_Vertex_Prim p = find_Vertex_Prim(v1);
        Iterator_Vertex_Prim q = find_Vertex_Prim(v2);
        if (p != m_Graph.end() && q != m_Graph.end())
        {
            Vertex_Prim<V, A> *pDestino1 = &(*q);
            Vertex_Prim<V, A> *pDestino2 = &(*p);
            p->m_list_Edge.push_back(Edge_Prim<V, A>(a, pDestino1));
            q->m_list_Edge.push_back(Edge_Prim<V, A>(a, pDestino2));
        }
    }

    void Prim()
    {
        Reset_Graph();
        Iterator_Vertex_Prim v = m_Graph.begin();
        std::list<Vertex_Prim<V, A>> P;
        std::list<Edge_Prim<V, A>> Q;
        v->m_Visit = true;
        P.push_back(*v);
        while (P.size() < m_Graph.size())
        {
            Edge_Prim<V, A> min = Min_Arista(P);
            if (!Ciclo(P, min))
            {
                Iterator_Vertex_Prim q = find_Vertex_Prim(min.m_pVertex_Prim->m_Dato);
                P.push_back(*q);
                Q.push_back(min);
                min.m_pVertex_Prim->m_Visit = true;
            }
        }

        Iterator_Vertex_Prim it = m_Graph.begin();
        std::list<V> G;
        typedef typename std::list<V>::iterator Iterator;
        std::ofstream g;
        g.open("Prim.dot");
        g << "graph A{\n";
        g << "\trankdir = \"LR\";" << std::endl;
        for (; it != m_Graph.end(); it++)
        {
            Iterator_Edge it_e = it->m_list_Edge.begin();
            for (; it_e != it->m_list_Edge.end(); ++it_e)
            {
                Iterator_Edge it_q = Q.begin();
                Iterator l = std::find(G.begin(), G.end(), it_e->m_pVertex_Prim->m_Dato);
                if (it_e->m_Dato == it_q->m_Dato)
                {
                    g << "\t" << it->m_Dato << " -- " << it_e->m_pVertex_Prim->m_Dato << " [label = " << it_e->m_Dato << ", color = red];\n";
                    Q.pop_front();
                }
                else if (l == G.end())
                {
                    g << "\t" << it->m_Dato << " -- " << it_e->m_pVertex_Prim->m_Dato << " [label = " << it_e->m_Dato << "];\n";
                }
            }
            G.push_back(it->m_Dato);
        }
        g << "}" << std::endl;
        g.close();
    }

    void Visualizer()
    {
        Iterator_Vertex_Prim it = m_Graph.begin();
        std::list<V> G;
        typedef typename std::list<V>::iterator Iterator;
        std::ofstream g;
        g.open("Prim.dot");
        g << "graph A{\n";
        g << "\trankdir = \"LR\";" << std::endl;
        for (; it != m_Graph.end(); it++)
        {
            if (!it->m_list_Edge.empty())
            {
                Iterator_Edge it_e = it->m_list_Edge.begin();
                for (; it_e != it->m_list_Edge.end(); ++it_e)
                {
                    Iterator l = std::find(G.begin(), G.end(), it_e->m_pVertex_Prim->m_Dato);
                    if (l == G.end())
                    {
                        g << "\t" << it->m_Dato << " -- " << it_e->m_pVertex_Prim->m_Dato << " [label = " << it_e->m_Dato << "];\n";
                    }
                }
            }
            else
            {
                g << "\t" << it->m_Dato << ";\n";
            }
            G.push_back(it->m_Dato);
        }
        g << "}" << std::endl;
        g.close();
    }

private:
    std::list<Vertex_Prim<V, A>> m_Graph;

    void Reset_Graph()
    {
        Iterator_Vertex_Prim it = m_Graph.begin();
        for (; it != m_Graph.end(); it++)
        {
            it->m_Visit = false;
        }
    }

    Iterator_Vertex_Prim find_Vertex_Prim(V v)
    {
        return std::find(m_Graph.begin(), m_Graph.end(), Vertex_Prim<V, A>(v));
    }

    bool find_edge(V v, A a)
    {
        Iterator_Vertex_Prim p = find_Vertex_Prim(v);
        Iterator_Edge q = std::find(p->m_list_Edge.begin(), p->m_list_Edge.end(), Edge_Prim<V, A>(a));
        if (q != p->m_list_Edge.end())
        {
            return true;
        }
    }

    Edge_Prim<V, A> Min_Arista(std::list<Vertex_Prim<V, A>> &P)
    {
        A Arista = INF;
        Vertex_Prim<V, A> *pDestino;
        Iterator_Vertex_Prim it = P.begin();
        for (; it != P.end(); it++)
        {
            Iterator_Edge it_e = it->m_list_Edge.begin();
            for (; it_e != it->m_list_Edge.end(); ++it_e)
            {
                if (it_e->m_Dato < Arista && it_e->m_pVertex_Prim->m_Visit == false)
                {
                    Arista = it_e->m_Dato;
                    pDestino = &(*find_Vertex_Prim(it_e->m_pVertex_Prim->m_Dato));
                }
            }
        }
        return Edge_Prim<V, A>(Arista, pDestino);
    }

    bool Ciclo(std::list<Vertex_Prim<V, A>> &P, Edge_Prim<V, A> q)
    {
        Iterator_Vertex_Prim it = P.begin();
        for (; it != P.end(); it++)
        {
            if (q.m_pVertex_Prim->m_Dato == it->m_Dato)
            {
                return true;
            }
        }
        return false;
    }
};
