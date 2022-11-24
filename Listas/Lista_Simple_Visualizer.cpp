#include <iostream>
#include <fstream>

template <class T>
class Nodo
{
public:
    T m_Dato;
    Nodo *m_pSig;
    int m_Size;

public:
    Nodo(T d)
    {
        m_Dato = d;
        m_pSig = 0;
        m_Size = 0;
    }
};

template <class T>
class Lista
{
private:
    Nodo<T> *m_pHead;

public:
    Lista()
    {
        m_pHead = 0;
    }

    void Push_Back(T d)
    {
        Nodo<T> *pNew = new Nodo<T>(d);
        Nodo<T> *pTmp = m_pHead;
        Nodo<T> *pFinal;
        if (Empty())
        {
            m_pHead = pNew;
            m_pHead->m_Size++;
        }
        else
        {
            while (pTmp)
            {
                if (pTmp->m_pSig == NULL)
                {
                    pFinal = pTmp;
                }
                pTmp = pTmp->m_pSig;
            }
            pFinal->m_pSig = pNew;
            m_pHead->m_Size++;
        }
    }

    void Push(bool Valid)
    {
        T d;
        std::cout << "Ingrese el Valor a Ingresar: ";
        std::cin >> d;
        if (Valid == true)
        {
            Push_Front(d);
        }
        else
        {
            Push_Back(d);
        }
    }

    void Push_Front(T d)
    {
        Nodo<T> *pNew = new Nodo<T>(d);
        if (Empty())
        {
            m_pHead = pNew;
            m_pHead->m_Size++;
        }
        else
        {
            pNew->m_pSig = m_pHead;
            m_pHead = pNew;
            m_pHead->m_Size++;
        }
    }

    void DeleteFront()
    {
        if (!Empty())
        {
            Nodo<T> *pTmp = m_pHead;
            m_pHead = m_pHead->m_pSig;
            delete pTmp;
        }
    }

    void DeleteLast()
    {
        if (!Empty())
        {
            Nodo<T> *pTmp = m_pHead;
            Nodo<T> *valor = NULL;
            while ((pTmp != NULL) && (pTmp->m_pSig != NULL))
            {
                valor = pTmp;
                pTmp = pTmp->m_pSig;
            }
            valor->m_pSig = pTmp->m_pSig;
            delete pTmp;
        }
    }

    T Front()
    {
        return m_pHead->m_Dato;
    }

    int Size()
    {
        return m_pHead->m_Size;
    }

    bool Empty()
    {
        if (m_pHead)
        {
            return false;
        }
        return true;
    }

    void Print()
    {
        Nodo<T> *pTmp = m_pHead;
        while (pTmp)
        {
            std::cout << pTmp->m_Dato << " --> ";
            pTmp = pTmp->m_pSig;
        }
    }
    void Visualizer()
    {
        Nodo<T> *pTmp = m_pHead;
        std::ofstream g;
        g.open("Lista_Simple.dot");
        g << "digraph A{\n";
        g << "\trankdir = \"LR\";" << std::endl;
        while (pTmp->m_pSig != NULL)
        {
            g << "\t" << pTmp->m_Dato << " -> " << pTmp->m_pSig->m_Dato << ";\n";
            pTmp = pTmp->m_pSig;
        }
        g << "}" << std::endl;
        g.close();
    }
};

void Menu()
{
    std::cout << "************************Lista Simple************************\n";
    std::cout << "1. Insertar en el Frente.\n";
    std::cout << "2. Insertar en la Cola.\n";
    std::cout << "3. Eliminar el Frente.\n";
    std::cout << "4. Eliminar la Cola.\n";
    std::cout << "5. Mostrar el Frente.\n";
    std::cout << "6. Mostrar el Tama" << char(164) << "o de la Lista.\n";
    std::cout << "7. Mostrar la Lista.\n";
    std::cout << "8. Salir.\n";
}

int main()
{

    Lista<int> A;
    int opc;
    bool valid = true;
    do
    {
        system("cls");
        Menu();
        std::cout << "Ingrese Opcion Valida: ";
        std::cin >> opc;
        switch (opc)
        {
        case 1:
            A.Push(true);
            break;
        case 2:
            A.Push(false);
            break;
        case 3:
            A.DeleteFront();
            break;
        case 4:
            A.DeleteLast();
            break;
        case 5:
            std::cout << A.Front();
            break;
        case 6:
            std::cout << A.Size();
            break;
        case 7:
            A.Visualizer();
            system("dot Lista_Simple.dot -o Lista_Simple.png -Tpng");
            system("C:\\Users\\Sebas-PC\\Desktop\\Clases_2022-II\\Algoritmos-y-Estructuras-de-Datos\\Visualizer\\Lista_Simple\\Lista_Simple.png");
            break;
        case 8:
            valid = false;
            break;
        default:
            std::cout << "Opcion no Valida." << std::endl;
            break;
        }
    } while (valid == true);
}
