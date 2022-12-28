#include <iostream>
#include <list>  // lista doblemente enlazada
#include <Iterator>
#include <fstream>


using namespace std;

template<class T>
class Nodo_Binomial
{
    typedef   Nodo_Binomial<T>  *  pNodo;  
    public:
       T             m_Data;
       int           m_Grade;
       pNodo         m_pFather;
       list< pNodo>  m_Sons;
       
    public:

    Nodo_Binomial(T d)
    {
        m_Data = d;
        m_Grade = 0;
        m_pFather =0;

    }
  	void IMAGEN_NODO(ostream& out) {
		out << "node" << this << " [label=\"" << m_Data << "\"];" << endl;
	  	for (auto hijo : m_Sons) {
		    // Escribir la conexión entre el nodo actual y el hijo
		    out << "node" << this << " -> node" << hijo  << ";" << endl;
		    // Generar la información del hijo recursivamente
		    hijo ->IMAGEN_NODO(out);
		}
	}
    void Add_Son(pNodo p)
    {
        m_Sons.push_front(p);
    }
};

template<class T>
class Binomial_Heap
{
    typedef          Nodo_Binomial<T>   *  pNodo; 
    typedef typename list<pNodo>::iterator Iterator; 	
    public:
    	ofstream BINOMIAL;
    private:
      list<pNodo>  m_pHeads;
      int          m_size;
    private:

    // time complexity O(logn)
    /*
    void compact()
    {
    	if (m_pHeads.size() < 2) {return;}
    	auto it = m_pHeads.begin();
    	while (it != m_pHeads.end())
		{
			auto aux = next(it,1);
			if((*it)->m_Grade == (*aux)->m_Grade)
			{
				*it = link(*it,*aux);
				m_pHeads.erase(aux);
			}
		}
    			      
	}*/
	/*
	if (m_pHeads.size() < 2) {
	      return;
	    }
   		for (auto it : m_pHeads) {
	    	if (m_pHeads.empty() || it->m_pHeads.size() != m_pHeads.back()->m_Sons.size()) {
	        	m_pHeads.push_back(it);
	      	} else {
		        // Si el tamaño del montículo binomial actual es igual al tamaño del último elemento del vector, fusionar los dos montículos binomiales
		        
		        pNodo h1 = m_pHeads.back();
		        pNodo h2 = it;
		        m_pHeads.pop_front();
		        pNodo h = merge(h1, h2);
		        // Agregar el montículo binomial resultante al vector
		        compactedHeaps.push_back(h);
	      	
			}
		}
    	/*
    	auto it = m_pHeads.begin();
    

		if( m_pHeads.size() >= 2 )
		{
			auto dos = next(it,1);
	  		while(it!= m_pHeads.end() )
			{
				
				//cout<<"\n GRADOS: "<<(*it)->m_Grade<<" y "<<(*dos)->m_Grade<<" \n";
	  			if((*it)->m_Grade == (*dos)->m_Grade)
				{	
					if((*it)->m_Data < (*dos)->m_Data)
					{
					
						(*dos)->Add_Son(*it);	
						(*dos)-> m_Grade++;
						(*it)->m_pFather = (*dos);
						m_pHeads.swap()
				
					}else	
					{
				
						(*it)->Add_Son(*dos);
						(*it)-> m_Grade++;
						(*dos)->m_pFather = (*it);
						m_pHeads.erase(dos);
					}
				}
				dos = it;
				it++;
			}
		}	
		*/
	
	
	void compact()
	{
		if (m_pHeads.size() < 2) {return;}
		Iterator it = m_pHeads.begin();
		while (it != m_pHeads.end())
	  	{
			Iterator it2 = std::next(it, 1);
	    	if (it2 != m_pHeads.end() && (*it)->m_Grade == (*it2)->m_Grade) {
	      	*it = link(*it, *it2);
	      	m_pHeads.erase(it2);
	    }else{it++;}
	  }
	}
    // time complexity O(1)
    pNodo link(pNodo p, pNodo q)
    {
        if(p->m_Data < q->m_Data)
        {
            p->m_Sons.push_front(q);
            q->m_pFather = p;
            p->m_Grade++;
            return p;
        }
       q->m_Sons.push_front(p);
       p->m_pFather = q;
       q->m_Grade++;
       return q;
    }
    // complexity time O(logn)
    Iterator find_max()
    {
       Iterator it = m_pHeads.begin();
       Iterator Maximun = it; 
       for( ; it!=m_pHeads.end();++it)
       {
             if((*Maximun)->m_Data < (*it)->m_Data)
                 Maximun = it;
       }
       return Maximun;
    }

    public: 
    
    Binomial_Heap() { m_size =0;  }

    // Time complexity O(logn) 
    void Insert(T d)
    {
        pNodo pNew = new Nodo_Binomial<T>(d);
        m_pHeads.push_front(pNew);
        compact();
    }

    // complexity time O(logn)
    void Extract_Max()
    {
        // 1. Find max -> O(logn)
        Iterator pMax = find_max();
        // 2. subir todos sus hijos a la lista de cabezas -> O(logn)
        Iterator  it  = (*pMax)->m_Sons.begin();
        for( ;it!=(*pMax)->m_Sons.end();++it)
           // 3. O(1)
        m_pHeads.erase(pMax);
        // 4.compactar  --> O(logn)
        compact(); 
    }
    
    // time complexity O(logn)
    void Delete(pNodo p)
    {
        Increase_key(p,10000000);
        Extract_Max();
    }

    // time complexity O(logn)
    pNodo Get_Max()
    {
        Iterator it = find_max();
        return (*it);
    }

    // time complexity O(logn)
    void Increase_key(pNodo p, T d)
    {
        if(p->m_Data > d) return;
        	p->m_Data = d;
        while(p->m_pFather && p->m_pFather->m_Data < p->m_Data)
        {
        	swap(p->m_Data, p->m_pFather->m_Data);
        	p = p->m_pFather;
        }
    }

	void mostrar() {
	  for (auto head : m_pHeads) {
	    mostrar2(head, 0);
	  }
	}
	
	void mostrar2(pNodo node, int nivel) {
	  // Imprimir el nodo actual
	  std::cout << "Level " << nivel << ": " << node->m_Data << std::endl;
	  // Recorrer los hijos del nodo y llamar a la función de impresión recursivamente
	  for (auto it : node->m_Sons) {
	    mostrar2(it, nivel + 1);
	  }
	}


	
	void mostrar_IMAGEN()
	{
		BINOMIAL.open("BINOMIAL.dot");
		BINOMIAL<<"digraph Grafo{\n";
		for(auto Nodo_cabeza: m_pHeads)
		{
			Nodo_cabeza->IMAGEN_NODO(BINOMIAL);
		}
		BINOMIAL<< "}" << endl;
		system("dot -Tpng BINOMIAL.dot -o BINOMIAL.png ");
		system("BINOMIAL.png" );
		BINOMIAL.close();
	}
		
  
};

int main()
{
    Binomial_Heap<int> A;
    cout<<"A";
    for(int i=0;i<3;i++)
    	A.Insert(i);
    A.Insert(30);
    A.Insert(10);
    A.Insert(4);
    cout<<"Extrae el maximo :"<<A.Get_Max()->m_Data<<endl;
    //A.mostrar();
    
    A.mostrar_IMAGEN();
 
    return 0;
}
