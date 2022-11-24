#include <iostream>
#include <fstream>

template <class T>
class Nodo
{
public:
    T m_Dato;
    Nodo<T> *m_pSig;

public:
    Nodo(T d)
    {
        m_Dato = d;
        m_pSig = 0;
    }
};

template <class T>
class Cola
{
private:
    Nodo<T> *m_pFirst;
    Nodo<T> *m_pLast;
    int m_Size;

public:
    Cola()
    {
        m_pFirst = m_pLast = 0;
        m_Size = 0;
    }

    bool Empty()
    {
        if (m_pFirst)
        {
            return false;
        }
        return true;
    }
    void Pop()
    {
        if (!Empty())
        {
            Nodo<T> *p_Aux;
            p_Aux = m_pFirst;
            m_pFirst = m_pFirst->m_pSig;
            m_Size--;
            delete p_Aux;
        }
    }
    void Push(T d)
    {
        Nodo<T> *p_New = new Nodo<T>(d);
        if (Empty())
        {
            m_pFirst = m_pLast = p_New;
            m_Size++;
        }
        else
        {
            m_pLast->m_pSig = p_New;
            m_pLast = p_New;
            m_Size++;
        }
    }

    void Push()
    {
        T d;
        std::cout << "Ingrese el valor a Ingresar: ";
        std::cin >> d;
        Push(d);
        std::cout << "Elemento Ingresado Correctamente.\n";
    }

    T Back()
    {
        if (!Empty())
        {
            return m_pLast->m_Dato;
        }
    }

    T Front()
    {
        if (!Empty())
        {
            return m_pFirst->m_Dato;
        }
    }

    int Size()
    {
        return m_Size;
    }

    void Visualizer()
    {
        Nodo<T> *pTmp = m_pFirst;
        std::ofstream g;
        g.open("Cola.dot");
        g << "digraph A{\n";
        while (pTmp->m_pSig != NULL)
        {
            g << "\t" << pTmp->m_Dato << " -> " << pTmp->m_pSig->m_Dato << ";\n";
            pTmp = pTmp->m_pSig;
        }
        pTmp = m_pFirst;
        while (pTmp)
        {
            g << "\t" << pTmp->m_Dato << "[shape = rectangle, width = 1, height = 0.1];\n";
            pTmp = pTmp->m_pSig;
        }
        g << "}" << std::endl;
        g.close();
    }
};

void Menu()
{
    std::cout << "************************Cola************************\n";
    std::cout << "1. Ingresar en la Cola(Push)\n";
    std::cout << "2. Eliminar de la Cola(Pop)\n";
    std::cout << "3. Mostrar el Frente.\n";
    std::cout << "4. Mostrar el Final.\n";
    std::cout << "5. Mostrar el Tama" << char(164) << "o de la Cola\n";
    std::cout << "6. Mostrar la Cola.\n";
    std::cout << "7. Salir.\n";
}

int main()
{
    Cola<int> A;
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
            A.Push();
            break;
        case 2:
            A.Pop();
            break;
        case 3:
            std::cout << "El Frente es " << A.Front() << std::endl;
            break;
        case 4:
            std::cout << "El Final es " << A.Back() << std::endl;
            break;
        case 5:
            std::cout << "El Tama" << char(164) << "o de la Cola es " << A.Size() << std::endl;
            break;
        case 6:
            A.Visualizer();
            system("dot Cola.dot -o Cola.png -Tpng");
            system("C:\\Users\\Sebas-PC\\Desktop\\Clases_2022-II\\Algoritmos-y-Estructuras-de-Datos\\Visualizer\\Cola\\Cola.png");
            break;
        case 7:
            valid = false;
            break;
        default:
            std::cout << "Opcion no Valida." << std::endl;
            break;
        }
    } while (valid == true);
}