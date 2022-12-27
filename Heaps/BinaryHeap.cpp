#include <iostream>
#include <fstream>
#include <vector>

template <typename T>
class NodoBH
{
public:
  T m_Dato;
  int m_Prioridad;
  int m_Hijos;

  NodoBH(T dato, int prioridad) : m_Dato(dato), m_Prioridad(prioridad), m_Hijos(0) {}
};

template <typename T>
class MinHeap
{
public:
  MinHeap() : m_pHeap() {}

  void Push(T m_Dato, int m_Prioridad)
  {
    m_pHeap.emplace_back(m_Dato, m_Prioridad);
    IncreaseKey(m_pHeap.size() - 1);
  }

  T Pop()
  {
    T top = m_pHeap.front().m_Dato;
    m_pHeap[0] = m_pHeap.back();
    m_pHeap.back().m_Dato = 0;
    m_pHeap.pop_back();
    DecreaseKey(0);
    return top;
  }

  void Print()
  {
    for (int i = 0; i < m_pHeap.size(); i++)
    {
      std::cout << m_pHeap[i].m_Dato << ", ";
    }
    std::cout << std::endl;
  }

  void Reset()
  {
    for (int i = 0; i < m_pHeap.size(); i++)
    {
      m_pHeap[i].m_Hijos = 0;
    }
  }

  void Visualizer()
  {
    Reset();
    std::ofstream g;
    g.open("BinaryHeap.dot");
    g << "digraph A{\n";
    int i = 0, j = 0;
    while (i < m_pHeap.size())
    {
      if (m_pHeap.size() == 1)
      {
        g << "\t" << m_pHeap[j].m_Dato << ";\n";
        g << "}";
        g.close();
        return;
      }
      if (m_pHeap.size() == 2)
      {
        g << "\t" << m_pHeap[j].m_Dato << " -> " << m_pHeap[j + 1].m_Dato << ";\n";
        g << "}";
        g.close();
        return;
      }
      if ((m_pHeap[i].m_Dato == m_pHeap.back().m_Dato))
      {
        g << "}";
        g.close();
        return;
      }
      else
      {
        if (m_pHeap[i].m_Hijos < 2)
        {
          if (m_pHeap[i + 1 + m_pHeap[i].m_Hijos].m_Dato != 0)
          {
            g << "\t" << m_pHeap[j].m_Dato << " -> " << m_pHeap[i + 1 + m_pHeap[i].m_Hijos].m_Dato << ";\n";
            if (m_pHeap[i + 1 + m_pHeap[i].m_Hijos].m_Dato == m_pHeap.back().m_Dato)
            {
              m_pHeap[i].m_Hijos += 2;
            }
            else
            {
              m_pHeap[i].m_Hijos += 1;
            }
          }
          else
          {
            m_pHeap[i].m_Hijos += 1;
          }
        }
        else
        {
          i += 2;
          j++;
        }
      }
    }
    g << "}";
    g.close();
  }

private:
  std::vector<NodoBH<T>> m_pHeap;

  void IncreaseKey(int pos)
  {
    while (pos > 0)
    {
      int padre = (pos - 1) / 2;
      if (m_pHeap[padre].m_Prioridad <= m_pHeap[pos].m_Prioridad)
      {
        break;
      }
      std::swap(m_pHeap[padre], m_pHeap[pos]);
      pos = padre;
    }
  }

  void DecreaseKey(int pos)
  {
    while (pos * 2 + 1 < m_pHeap.size())
    {
      int m_Hijos = pos * 2 + 1;
      if (m_Hijos + 1 < m_pHeap.size() &&
          m_pHeap[m_Hijos + 1].m_Prioridad < m_pHeap[m_Hijos].m_Prioridad)
      {
        m_Hijos++;
      }
      if (m_pHeap[pos].m_Prioridad <= m_pHeap[m_Hijos].m_Prioridad)
      {
        break;
      }
      std::swap(m_pHeap[pos], m_pHeap[m_Hijos]);
      pos = m_Hijos;
    }
  }
};
