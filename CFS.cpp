#include <iostream>
#include "RBTree.h"
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class CFS_Sched{
    public:
    void Insert(int key, std::string label, int timeToLive){
        RBTree_.Insert(key, label, timeToLive);
    }

    void IncrAndProcessRuntime(){
        RBTreeNode *root = RBTree_.GetRoot();
        root->key += 1;
        
        if (root->key == root->timeToLive){
            finishedProcesses.push_back(root->metaData);
            RBTree_.Delete(root);
        }
    }

    int Min(){
        return RBTree_.Minimum(RBTree_.GetRoot())->key; 
    }

    private:
    RBTree RBTree_;
    vector<string> finishedProcesses;
};

int main(int argc, char* argv[]){
    // string filename = argv[1];
	string filename = "./input_1.txt";
    string outname = regex_replace(filename, std::regex("input"), "output");

    ofstream ofile;
    ifstream file;
    ofile.open(outname, ios::trunc); // open a filestream given argv input_*.txt -> output_*.txt
    file.open(filename, ios::in);
    string temp;

    getline(file, temp);
    return 0;
}