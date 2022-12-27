#include <iostream>
#include <fstream>

template <class T>
class NodoP
{
public:
    T m_Dato;
    NodoP<T> *m_pAnt;

public:
    NodoP(T d)
    {
        m_Dato = d;
        m_pAnt = 0;
    }
};

template <class T>
class Pila
{
private:
    NodoP<T> *m_pTope;

public:
    Pila()
    {
        m_pTope = 0;
    }

    bool Empty()
    {
        return m_pTope == 0;
    }

    void Pop()
    {
        if (!m_pTope)
        {
            return;
        }
        NodoP<T> *tmp = m_pTope;
        m_pTope = m_pTope->m_pAnt;
        delete tmp;
    }

    void Push(T d)
    {
        NodoP<T> *pNuevo = new NodoP<T>(d);
        if (!m_pTope)
        {
            m_pTope = pNuevo;
        }
        else
        {
            pNuevo->m_pAnt = m_pTope;
            m_pTope = pNuevo;
        }
    }

    void Search(T d)
    {
        if (!Empty())
        {
            NodoP<T> *pTmp = m_pTope;
            NodoP<T> *pAux;
            while (pTmp)
            {
                if (pTmp->m_Dato == d)
                {
                    pAux = pTmp;
                }
                pTmp = pTmp->m_pAnt;
            }
            pTmp = m_pTope;
            std::ofstream g;
            g.open("C:\\Users\\Sebas-PC\\Documents\\Prueba01QT\\Imagenes\\Pila.dot");
            g << "digraph Grafo{\n";
            g << "\trankdir = \"LR\";" << std::endl;
            g << "\tTop -> " << m_pTope->m_Dato << ";\n";
            g << "\tTop [shape=Mdiamond, style = filled, color = gray];\n";
            while (pTmp->m_pAnt != NULL)
            {
                g << "\t" << pTmp->m_Dato << "->";
                pTmp = pTmp->m_pAnt;
                g << pTmp->m_Dato << ";" << std::endl;
            }
            pTmp = m_pTope;
            while (pTmp)
            {
                g << "\t" << pTmp->m_Dato << "[shape = rectangle, width = 1, height = 0.1];\n";
                pTmp = pTmp->m_pAnt;
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
        if (!Empty())
        {
            NodoP<T> *pTmp = m_pTope;
            std::ofstream g;
            g.open("C:\\Users\\Sebas-PC\\Documents\\Prueba01QT\\Imagenes\\Pila.dot");
            g << "digraph Grafo{\n";
            g << "\trankdir = \"LR\";" << std::endl;
            g << "\tTop -> " << m_pTope->m_Dato << ";\n";
            g << "\tTop [shape=Mdiamond, style = filled, color = gray];\n";
            while (pTmp->m_pAnt != NULL)
            {
                g << "\t" << pTmp->m_Dato << "->";
                pTmp = pTmp->m_pAnt;
                g << pTmp->m_Dato << ";" << std::endl;
            }
            pTmp = m_pTope;
            while (pTmp)
            {
                g << "\t" << pTmp->m_Dato << "[shape = rectangle, width = 1, height = 0.1];\n";
                pTmp = pTmp->m_pAnt;
            }

            g << "}" << std::endl;
            g.close();
        }
    }
};
