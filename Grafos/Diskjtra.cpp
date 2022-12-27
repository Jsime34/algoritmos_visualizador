#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#define INF 99999

template <class V, class A>
class Edge_Diskjtra;

template <class V, class A>
class Vertex_Diskjtra
{
public:
    V m_Dato;
    V m_Prev;
    bool m_Visit;
    A m_Distancia;
    std::list<Edge_Diskjtra<V, A>> m_list_Edge;

    Vertex_Diskjtra(V vertice, V next = "")
    {
        m_Dato = vertice;
        m_Prev = next;
        m_Visit = false;
        m_Distancia = 0;
    }

    void Distance(A dist, V prev)
    {
        m_Distancia = dist;
        m_Prev = prev;
    }

    bool operator==(const Vertex_Diskjtra<V, A> &Ve)
    {
        return m_Dato == Ve.m_Dato;
    }

    bool operator<(const Vertex_Diskjtra<V, A> &b) const
    {
        return m_Distancia > b.m_Distancia;
    }
};

template <class V, class A>
class Edge_Diskjtra
{
public:
    A m_Dato;
    bool m_Visit;
    Vertex_Diskjtra<V, A> *m_pVertex_Diskjtra;

    Edge_Diskjtra(A a, Vertex_Diskjtra<V, A> *q = 0)
    {
        m_Dato = a;
        m_pVertex_Diskjtra = q;
    }

    bool operator==(const Edge_Diskjtra<V, A> &Ar)
    {
        return m_Dato == Ar.m_Dato;
    }
};

template <class V, class A>
class Graph_Diskjtra
{
    typedef typename std::list<Vertex_Diskjtra<V, A>>::iterator Iterator_Vertex_Diskjtra;
    typedef typename std::list<Edge_Diskjtra<V, A>>::iterator Iterator_Edge_Diskjtra;

public:
    Graph_Diskjtra(){};

    void Insert(V Vertice)
    {
        m_Graph.push_back(Vertex_Diskjtra<V, A>(Vertice));
    };

    void Insert_Edge(V v1, V v2, A a)
    {
        Iterator_Vertex_Diskjtra p = find_Vertex_Diskjtra(v1);
        Iterator_Vertex_Diskjtra q = find_Vertex_Diskjtra(v2);
        if (p != m_Graph.end() && q != m_Graph.end())
        {
            Vertex_Diskjtra<V, A> *pDestino = &(*q);
            p->m_list_Edge.push_back(Edge_Diskjtra<V, A>(a, pDestino));
        }
    }
    void Diskjtra(V v1, V v2)
    {
        std::priority_queue<Vertex_Diskjtra<V, A>> Pq;
        std::vector<A> Dist(m_Graph.size(), INF);
        std::vector<bool> Mark(m_Graph.size(), false);

        int n1 = Pos(v1);

        Dist[n1] = 0;
        Iterator_Vertex_Diskjtra p = find_Vertex_Diskjtra(v1);
        Pq.push(*p);
        while (!Pq.empty())
        {
            Vertex_Diskjtra<V, A> st = Pq.top();
            Pq.pop();
            int l = Pos(st.m_Dato);
            Mark[l] = true;
            if (st.m_Dato == v2)
            {
                break;
            }
            Iterator_Edge_Diskjtra it_e = st.m_list_Edge.begin();
            for (; it_e != st.m_list_Edge.end(); ++it_e)
            {
                int k = Pos(it_e->m_pVertex_Diskjtra->m_Dato);
                if (!Mark[k] && ((Dist[l] + it_e->m_Dato) < Dist[k]))
                {
                    Dist[k] = st.m_Distancia + it_e->m_Dato;
                    it_e->m_pVertex_Diskjtra->Distance(st.m_Distancia + it_e->m_Dato, st.m_Dato);
                    Iterator_Vertex_Diskjtra it_p = find_Vertex_Diskjtra(it_e->m_pVertex_Diskjtra->m_Dato);
                    Pq.push(*it_p);
                }
            }
        }

        int k = Pos(v2);
        if (Dist[k] != INF)
        {
            std::stack<V> Ca;
            Iterator_Vertex_Diskjtra q = find_Vertex_Diskjtra(v2);
            Ca.push(q->m_Dato);
            while (Ca.top() != v1)
            {
                Ca.push(q->m_Prev);
                q = find_Vertex_Diskjtra(q->m_Prev);
            }
            V f = Ca.top();
            Ca.pop();
            Iterator_Vertex_Diskjtra it = m_Graph.begin();
            std::ofstream g;
            g.open("Diskjtra.dot");
            g << "digraph A{\n";
            g << "\trankdir = \"LR\";" << std::endl;
            for (; it != m_Graph.end(); it++)
            {
                if (!it->m_list_Edge.empty())
                {
                    Iterator_Edge_Diskjtra it_e = it->m_list_Edge.begin();
                    for (; it_e != it->m_list_Edge.end(); ++it_e)
                    {
                        if (it->m_Dato == f)
                        {
                            if (!Ca.empty() && it_e->m_pVertex_Diskjtra->m_Dato == Ca.top())
                            {
                                g << "\t" << it->m_Dato << " -> " << it_e->m_pVertex_Diskjtra->m_Dato << " [label = " << it_e->m_Dato << ",color = red];\n";
                                f = Ca.top();
                                Ca.pop();
                            }
                            else
                            {
                                g << "\t" << it->m_Dato << " -> " << it_e->m_pVertex_Diskjtra->m_Dato << " [label = " << it_e->m_Dato << "];\n";
                            }
                        }
                        else
                        {
                            g << "\t" << it->m_Dato << " -> " << it_e->m_pVertex_Diskjtra->m_Dato << " [label = " << it_e->m_Dato << "];\n";
                        }
                    }
                }
                else
                {
                    g << "\t" << it->m_Dato << ";\n";
                }
            }
            g << "}" << std::endl;
            g.close();
        }
        else
        {
            Visualizer();
        }
    }

