#include<iostream>
#include<list>
#include <fstream>

using namespace std;

template<class Obj, int (*fd)(string, int) , int size = 11>
class Hash
{
    private:
       list<Obj> m_Tablal[size];
    private:

     
    public:
    ofstream BINOMIAL;
    Hash(){};  
    void Insert(string key, Obj obj)
    {
        int pos =fd(key,size);
        cout<<"Lugar de insercion : "<<pos<<endl; 
        m_Tablal[pos].push_back(obj);
    }

    void Print()
    {
       typedef typename list<Obj>::iterator ITERADOR;

      for (int  i = 0; i < size ; i++)
      {
         ITERADOR it = m_Tablal[i].begin();
         cout<<"["<<i<<"]" ;
         for(;it!=m_Tablal[i].end();++it)
           cout<<*it<<"-->";
         cout<<endl;
      }   
    }
    void generateElementNode(ostream& out, const Obj& obj) {
	  out << "node" << obj << " [label=\"" << obj << "\", shape=ellipse];" << endl;
	}
    
    void generateDot() {
    	
   		BINOMIAL.open("hash.dot");
		BINOMIAL<<"digraph Grafo{\n";
		for (int i = 0; i < size; i++) {
			BINOMIAL<< "node" << i << " [label=\"" << i << "\", shape=rectangle];" << endl;
		    for (auto& obj : m_Tablal[i]) {
		      generateElementNode(BINOMIAL, obj);
		      BINOMIAL<< "node" << i << " -> node" << obj << ";" << endl;
		    }
	   	}
		BINOMIAL<< "}" << endl;
		system("dot -Tpng hash.dot -o hash.png ");
		system("hash.png" );
		BINOMIAL.close();
	}


   
     
};

// Estas son funciones de disperción creadas por el usuario
  int FD1(string key, int size)
       {
            char * p = (char*)key.c_str();
            int s =0;
            while (*p)
            {
              s+=*p;
              p++;
            }
            return s%size;
            
       } 

 int FD2(string key, int size)
       {
            int s = key.size();
            if (s<2) return (key[0]*key[0])%size;
            return  (key[s/2]*key[s/2+1])%size;
            
       } 

int main()
{
   Hash<int,FD2>  A;
   A.Insert("cuatro",4);
   A.Insert("ocho",34);
   A.Insert("nueve",44);
   A.Insert("treitaitres",54);
   A.Insert("noventa",64);
   A.Insert("xxxx",774);
   A.Print();
	A.generateDot();
}