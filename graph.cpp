#include "graph.h"
#include<stdexcept>
#include<queue>
#include<algorithm>

void Graph::addNode(std::string name)
{
    if(m_size == 0) {
        m_namesOfNodes.push_back(name);
        m_matrix.push_back(std::vector<bool>());
        m_matrix[0].push_back(0);
        m_size++;
    }
    else {
        if(checkName(name))
            throw std::runtime_error("Node already exists.");
        m_namesOfNodes.push_back(name);
        m_matrix.push_back(std::vector<bool>());
        for(int i = 0; i < m_size; i++)
            m_matrix[m_size].push_back(0);
        for(int i = 0; i < m_size + 1; i++)
            m_matrix[i].push_back(0);
        m_size++;


    }
}

void Graph::addPath(std::string from, std::string to)
{
    if((checkName(from) && checkName(to)) == 0 || from == to)
        throw std::runtime_error(std::string("There is no possible route between ")
                                 + from + std::string(" and ")
                                 + to + std::string("."));
    int from_pos, to_pos;
    for(int i = 0; i < m_size; i++) {
        if(m_namesOfNodes[i] == from)
            from_pos = i;
        if(m_namesOfNodes[i] == to)
            to_pos = i;
    }
    m_matrix[from_pos][to_pos] = 1;
    m_matrix[to_pos][from_pos] = 1;
}


bool Graph::checkName(std::string name) const
{
    for(int i = 0; i < m_size; i++)
        if(m_namesOfNodes[i] == name)
            return true;
    return false;
}

Graph::AdjacentMatrix Graph::getMatrix() const
{
    return m_matrix;
}

Graph::NamesList Graph::getNamesOfNodes() const
{
    return m_namesOfNodes;
}

int Graph::getIndex(std::string name)
{
    for(int i = 0; i < m_size; i++)
        if(m_namesOfNodes[i] == name)
            return i;
    return -1;
}

Graph::NamesList Graph::getPath(const std::vector<int> & array, int from, int to) const
{
    NamesList result;
    for(int i = to; i != from; i = array[i])
        result.push_back(m_namesOfNodes[i]);
    result.push_back(m_namesOfNodes[from]);
    std::reverse(result.begin(),result.end());
    return result;
}

Graph::NamesList Graph::DFS(std::string name)
{
        std::vector<int> used(m_size);      //Массив, хранящий использованные вершины
        std::vector<int> moved(m_size);      //Массив, хранящий пути
        bool found = false;
        int finish = getIndex(name);
        DFSrecursive(0, finish,found, moved, used);
        if(found)
            return getPath(moved,0,finish);
        else
            return NamesList();

}

void Graph::DFSrecursive(int current, int destination,
                         bool & found, std::vector<int> & moved,
                         std::vector<int> & used)
{
    if(found)
        return;
    if (current == destination) {  // Проверяем, конец ли
        found = true;
        return;
    }
    used[current] = 1;
    for ( int i=0; i<m_size; i++ )  //Находим смежные.
        if ( m_matrix[current][i]==1) {
            if(used[i] == 1)
                continue;
            moved[i] = current;
            DFSrecursive(i, destination, found, moved, used);
        }
}

Graph::NamesList Graph::BFS(std::string name)
{
    if(!checkName(name))
        throw std::runtime_error("There is no node with such name.");

    std::queue<int> turn;               //Это очередь, хранящая номера вершин
    std::vector<int> used(m_size);      //Массив, хранящий использованные вершины
    std::vector<int> from(m_size);      //Массив, хранящий пути

    turn.push(0);
    while(!turn.empty()) {              //Проверяем, пуста ли очередь
        int index = turn.front();       //Берем из очереди крайнюю вершину.
        if(m_namesOfNodes[index] == name)
            return getPath(from, 0, index);
        used[index] = 1;                //Помечаем как пройденную.
        turn.pop();                     //Удаляем ее.
        for ( int i=0; i<m_size; i++ )  //Находим смежные.
            if ( m_matrix[index][i]==1) {
                if(used[i] == 1)
                    continue;
                turn.push(i);           //добавляем в очередь вершину i.
                from[i] = index;
            }
    }
    return NamesList();
}

