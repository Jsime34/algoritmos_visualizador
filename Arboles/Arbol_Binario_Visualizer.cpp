#include <iostream>
#include <fstream>
template <class T>
class Nodo
{
public:
    T m_Dato;
    Nodo<T> *m_pSon[2];
    Nodo(T d)
    {
        m_Dato = d;
        m_pSon[0] = m_pSon[1] = 0;
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
    void Add(T d)
    {
        if (!m_pRoot)
        {
            m_pRoot = new Nodo<T>(d);
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
                g << "\t" << p->m_pSon[0]->m_Dato << "[style = filled, color = black, fontcolor = white];\n";
            }
            if (p->m_pSon[1] != NULL)
            {
                g << "\t" << p->m_Dato << " -> " << p->m_pSon[1]->m_Dato << ";\n";
                g << "\t" << p->m_pSon[1]->m_Dato << "[style = filled, color = black, fontcolor = white];\n";
            }
            Recorrer(p->m_pSon[0], g);
            Recorrer(p->m_pSon[1], g);
        }
    }

    void Visualizer()
    {
        std::ofstream g;
        g.open("TreeBinary.dot");
        g << "digraph A{\n";
        Recorrer(m_pRoot, g);
        g << "}";
    }
};

void Menu()
{
    std::cout << "************************Arbol Binario************************\n";
    std::cout << "1. Ingresar al Arbol\n";
    std::cout << "2. Eliminar del Arbol)\n";
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
            system("dot TreeBinary.dot -o TreeBinary.png -Tpnwg");
            system("C:\\Users\\Sebas-PC\\Desktop\\Clases_2022-II\\Algoritmos-y-Estructuras-de-Datos\\Visualizer\\ArbolBinario\\TreeBinary.png");
            break;
        case 4:
            valid = false;
            break;
        default:
            break;
        }
    } while (valid == true);
}