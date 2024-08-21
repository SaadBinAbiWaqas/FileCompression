#include"compression.hpp"
#include<iostream>

Compression::Compression(){}

Compression::Compression(string inputfile, string outputfile){
    this->InputFileName = inputfile;
    this->OutputFileName = outputfile;
    init_Node();
}
// Compression::Compression(string inputfile){
//     this->InputFileName = inputfile;
//     init_Node();
// }

Compression::Compression(string file)
{
	this->InputFileName = file;
	init_Node();
}

void Compression::call_Traverse(){
	traverse_Codes(root, " ");
}

void Compression::init_Node()
{
	for(int i = 0; i < 128; i++)
	{
		nodes.push_back((new Node()));
		nodes[i]->c = i;
		nodes[i]->frequency = 0;
		nodes[i]->code = " ";
	}
}

void Compression::Compress()
{
     MakeMin_Heap();
     Huff_Tree();
     call_Traverse();
     call_Save();
   //  print_Codes(root, " ");
}

void Compression::call_Traverse()
{
     traverse_Codes(root, " ");
}

//void Compression::init_Node(){
//    // initialising the nodes from 0 to 127 characters
//    for(int i = 0; i < 128; i++)
//    {
//        nodes.push_back(new Node());
//        nodes[i]->c = i;
//        nodes[i]->frequency = 0;
//        nodes[i]->code = " ";
//    }
//
//    // call for min_Heap function
//
//}

void Compression::MakeMin_Heap()
{
    // read from file and update every node's frequency
    // finally, adding these nodes into minimum heap
    // using json for reading from file

    ifstream file;
    file.open(InputFileName, ios::in);

    char ch;
    file>>ch;
   while(!file.eof()){
        nodes[ch]->frequency++;
         file>>ch;
    }

    // pushing these node in minimum heap
    // characters with frequency 0 will not be added to the heap.
    // 0 frequency means that my text file not contain such characters.

     for(int i = 0; i < 128; i++){
        if(nodes[i]->frequency > 0)
        {
             min_Heap.push(nodes[i]);
        }
       
     }

 // every time when i am poping an element, the last index elemnt come to first and then it heapify


// checking:
    // Node* x = min_Heap.top();
    // cout<<x->c<<" "<<x->frequency<<endl;
    // min_Heap.pop();
    // Node* y = min_Heap.top();
    // cout<<y->c<<" "<<y->frequency<<endl;
    // min_Heap.pop();
    // Node* z = min_Heap.top();
    // cout<<z->c<<" "<<z->frequency<<endl;
    // min_Heap.pop();
    // Node* n = min_Heap.top();
    // cout<<n->c<<" "<<n->frequency<<endl;
  
}

void Compression::Huff_Tree()
{
    // make a copy of already existed min_heap 
    Node* x1;
    Node* x2;
     priority_queue<Node*, vector<Node*>, NodeComparator> temp_Min_Heap(min_Heap);
    
    while(temp_Min_Heap.size() != 1)
    {
         x1 = temp_Min_Heap.top(); // small node
        temp_Min_Heap.pop();
         x2 = temp_Min_Heap.top(); // greater than small node or 2nd node
        temp_Min_Heap.pop();

        root = new Node();
        root->frequency = x1->frequency+x2->frequency;
        root->left = x1;
        root->right = x2;
        temp_Min_Heap.push(root);

    }

}

void Compression::traverse_Codes(Node* root, string str)
{
    // traverse paths leading to each character
    // also, assign left with 0 and right with 1

    if(root->left == NULL && root->right == NULL)
    {
        root->code = str;
    //    cout<<root->c<<" "<<root->frequency<<" "<<root->code<<endl;
        return;
    }

    traverse_Codes(root->left, str + '0');
    traverse_Codes(root->right, str + '1');

}

void Compression::call_Save()
{
    save_File(OutputFileName ,InputFileName);
}

// void Compression::save_File(string Outfile, string Infile)
// {
//     ifstream in;
//     in.open(Infile, ios::in);

//     ofstream out;
//     out.open(Outfile, ios::out | ios::binary);

//     char id;
//     in>>id;
//     while(!in.eof())
//     {
//         string cod  = nodes[id]->code;
//         int x = stoi(cod);
//         out.write(reinterpret_cast<const char*>(&x), sizeof(x));
//         in >> id;
//     }

//     in.close();
//     out.close();
// }

void Compression::save_File(string inF , string outF) {
    //Saving encoded (.huf) file

    ifstream inFile;
    inFile.open(inF, ios::in);

    ofstream outFile;
    outFile.open(outF, ios::out | ios::binary);
    string in = "";
    string s = "";
    char id;

    //Saving the meta data (huffman tree)
    in += (char)min_Heap.size();
    priority_queue <Node*, vector<Node*>, NodeComparator> tempPQ(min_Heap);
    while (!tempPQ.empty()) {
        Node* curr = tempPQ.top();
        in += curr->c;
        //Saving 16 decimal values representing code of curr->data
        s.assign(127 - curr->code.length(), '0');
        s += '1';
        s += curr->code;
        //Saving decimal values of every 8-bit binary code 
        in += (char)binToDec(s.substr(0, 8));
        for (int i = 0; i < 15; i++) {
            s = s.substr(8);
            in += (char)binToDec(s.substr(0, 8));
        }
        tempPQ.pop();
    }
    s.clear();

    //Saving codes of every charachter appearing in the input file
    inFile.get(id);
    while (!inFile.eof()) {
        s += nodes[id]->code;
        //Saving decimal values of every 8-bit binary code
        while (s.length() > 8) {
            in += (char)binToDec(s.substr(0, 8));
            s = s.substr(8);
        }
        inFile.get(id);
    }

    //Finally if bits remaining are less than 8, append 0's
    int count = 8 - s.length();
	if (s.length() < 8) {
		s.append(count, '0');
	}
	in += (char)binToDec(s);	
    //append count of appended 0's
    in += (char)count;

    //write the in string to the output file
	outFile.write(in.c_str(), in.size());
	inFile.close();
	outFile.close();
}

int Compression::binToDec(string inStr) {
    int res = 0;
    for (auto c : inStr) {
        res = res * 2 + c - '0';
    }
    return res;
}
