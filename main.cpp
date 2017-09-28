#include<iostream>
#include<graph.h>

void printMenu();
void errMsg(std::string what);

int main()
{
    using std::cout;
    using std::cin;

    Graph graph;
    std::cout << "Hello, this is a lil' programm which helps you to test the Graph class. Enjoy!\n\n\n";
    printMenu();
    char ch;
    cin.get(ch).get();
    while (toupper(ch) != 'Q') {
        switch (ch) {
            case '1': {
                std::string temp;
                cout << "Name of the node: _\b";
                std::getline(cin,temp);
                try {
                    graph.addNode(temp);
                }
                catch(std::runtime_error & e) {
                        errMsg(e.what());
                        break;
                }
                cout << "Successfull.\n";
                break;
            }
            case '2': {
                std::string temp1;
                cout << "Name of the first node: _\b";
                std::getline(cin,temp1);
                std::string temp2;
                cout << "Name of the second node: _\b";
                std::getline(cin,temp2);
                try {
                    graph.addPath(temp1,temp2);
                }
                catch(std::runtime_error & e) {
                        errMsg(e.what());
                        break;
                }
                cout << "Successfull.\n";
                break;
            }
            case '3': {
                std::string temp;
                cout << "Name of the searching node: _\b";
                std::getline(cin,temp);
                try {
                    auto result = graph.BFS(temp);
                    if(result.size()) {
                        cout << "Path to " << temp << " is " ;
                        for(auto node : result)
                            cout << node << "  ";
                        cout << std::endl;
                    }
                    else
                        cout << "There is no route between beginning of the Graph and " << temp << ".\n";
                }
                catch(std::runtime_error & e) {
                        errMsg(e.what());
                        break;
                }
                cout << "Successfull.\n";
                break;
            }
        case '4': {
            std::string temp;
            cout << "Name of the searching node: _\b";
            std::getline(cin,temp);
            try {
                auto result = graph.DFS(temp);
                if(result.size()) {
                    cout << "Path to " << temp << " is " ;
                    for(auto node : result)
                        cout << node << "  ";
                    cout << std::endl;
                }
                else
                    cout << "There is no route between beginning of the Graph and " << temp << ".\n";
            }
            catch(std::runtime_error & e) {
                    errMsg(e.what());
                    break;
            }
            cout << "Successfull.\n";
            break;
        }
            case '5': {
                auto matrix = graph.getMatrix();
                if(!matrix.size())
                    cout << "Empty matrix.\n";
                else {
                    auto names = graph.getNamesOfNodes();
                    for(auto name : names)
                        cout << "\t" <<name;
                    cout << std::endl;
                    auto iter = names.begin();
                    for(auto row : matrix) {
                        cout << *iter++ << "\t";
                        for(auto element : row)
                            cout << element << "\t";
                        cout << std::endl;
                    }
                }
                break;
            }
            default:
                errMsg("\nWrong input pls try again.");
                break;
        }
        printMenu();
        cin.get(ch).get();
    }
}

void printMenu()
{

    std::cout<< "\n\nChoose one of the functions below: (q to quit)\n\n"
         << "==============================================\n"
         << "1)Add node.\t\t\t 2)Add path.\n"
         << "3)Find path(BFS).\t\t 4)Find path(DFS).\n"
         << "5)Show adjacent matrix.\n"
         << "Input:_\b";
}

void errMsg(std::string what)
{
    std::cerr << what << std::endl;
}
