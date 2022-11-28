#include <iostream>
#include <fstream>
template <class T>
class Nodo
{
public:
    T m_Dato;
    Nodo<T> *m_pSon[2];
    Nodo<T> *m_pDad;
    bool m_Color;
    Nodo(T d)
    {
        m_Dato = d;
        m_pSon[0] = m_pSon[1] = 0;
        m_Color = 0;
        m_pDad = 0;
    }
};
template <class T>
class Tree
{
private:
    Nodo<T> *m_pRoot;

public:
    Tree() { m_pRoot = nullptr; }
    Nodo<T> *Padre(Nodo<T> *p)
    {
        if (p == m_pRoot)
        {
            return 0;
        }
        T d = p->m_Dato;
        Nodo<T> *q = m_pRoot;
        while (q->m_pSon[q->m_Dato < d]->m_Dato != p->m_Dato)
        {
            q = q->m_pSon[q->m_Dato < d];
        }
        return q;
    }
    Nodo<T> *Tio(Nodo<T> *q)
    {
        if (!q)
        {
            return 0;
        }
        Nodo<T> *p = Abuelo(q);
        if (p->m_Dato < q->m_Dato)
        {
            return p->m_pSon[0];
        }
        else
        {
            return p->m_pSon[1];
        }
    }
    Nodo<T> *Abuelo(Nodo<T> *p)
    {
        if (p->m_pDad == m_pRoot)
        {
            return 0;
        }
        Nodo<T> *q = p->m_pDad;
        Nodo<T> *r = q->m_pDad;
        return r;
    }
    void RI(Nodo<T> *&p)
    {
        Nodo<T> *q = p->m_pSon[1];
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
    void RD(Nodo<T> *&p)
    {
        Nodo<T> *q = p->m_pSon[0];
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

    void Caso01(Nodo<T> *&p)
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
    void Caso02(Nodo<T> *&p)
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
    void Caso03(Nodo<T> *&p)
    {
        Nodo<T> *tio = Tio(p), *a;
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
    void Caso04(Nodo<T> *&p)
    {
        Nodo<T> *q = Abuelo(p);
        Nodo<T> *r = p->m_pDad;
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
    void Caso05(Nodo<T> *&p)
    {
        Nodo<T> *q = Abuelo(p);
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
    void Add(T d)
    {

        if (!m_pRoot)
        {
            m_pRoot = new Nodo<T>(d);
            Caso01(m_pRoot);
            return;
        }
        else
        {
            Nodo<T> *p = m_pRoot;
            Nodo<T> *q = p;
            while (p)
            {
                q = p;
                if (p->m_Dato == d)
                    return;
                p = p->m_pSon[p->m_Dato < d];
            }
            Nodo<T> *&r = q->m_pSon[q->m_Dato < d];
            r = new Nodo<T>(d);
            r->m_pDad = Padre(r);
            Caso01(r);
        }
    }

    void Add()
    {
        T d;
        std::cout << "Ingrese el Valor a Ingresar: ";
        std::cin >> d;
        Add(d);
    }

    void Recorrer(Nodo<T> *p, std::ofstream &g)
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
            Recorrer(p->m_pSon[0], g);
            Recorrer(p->m_pSon[1], g);
        }
    }

    void Visualizer()
    {
        std::ofstream g;
        g.open("TreeRB.dot");
        g << "digraph A{\n";
        Recorrer(m_pRoot, g);
        g << "}";
    }
};

void Menu()
{
    std::cout << "************************Arbol Red/Black************************\n";
    std::cout << "1. Ingresar al Arbol\n";
    std::cout << "2. Eliminar del Arbol)\n";
    std::cout << "3. Mostrar el Arbol.\n";
    std::cout << "4. Salir.\n";
}
int main()
{
    Tree<int> A;
    /* int opc;
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
            system("dot TreeRB.dot -o TreeRB.png -Tpng");
            system("C:\\Users\\Sebas-PC\\Desktop\\Clases_2022-II\\Algoritmos-y-Estructuras-de-Datos\\Visualizer\\ArbolRedBlack\\TreeRB.png");
            break;
        case 4:
            valid = false;
            break;
        default:
            break;
        }
    } while (valid == true); */
    A.Add(70);
    A.Add(80);
    A.Add(100);
     A.Add(120);
    A.Add(170);
    A.Add(180);
    A.Add(115);
    A.Add(90);
     A.Add(95);
     A.Add(200);
    A.Add(300);
    A.Add(400);   
    A.Visualizer();
    system("dot TreeRB.dot -o TreeRB.png -Tpng");
    system("C:\\Users\\Sebas-PC\\Desktop\\Clases_2022-II\\Algoritmos-y-Estructuras-de-Datos\\Visualizer\\ArbolRedBlack\\TreeRB.png");
}
