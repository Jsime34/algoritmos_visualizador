#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

template<class T>
class Nodo
{

	public:
		T    m_Dato;
		Nodo<T> * m_pSig;
		Nodo<T> * m_pAnt;
    public:
		Nodo(T d)
		{
			m_Dato = d;
			m_pSig = 0;
			m_pAnt = 0;
		}
};

template<class T>
class ListaD
{

public:
	 Nodo<T> * m_pHead;
	 Nodo<T> * m_pLast;
	 Nodo<T> * m_Current;
	 
   int m_size;
public:
	ListaD()
	{
		m_pHead = m_pLast =0;
		m_Current=0;
    	m_size=0;
	}

    int size(){return m_size;}

	void Add_Last(T d)
	{
    //if(d=="FIN") return;
   	Nodo<T> * pNuevo = new Nodo<T>(d);
	if (!m_pHead){
		m_pHead = m_pLast = pNuevo;
	}
	else
	{
		m_pLast->m_pSig =pNuevo;
		pNuevo->m_pAnt = m_pLast;
		m_pLast = pNuevo;
	}
    m_size++;
	}

	void Add_First(T d){
		Nodo<T> *pNuevo = new Nodo<T>(d);
		if(!m_pLast){
			m_pHead = m_pLast = pNuevo;
		}
		else{
			m_pHead->m_pAnt = pNuevo;
			pNuevo->m_pSig = m_pHead;
			m_pHead = pNuevo;
		}
		m_size++;
	}

	void Print()
	{
		Nodo<T> * tmp = m_pHead;
		while(tmp!=0)
		{
			cout<<tmp->m_Dato<<endl;
			tmp = tmp->m_pSig;
		}
	}




	bool find(T d)
	{
		Nodo<T> * tmp = m_pHead;
		while(tmp!=0)
		{
			if(tmp->m_Dato==d) return true;
			tmp = tmp->m_pSig;
		}
		return false;
	}

	void Visualizer()
    {
        Nodo<T> *pTmp = m_pHead;
        ofstream g;
        g.open("graphviz1.dot");
        g << "digraph A{\n";
        g << "\trankdir = \"LR\";" << endl;
        while (pTmp->m_pSig != NULL)
        {
            g << "\t" << pTmp->m_Dato << " -> " << pTmp->m_pSig->m_Dato << ";\n";
			g << "\t" << pTmp->m_pSig->m_Dato << " -> " << pTmp->m_Dato << ";\n";
            pTmp = pTmp->m_pSig;
        }
        g << "}" << endl;
        g.close();
    }
};

int main(){
	ListaD<int> grafito;
	grafito.Add_Last(8);
	grafito.Add_Last(10);
	grafito.Add_Last(12);
	grafito.Add_Last(15);
	grafito.Visualizer();
	return 1;
}