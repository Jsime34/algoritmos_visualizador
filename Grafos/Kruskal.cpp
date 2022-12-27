#include <list>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>

template <class V, class A>
class Edge_Kruskal;

template <class V, class A>
class Vertex_Kruskal
{
public:
    V m_Dato;
    bool m_Visit;
    std::list<Edge_Kruskal<V, A>> m_list_Edge;

    Vertex_Kruskal(V vertice)
    {
        m_Dato = vertice;
        m_Visit = false;
    }

    bool operator==(const Vertex_Kruskal<V, A> &Ve)
    {
        return m_Dato == Ve.m_Dato;
    }
};

template <class V, class A>
class Edge_Kruskal
{
public:
    A m_Dato;
    V m_Origen;
    Vertex_Kruskal<V, A> *m_pVertex_Kruskal;

    Edge_Kruskal(V v, A a, Vertex_Kruskal<V, A> *q = 0)
    {
        m_Dato = a;
        m_Origen = v;
        m_pVertex_Kruskal = q;
    }

    bool operator==(const Edge_Kruskal<V, A> &Ar)
    {
        return m_Dato == Ar.m_Dato;
    }

    bool operator<(const Edge_Kruskal<V, A> &b) const
    {
        return m_Origen < b.m_Origen;
    }
};

struct greater
{
    template <class V, class A>
    bool operator()(const Edge_Kruskal<V, A> &x, const Edge_Kruskal<V, A> &y) const
    {
        return x.m_Dato > y.m_Dato;
    }
};

template <class V, class A>
class DisjointSet
{
    std::unordered_map<V, V> parent;

public:
    typedef typename std::list<Vertex_Kruskal<V, A>>::iterator Iterator_Vertex_Kruskal;
    void makeSet(std::list<Vertex_Kruskal<V, A>> &m_Graph)
    {
        Iterator_Vertex_Kruskal it = m_Graph.begin();
        for (int i = 0; i < m_Graph.size(); i++)
        {
            parent[it->m_Dato] = it->m_Dato;
            ++it;
        }
    }

    V Find(V k)
    {
        if (parent[k] == k)
        {
            return k;
        }

        return Find(parent[k]);
    }

    void Union(V a, V b)
    {
        V x = Find(a);
        V y = Find(b);

        parent[x] = y;
    }
};

template <class V, class A>
class Graph_Kruskal
{
    typedef typename std::list<Vertex_Kruskal<V, A>>::iterator Iterator_Vertex_Kruskal;
    typedef typename std::list<Edge_Kruskal<V, A>>::iterator Iterator_Edge_Kruskal;

public:
    Graph_Kruskal(){};

    void Insert(V Vertice)
    {
        m_Graph.push_back(Vertex_Kruskal<V, A>(Vertice));
    };

    void Insert_Edge(V v1, V v2, A a)
    {
        Iterator_Vertex_Kruskal p = find_Vertex_Kruskal(v1);
        Iterator_Vertex_Kruskal q = find_Vertex_Kruskal(v2);
        if (p != m_Graph.end() && q != m_Graph.end())
        {
            Vertex_Kruskal<V, A> *pDestino1 = &(*q);
            Vertex_Kruskal<V, A> *pDestino2 = &(*p);
            p->m_list_Edge.push_back(Edge_Kruskal<V, A>(p->m_Dato, a, pDestino1));
            q->m_list_Edge.push_back(Edge_Kruskal<V, A>(q->m_Dato, a, pDestino2));
        }
    }

