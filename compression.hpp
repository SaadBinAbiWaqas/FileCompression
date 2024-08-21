#include<vector>
#include<fstream>
#include<queue>
#include<functional>
#include"Node.cpp"
#include<String>
using namespace std;
class Compression{
    vector<Node*> nodes;
    Node* root;
    string InputFileName;
    string OutputFileName;

    struct NodeComparator {
    bool operator()(const Node* a, const Node* b) const {
        return a->frequency > b->frequency; // '>' for min heap
    }
};

    priority_queue<Node*, vector<Node*>, NodeComparator> min_Heap;

    Compression();
    // Compression(string, string);
   

    
    void init_Node();

    public:

    //add calls for these function in prev functions
    // e.g, Compression constructor wil call the init_array
    // the after initalising the array of nodes, it will the call the min_Heap fun
    // after that, min_Heap will call Huff_tree function
    // then Huff_Tree will call travesal function
    // and finally, traversal will call save_Codes function 

   Compression(string, string);
   
   void call_Traverse();
    void Compress();
    void MakeMin_Heap();
    void Huff_Tree();
    void traverse_Codes(Node* , string );
    void save_File(string, string);
    void call_Save();
    int binToDec(string);
    
};