#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<string>
#include<list>

class Graph
{
private:
    typedef std::vector<std::vector<bool>> AdjacentMatrix;
    typedef std::vector<std::string> NamesList;
    NamesList m_namesOfNodes;
    AdjacentMatrix m_matrix;
    int m_size;

private:
    bool checkName(std::string) const;
    NamesList getPath(const std::vector<int> &, int from, int to) const;
    void DFSrecursive(int current, int destination,
                      bool & found, std::vector<int> & moved,
                      std::vector<int> & used);

public:
    Graph() : m_size(0) {}

    AdjacentMatrix getMatrix() const;
    NamesList getNamesOfNodes() const;
    int getIndex(std::string);

    void addNode(std::string name);
    void addPath(std::string from, std::string to);
    NamesList BFS(std::string name);
    NamesList DFS(std::string name);

};

#endif // GRAPH_H