    void Visualizer()
    {
        Iterator_Vertex_Diskjtra it = m_Graph.begin();
        std::ofstream g;
        g.open("Diskjtra.dot");
        g << "digraph A{\n";
        g << "\trankdir = \"LR\";" << std::endl;
        for (; it != m_Graph.end(); it++)
        {
            if (!it->m_list_Edge.empty())
            {
                Iterator_Edge_Diskjtra it_e = it->m_list_Edge.begin();
                for (; it_e != it->m_list_Edge.end(); ++it_e)
                {
                    g << "\t" << it->m_Dato << " -> " << it_e->m_pVertex_Diskjtra->m_Dato << " [label = " << it_e->m_Dato << "];\n";
                }
            }
            else
            {
                g << "\t" << it->m_Dato << ";\n";
            }
        }
        g << "}" << std::endl;
        g.close();
    }

private:
    std::list<Vertex_Diskjtra<V, A>> m_Graph;

    void Reset_Graph()
    {
        Iterator_Vertex_Diskjtra it = m_Graph.begin();
        for (; it != m_Graph.end(); it++)
        {
            it->m_Visit = false;
            it->m_Distancia = 0;
        }
    }

    Iterator_Vertex_Diskjtra find_Vertex_Diskjtra(V v)
    {
        return std::find(m_Graph.begin(), m_Graph.end(), Vertex_Diskjtra<V, A>(v));
    }

    bool find_edge(V v, A a)
    {
        Iterator_Vertex_Diskjtra p = find_Vertex_Diskjtra(v);
        Iterator_Edge_Diskjtra q = std::find(p->m_list_Edge.begin(), p->m_list_Edge.end(), Edge_Diskjtra<V, A>(a));
        if (q != p->m_list_Edge.end())
        {
            return true;
        }
    }

    int Pos(V v1)
    {
        Iterator_Vertex_Diskjtra it = m_Graph.begin();
        int n = 0, n1;
        for (; it != m_Graph.end(); ++it)
        {
            if (it->m_Dato == v1)
            {
                n1 = n;
            }
            n++;
        }
        return n1;
    }
};
