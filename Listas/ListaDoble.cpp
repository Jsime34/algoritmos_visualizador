#include <iostream>
#include <fstream>

template <class T>
class NodoLD
{

public:
    T m_Dato;
    NodoLD<T> *m_pSig;
    NodoLD<T> *m_pAnt;
    int m_Size;

public:
    NodoLD(T d)
    {
        m_Dato = d;
        m_pSig = 0;
        m_pAnt = 0;
        m_Size = 0;
    }
};

template <class T>
class ListaD
{

public:
    NodoLD<T> *m_pHead;
    NodoLD<T> *m_pLast;
    NodoLD<T> *m_pCurrent;

public:
    ListaD()
    {
        m_pHead = m_pLast = 0;
        m_pCurrent = 0;
    }


    void Push_Back(T d)
    {
        NodoLD<T> *pNuevo = new NodoLD<T>(d);
        if (!m_pHead)
        {
            m_pHead = m_pLast = pNuevo;
        }
        else
        {
            m_pLast->m_pSig = pNuevo;
            pNuevo->m_pAnt = m_pLast;
            m_pLast = pNuevo;
        }
    }

    void Push_Front(T d)
    {
        NodoLD<T> *pNuevo = new NodoLD<T>(d);
        if (!m_pLast)
        {
            m_pHead = m_pLast = pNuevo;
        }
        else
        {
            m_pHead->m_pAnt = pNuevo;
            pNuevo->m_pSig = m_pHead;
            m_pHead = pNuevo;
        }
    }

    void DeleteFront()
    {
        if (!Empty())
        {
            NodoLD<T> *pTmp = m_pHead;
            m_pHead = m_pHead->m_pSig;
            delete pTmp;
        }
    }

    void DeleteLast()
    {
        if (!Empty())
        {
            NodoLD<T> *pTmp = m_pLast;
            m_pLast = m_pLast->m_pAnt;
            delete pTmp;
        }
    }

    void Search(T d)
    {
        if(!Empty())
        {
            NodoLD<T> *pTmp = m_pHead;
            while (pTmp)
            {
                if (pTmp->m_Dato == d)
                {
                    m_pCurrent = pTmp;
                }
                pTmp = pTmp->m_pSig;
            }
            std::ofstream g;
            g.open("C:\\Users\\Sebas-PC\\Documents\\Prueba01QT\\Imagenes\\Lista_Doble.dot");
            g << "digraph A{\n";
            g << "\trankdir = \"LR\";" << std::endl;
            g << "\tRoot -> " << m_pHead->m_Dato << ";\n";
            g << "\tRoot [shape=Mdiamond, style = filled, color = gray];\n";
            pTmp = m_pHead;
            while (pTmp->m_pSig != NULL)
            {
                g << "\t" << pTmp->m_Dato << " -> " << pTmp->m_pSig->m_Dato << ";\n";
                pTmp = pTmp->m_pSig;
            }
            g << "\t" << m_pCurrent->m_Dato << "[style = filled, color = yellow];\n";
            g << "\tCurrent -> " << m_pCurrent->m_Dato << ";\n";
            g << "\tCurrent [shape=Mdiamond, style = filled, color = yellow];\n";
            g << "}" << std::endl;
            g.close();
        }
    }

    bool Empty()
    {
        if (m_pHead)
        {
            return false;
        }
        return true;
    }

    void Visualizer()
    {
        NodoLD<T> *pTmp = m_pHead;
        std::ofstream g;
        g.open("C:\\Users\\Sebas-PC\\Documents\\Prueba01QT\\Imagenes\\Lista_Doble.dot");
        g << "digraph A{\n";
        g << "\trankdir = \"LR\";" << std::endl;
        g << "\tRoot -> " << m_pHead->m_Dato << ";\n";
        g << "\tRoot [shape=Mdiamond, style = filled, color = gray];\n";
        while (pTmp->m_pSig != NULL)
        {
            g << "\t" << pTmp->m_Dato << " -> " << pTmp->m_pSig->m_Dato << ";\n";
            g << "\t" << pTmp->m_pSig->m_Dato << " -> " << pTmp->m_Dato << ";\n";
            pTmp = pTmp->m_pSig;
        }
        g << "}" << std::endl;
        g.close();
    }
};
