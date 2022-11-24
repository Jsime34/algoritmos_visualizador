#include <string>
#include <iostream>
#include <fstream>

using namespace std;


template<class T>
class Nodo
{
  public:
     T          m_Dato;
     Nodo<T>  * m_pAnt;
  public:
     Nodo(T d)
     {
       m_Dato = d;
       m_pAnt = 0;
     }
  
};

template<class T>
class Pila
{
    private:
     Nodo<T> * m_pTope;
    public:
       Pila()
       {
         m_pTope =0;
       }
       bool IsEmpty()
       {
           return m_pTope==0;         
       }
       void Pop()
       {
          if(!m_pTope) return;
          
          Nodo<T> * tmp = m_pTope; 
          m_pTope = m_pTope->m_pAnt; 
          delete tmp;
           
       }
       void Push(T d)
       {
        Nodo<T> * pNuevo = new Nodo<T>(d); 
        if(!m_pTope)
		
            m_pTope =  pNuevo;
            
        else
        {
         pNuevo->m_pAnt = m_pTope; 
         m_pTope = pNuevo;
         
        }
       }
       
       T *  Top()
       {
          if(!IsEmpty())
		  {
		  	 return &(m_pTope->m_Dato);
		  }    
          return 0;
       }
       void mostrar()
		{
			ofstream PILA;
			Nodo<T>*aux =  m_pTope;
			PILA.open("PILA.dot");
			PILA<<"digraph Grafo{\n";
			PILA<<"TOPE"<<"->";
			while(aux)
			{
				PILA<<aux->m_Dato<<"->";
				aux=aux->m_pAnt;
				
				if(aux==NULL){
					PILA<<"NULL";
					break;
				}
				PILA<<aux->m_Dato<<";"<<endl;
			}
			PILA<< "}" << endl;
			system("dot -Tpng PILA.dot -o PILA.png ");
			system("PILA.png" );
			PILA.close();
		}
       void mostrar_C()
	   {
	   		Nodo<T>*aux =  m_pTope;
	   		while(aux)
			{
				cout<<aux->m_Dato;
				aux=aux->m_pAnt;
			}
	   }
};


int main()
{

  Pila<int>  A;
 	A.Push(1);
  	A.Push(2);
  	A.Push(3);
  	A.Push(4);
	A.Push(5);
	A.Push(6);
  /*
  cout<<*(A.Top())<<" ";
  A.Pop();
  cout<<*(A.Top())<<" ";
  A.Pop();
  cout<<*(A.Top())<<" ";
  A.Pop();
  */
  
  //cout<<*(A.Top())<<" ";
  
  A.mostrar_C();
  //A.mostrar();
  A.Pop();
  A.mostrar();
  A.Pop();
  return 0;
  
  
  
}

