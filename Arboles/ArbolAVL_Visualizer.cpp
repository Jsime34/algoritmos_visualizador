#include <iostream>
#include <fstream>
#include <algorithm>
template <class T>
class Nodo
{
public:
    T m_Dato;
    int m_Factor;
    Nodo<T> *m_pSon[2];
    Nodo<T> *m_pDad;

public:
    Nodo(T d)
    {
        m_Dato = d;
        m_pSon[0] = m_pSon[1] = nullptr;
        m_Factor = 0;
        m_pDad = nullptr;
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

    void updateBalance(Nodo<T> *&p)
    {
        if (p->m_Factor < -1 || p->m_Factor > 1)
        {
            rebalance(p);
            return;
        }
        if (p->m_pDad != nullptr)
        {
            if (p == p->m_pDad->m_pSon[0])
            {
                p->m_pDad->m_Factor -= 1;
            }
            if (p == p->m_pDad->m_pSon[1])
            {
                p->m_pDad->m_Factor += 1;
            }
            if (p->m_pDad->m_Factor != 0)
            {
                Nodo<T> *r = p->m_pDad;
                updateBalance(r);
            }
        }
    }

    void rebalance(Nodo<T> *&p)
    {
        Nodo<T> *r;
        if (p->m_Factor > 0)
        {
            if (p->m_pSon[1]->m_Factor < 0)
            {
                r = p->m_pSon[1];
                rightRotate(r);
                leftRotate(p);
            }
            else
            {
                leftRotate(p);
            }
        }
        else if (p->m_Factor < 0)
        {
            if (p->m_pSon[0]->m_Factor > 0)
            {
                r = p->m_pSon[0];
                leftRotate(r);
                rightRotate(p);
            }
            else
            {
                rightRotate(p);
            }
        }
    }
    void leftRotate(Nodo<T> *&p)
    {
        Nodo<T> *q = p->m_pSon[1];
        p->m_pSon[1] = q->m_pSon[0];
        if (q->m_pSon[0] != nullptr)
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
        p->m_Factor = p->m_Factor - 1 - std::max(0, q->m_Factor);
        q->m_Factor = q->m_Factor - 1 + std::min(0, p->m_Factor);
    }
    void rightRotate(Nodo<T> *&p)
    {
        Nodo<T> *q = p->m_pSon[0];
        p->m_pSon[0] = q->m_pSon[1];
        if (q->m_pSon[1] != nullptr)
        {
            q->m_pSon[1]->m_pDad = p;
        }
        q->m_pDad = p->m_pDad;
        if (p->m_pDad == nullptr)
        {
            m_pRoot = q;
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
        p->m_Factor = p->m_Factor + 1 - std::min(0, q->m_Factor);
        q->m_Factor = q->m_Factor + 1 + std::max(0, p->m_Factor);
    }
    void Insert(T d)
    {
        Nodo<T> *p_New = new Nodo<T>(d);
        Nodo<T> *p = nullptr;
        Nodo<T> *q = m_pRoot;
        while (q != nullptr)
        {
            p = q;
            if (p_New->m_Dato < q->m_Dato)
            {
                q = q->m_pSon[0];
            }
            else
            {
                q = q->m_pSon[1];
            }
        }
        p_New->m_pDad = p;
        if (p == nullptr)
        {
            m_pRoot = p_New;
        }
        else if (p_New->m_Dato < p->m_Dato)
        {
            p->m_pSon[0] = p_New;
        }
        else
        {
            p->m_pSon[1] = p_New;
        }
        updateBalance(p_New);
    }

    void Recorrer(Nodo<T> *p, std::ofstream &g)
    {
        if (p != NULL)
        {
            if (p == m_pRoot)
            {
                g << "\t" << p->m_Dato << " [style = filled, color = black, fontcolor = white];\n";
            }
            if (p->m_pSon[0] != NULL)
            {
                g << "\t" << p->m_Dato << " -> " << p->m_pSon[0]->m_Dato << ";\n";
                g << "\t" << p->m_pSon[0]->m_Dato << " [style = filled, color = black, fontcolor = white];\n";
            }
            if (p->m_pSon[1] != NULL)
            {
                g << "\t" << p->m_Dato << " -> " << p->m_pSon[1]->m_Dato << ";\n";
                g << "\t" << p->m_pSon[1]->m_Dato << " [style = filled, color = black, fontcolor = white];\n";
            }
            Recorrer(p->m_pSon[0], g);
            Recorrer(p->m_pSon[1], g);
        }
    }

    void Visualizer()
    {
        std::ofstream g;
        g.open("TreeAVL.dot");
        g << "digraph A{\n";
        g << "\tRoot -> " << m_pRoot->m_Dato <<";\n";
        g << "\tRoot [shape=Mdiamond, style = filled, color = black, fontcolor = white];\n";
        Recorrer(m_pRoot, g);
        g << "}";
    }
};

void Menu()
{
    std::cout << "************************Arbol AVL************************\n";
    std::cout << "1. Ingresar al Arbol\n";
    std::cout << "2. Eliminar del Arbol)\n";
    std::cout << "3. Mostrar el Arbol.\n";
    std::cout << "4. Salir.\n";
}

int main()
{
    Tree<int> A;
    /*int opc;
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
    } while (valid == true);*/
    A.Insert(70);
    A.Insert(80);
    A.Insert(100);
    A.Insert(120);
    A.Insert(170);
    A.Insert(180);
    A.Insert(115);
    A.Insert(90);
    A.Insert(95);
    A.Insert(200);
    A.Insert(300);
    A.Insert(400);
    A.Insert(500);
    A.Insert(600);
    A.Visualizer();
}
