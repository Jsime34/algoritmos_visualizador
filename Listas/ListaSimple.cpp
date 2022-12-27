#include <iostream>
#include <fstream>

template <class T>
class NodoLS
{
public:
    T m_Dato;
    NodoLS *m_pSig;
    int m_Size;

public:
    NodoLS(T d)
    {
        m_Dato = d;
        m_pSig = 0;
        m_Size = 0;
    }
};

template <class T>
class Lista_Simple
{
private:
    NodoLS<T> *m_pHead;

public:
    Lista_Simple()
    {
        m_pHead = 0;
    }

    void Push_Back(T d)
    {
        NodoLS<T> *pNew = new NodoLS<T>(d);
        NodoLS<T> *pTmp = m_pHead;
        NodoLS<T> *pFinal;
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

    void Search(T d)
    {
        if (!Empty())
        {
            NodoLS<T> *pTmp = m_pHead;
            NodoLS<T> *pAux;
            while (pTmp)
            {
                if (pTmp->m_Dato == d)
                {
                    pAux = pTmp;
                }
                pTmp = pTmp->m_pSig;
            }
            std::ofstream g;
            g.open("C:\\Users\\Sebas-PC\\Documents\\Prueba01QT\\Imagenes\\Lista_Simple.dot");
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
            g << "\t" << pAux->m_Dato << "[style = filled, color = yellow];\n";
            g << "\tCurrent -> " << pAux->m_Dato << ";\n";
            g << "\tCurrent [shape=Mdiamond, style = filled, color = yellow];\n";
            g << "}" << std::endl;
            g.close();
        }
    }

    void Push_Front(T d)
    {
        NodoLS<T> *pNew = new NodoLS<T>(d);
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
            NodoLS<T> *pTmp = m_pHead;
            m_pHead = m_pHead->m_pSig;
            delete pTmp;
        }
    }

    void DeleteLast()
    {
        if (!Empty())
        {
            NodoLS<T> *pTmp = m_pHead;
            NodoLS<T> *valor = NULL;
            while ((pTmp != NULL) && (pTmp->m_pSig != NULL))
            {
                valor = pTmp;
                pTmp = pTmp->m_pSig;
            }
            valor->m_pSig = pTmp->m_pSig;
            delete pTmp;
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
        NodoLS<T> *pTmp = m_pHead;
        std::ofstream g;
        g.open("C:\\Users\\Sebas-PC\\Documents\\Prueba01QT\\Imagenes\\Lista_Simple.dot");
        g << "digraph A{\n";
        g << "\trankdir = \"LR\";" << std::endl;
        g << "\tRoot -> " << m_pHead->m_Dato << ";\n";
        g << "\tRoot [shape=Mdiamond, style = filled, color = gray];\n";
        while (pTmp->m_pSig != NULL)
        {
            g << "\t" << pTmp->m_Dato << " -> " << pTmp->m_pSig->m_Dato << ";\n";
            pTmp = pTmp->m_pSig;
        }
        g << "}" << std::endl;
        g.close();
    }
};
