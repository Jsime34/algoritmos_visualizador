#include <iostream>
#include <fstream>
#include <algorithm>
template <class T>
class Nodo
{

public:
    T m_Dato;
    Nodo<T> *m_pSon[2];
    int m_Height;
    int m_Factor;

public:
    Nodo(T d)
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

private:
    Nodo<T> *m_pRoot;

public:
    Tree()
    {
        m_pRoot = nullptr;
    }

    void RDD(Nodo<T> *&p)
    {
        Nodo<T> *q = p->m_pSon[1];
        p->m_pSon[1] = q->m_pSon[0];
        q->m_pSon[0] = p;
        p->m_Factor = 0;
        q->m_Factor = 0;
        p = q;
        if (!q->m_pSon[0]->m_pSon[0] && !q->m_pSon[0]->m_pSon[1])
        {
            q->m_pSon[0]->m_Height = 0;
            q->m_Height = q->m_pSon[0]->m_Height + 1;
        }
        else
        {
            q->m_pSon[0]->m_Height = 1 + std::max(q->m_pSon[0]->m_pSon[0]->m_Height, q->m_pSon[0]->m_pSon[1]->m_Height);
        }
    }

    void RII(Nodo<T> *&p)
    {
        Nodo<T> *q = p->m_pSon[0];
        p->m_pSon[0] = q->m_pSon[1];
        q->m_pSon[1] = p;
        p->m_Factor = 0;
        q->m_Factor = 0;
        p = q;
        if (!q->m_pSon[1]->m_pSon[0] && !q->m_pSon[1]->m_pSon[1])
        {
            q->m_pSon[1]->m_Height = 0;
            q->m_Height = q->m_pSon[1]->m_Height + 1;
        }
        else
        {
            q->m_pSon[1]->m_Height = 1 + std::max(q->m_pSon[1]->m_pSon[0]->m_Height, q->m_pSon[1]->m_pSon[1]->m_Height);
        }
    }

    void RDI(Nodo<T> *&p)
    {
        Nodo<T> *q = p->m_pSon[1];
        Nodo<T> *r = q->m_pSon[0];
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

    void RID(Nodo<T> *&p)
    {
        Nodo<T> *q = p->m_pSon[0];
        Nodo<T> *r = q->m_pSon[1];
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
            p->m_Factor = 1;
            q->m_Factor = -1;
            q->m_Height = 1;
            r->m_Factor = 0;
            r->m_Height = 2;
            break;
        }
        p = r;
    }

    void InsertR(T d, Nodo<T> *&p)
    {
        if (!p)
        {
            p = new Nodo<T>(d);
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

    void Insert(T d)
    {
        InsertR(d, m_pRoot);
    }

    void Add()
    {
        T d;
        std::cout << "Ingrese el dato que desea agregar: ";
        std::cin >> d;
        Insert(d);
    }

    void Mostrar(Nodo<T> *p, int contador)
    {
        if (p == NULL)
        {
            return;
        }
        else
        {
            Mostrar(p->m_pSon[1], contador + 1);
            for (int i = 0; i < contador; i++)
            {
                std::cout << "\t\t";
            }
            std::cout << p->m_Dato << ": " << p->m_Factor << std::endl;
            Mostrar(p->m_pSon[0], contador + 1);
        }
    }

    void Print()
    {
        Mostrar(m_pRoot, 0);
    }

    void VisualizerR(Nodo<T> *p, std::ofstream &g)
    {
        if (p != NULL)
        {
            if (p == m_pRoot)
            {
                g << "\t" << p->m_Dato << " [style = filled, color = gray];\n";
            }
            if (p->m_pSon[0] != NULL)
            {
                g << "\t" << p->m_Dato << " -> " << p->m_pSon[0]->m_Dato << ";\n";
                g << "\t" << p->m_pSon[0]->m_Dato << " [style = filled, color = gray];\n";
            }
            if (p->m_pSon[1] != NULL)
            {
                g << "\t" << p->m_Dato << " -> " << p->m_pSon[1]->m_Dato << ";\n";
                g << "\t" << p->m_pSon[1]->m_Dato << " [style = filled, color = gray];\n";
            }

            VisualizerR(p->m_pSon[0], g);
            VisualizerR(p->m_pSon[1], g);
        }
    }

    void Visualizer()
    {
        std::ofstream g;
        g.open("TreeAVL.dot");
        g << "digraph A{\n";
        g << "\tRoot -> " << m_pRoot->m_Dato << ";\n";
        g << "\tRoot [shape=Mdiamond, style = filled, color = gray];\n";
        VisualizerR(m_pRoot, g);
        g << "}";
    }
};

void Menu()
{
    std::cout << "************************Arbol AVL************************\n";
    std::cout << "1. Ingresar al Arbol\n";
    std::cout << "2. Eliminar del Arbol\n";
    std::cout << "3. Mostrar el Arbol.\n";
    std::cout << "4. Salir.\n";
}

int main()
{
    Tree<int> A;
    int opc;
    bool valid = true;
    do
    {
        system("cls");
        Menu();
        std::cout << "Ingrese Opci" << char(162) << "n V" << char(160) << "lida: ";
        std::cin >> opc;
        switch (opc)
        {
        case 1:
            A.Add();
            break;
        case 2:
            std::cout << "Funcion no implementada.\n";
            system("pause");
            break;
        case 3:
            A.Visualizer();
            system("dot TreeAVL.dot -o TreeAVL.png -Tpng");
            system("C:\\Users\\Sebas-PC\\Desktop\\Clases_2022-II\\Algoritmos-y-Estructuras-de-Datos\\Visualizer\\ArbolAVL\\TreeAVL.png");
            break;
        case 4:
            valid = false;
            break;
        default:
            std::cout << "Opci" << char(162) << "n no V" << char(160) << "lida. ";
            break;
        }
    } while (valid == true);
}
