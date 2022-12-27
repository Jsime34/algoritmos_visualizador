#include <iostream>
#include <fstream>
template <class T>
class NodoC
{
public:
    T m_Dato;
    NodoC<T> *m_pSig;

public:
    NodoC(T d)
    {
        m_Dato = d;
        m_pSig = 0;
    }
};


template <class T>
class Cola
{
private:
    NodoC<T> *m_pFirst;
    NodoC<T> *m_pLast;
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
            NodoC<T> *p_Aux;
            p_Aux = m_pFirst;
            m_pFirst = m_pFirst->m_pSig;
            m_Size--;
            delete p_Aux;
        }
    }
    void Push(T d)
    {
        NodoC<T> *p_New = new NodoC<T>(d);
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

    void Search(T d)
    {
        if (!Empty())
        {
            NodoC<T> *pTmp = m_pFirst;
            NodoC<T> *pAux;
            while (pTmp)
            {
                if (pTmp->m_Dato == d)
                {
                    pAux = pTmp;
                }
                pTmp = pTmp->m_pSig;
            }
            pTmp = m_pFirst;
            std::ofstream g;
            g.open("C:\\Users\\Sebas-PC\\Documents\\Prueba01QT\\Imagenes\\Cola.dot");
            g << "digraph Grafo{\n";
            g << "\trankdir = \"LR\";" << std::endl;
            g << "\tIn -> " << m_pFirst->m_Dato << ";\n";
            g << "\tIn [shape=Mdiamond, style = filled, color = gray];\n";
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
            g << "\t" << pAux->m_Dato << "[style = filled, color = yellow];\n";
            g << "\tCurrent -> " << pAux->m_Dato << ";\n";
            g << "\tCurrent [shape=Mdiamond, style = filled, color = yellow];\n";
            g << "}" << std::endl;
            g.close();
        }
    }

    void Visualizer()
    {
        NodoC<T> *pTmp = m_pFirst;
        std::ofstream g;
        g.open("C:\\Users\\Sebas-PC\\Documents\\Prueba01QT\\Imagenes\\Cola.dot");
        g << "digraph A{\n";
        g << "\trankdir = \"LR\";" << std::endl;
        g << "\tIn -> " << m_pFirst->m_Dato << ";\n";
        g << "\tIn [shape=Mdiamond, style = filled, color = gray];\n";
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