    void Kruskal()
    {
        std::list<Edge_Kruskal<V, A>> MST;
        std::priority_queue<Edge_Kruskal<V, A>, std::vector<Edge_Kruskal<V, A>>, greater> edges;
        InsertEdgeKruskal(edges);
        DisjointSet<V, A> ds;
        ds.makeSet(m_Graph);

        while (MST.size() + 1 < m_Graph.size())
        {
            Edge_Kruskal<V, A> e = edges.top();
            edges.pop();

            V x = ds.Find(e.m_Origen);
            V y = ds.Find(e.m_pVertex_Kruskal->m_Dato);

            if (x != y)
            {
                MST.push_back(e);
                ds.Union(x, y);
            }
        }
        MST.sort();
        Iterator_Vertex_Kruskal it = m_Graph.begin();
        std::list<V> G;
        typedef typename std::list<V>::iterator Iterator;
        std::ofstream g;
        g.open("Kruskal.dot");
        g << "graph A{\n";
        g << "\trankdir = \"LR\";" << std::endl;
        for (; it != m_Graph.end(); it++)
        {
            Iterator_Edge_Kruskal it_e = it->m_list_Edge.begin();
            for (; it_e != it->m_list_Edge.end(); ++it_e)
            {
                Iterator_Edge_Kruskal it_q = MST.begin();
                Iterator l = std::find(G.begin(), G.end(), it_e->m_pVertex_Kruskal->m_Dato);
                if ((it_e->m_Origen == it_q->m_Origen) && (it_e->m_pVertex_Kruskal->m_Dato == it_q->m_pVertex_Kruskal->m_Dato))
                {
                    g << "\t" << it->m_Dato << " -- " << it_e->m_pVertex_Kruskal->m_Dato << " [label = " << it_e->m_Dato << ", color = red];\n";
                    MST.pop_front();
                }
                else if (l == G.end())
                {
                    g << "\t" << it->m_Dato << " -- " << it_e->m_pVertex_Kruskal->m_Dato << " [label = " << it_e->m_Dato << "];\n";
                }
            }
            G.push_back(it->m_Dato);
        }
        g << "}" << std::endl;
        g.close();
    }

    void Visualizer()
    {
        Iterator_Vertex_Kruskal it = m_Graph.begin();
        std::list<V> G;
        typedef typename std::list<V>::iterator Iterator;
        std::ofstream g;
        g.open("Kruskal.dot");
        g << "graph A{\n";
        g << "\trankdir = \"LR\";" << std::endl;
        for (; it != m_Graph.end(); it++)
        {
            if (!it->m_list_Edge.empty())
            {
                Iterator_Edge_Kruskal it_e = it->m_list_Edge.begin();
                for (; it_e != it->m_list_Edge.end(); ++it_e)
                {
                    Iterator l = std::find(G.begin(), G.end(), it_e->m_pVertex_Kruskal->m_Dato);
                    if (l == G.end())
                    {
                        g << "\t" << it->m_Dato << " -- " << it_e->m_pVertex_Kruskal->m_Dato << " [label = " << it_e->m_Dato << "];\n";
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
    std::list<Vertex_Kruskal<V, A>> m_Graph;

    Iterator_Vertex_Kruskal find_Vertex_Kruskal(V v)
    {
        return std::find(m_Graph.begin(), m_Graph.end(), Vertex_Kruskal<V, A>(v));
    }

    bool find_edge(V v, A a)
    {
        Iterator_Vertex_Kruskal p = find_Vertex_Kruskal(v);
        Iterator_Edge_Kruskal q = std::find(p->m_list_Edge.begin(), p->m_list_Edge.end(), Edge_Kruskal<V, A>(a));
        if (q != p->m_list_Edge.end())
        {
            return true;
        }
    }

    void InsertEdgeKruskal(std::priority_queue<Edge_Kruskal<V, A>, std::vector<Edge_Kruskal<V, A>>, greater> &P)
    {
        Iterator_Vertex_Kruskal it = m_Graph.begin();
        std::list<V> G;
        typedef typename std::list<V>::iterator Iterator;
        for (; it != m_Graph.end(); ++it)
        {
            Iterator_Edge_Kruskal it_e = it->m_list_Edge.begin();
            for (; it_e != it->m_list_Edge.end(); ++it_e)
            {
                Iterator l = std::find(G.begin(), G.end(), it_e->m_pVertex_Kruskal->m_Dato);
                if (l == G.end())
                {
                    P.push(*it_e);
                }
            }
            G.push_back(it->m_Dato);
        }
    }
};
