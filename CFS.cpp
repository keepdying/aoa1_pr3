#include <iostream>
#include "RBTree.h"
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
using namespace std;

struct Process{
    string Metadata;
    int TimeOfArrival;
    int FinishedTime;
    int BurstTime;
};
class CFS_Sched{
    public:
    void Insert(int key, string label, int BurstTime){
        RBTree_.Insert(key, label, BurstTime);
    }

    void IncrAndProcessRuntime(){
        RBTreeNode *min = RBTree_.Minimum(RBTree_.GetRoot());

        if (min == nullptr){
            return;
        }
        
        if (min->parent != nullptr){
            if (min->key + 1 == min->parent->key){
                min->key += 1;
                return;
            }
        }

        RBTree_.Delete(min);
        min->key += 1;
        
        if (min->key == min->BurstTime){
            Process Process_;
            Process_.Metadata = min->Metadata;
            Process_.FinishedTime = this->currRuntime;
            FinishedProcesses.push_back(Process_);
            delete min;
        } else {
            RBTree_.Insert(min->key, min->Metadata, min->BurstTime);
            delete min;
        }

    }
    
    int Min(){
        return RBTree_.Minimum(RBTree_.GetRoot())->key; 
    }

    string RunningTask(){
        return RBTree_.Minimum(RBTree_.GetRoot())->Metadata;
    }

    int TaskVruntime(){
        return RBTree_.Minimum(RBTree_.GetRoot())->key;
    }

    string TaskStatus(){
        if (RBTree_.Minimum(RBTree_.GetRoot())->key + 1 == RBTree_.Minimum(RBTree_.GetRoot())->BurstTime){
            return "Complete";
        } else {
            return "Incomplete";
        }
    }

    void PrintInOrder(ostream &os){
        RBTree_.PrintInOrder(os, RBTree_.GetRoot());
    }

    void Start(ostream &os, vector<Process> &ProcessList){
        chrono::time_point<chrono::high_resolution_clock> start, end; // define start and end times.
	    start = chrono::high_resolution_clock::now();
        int process_count = ProcessList.size();

        for (int& i = this->currRuntime; i < this->maxRuntime; i++){
            for (int j = 0; j < ProcessList.size(); j++){
                if (ProcessList[j].TimeOfArrival == i ){
                    this->Insert(0, ProcessList[j].Metadata, ProcessList[j].BurstTime);
                    ProcessList.erase(ProcessList.begin() + j);
                    j--;
                }
            }
            os << i << ",";
            if (RBTree_.GetRoot() == nullptr){
                os << "-,-,-,-,-" << "\n";
            } else {
                os << this->RunningTask() << "," << this->TaskVruntime() << "," << this->Min() << ",";
                this->PrintInOrder(os);
                os << this->TaskStatus() << "\n";
                this->IncrAndProcessRuntime();
            }
        }

        end = chrono::high_resolution_clock::now();
	    chrono::duration<double> elapsed_seconds = end - start;
        os << "Scheduling finished in " << elapsed_seconds.count() * 1000 << "ms." << "\n";
        os << this->FinishedProcesses.size() << " of " << process_count << " processes are completed." << "\n";
        os << "The order of completion of the tasks: ";
        for (int k = 0; k < this->FinishedProcesses.size(); k++){
            os << this->FinishedProcesses[k].Metadata << (k + 1 == this->FinishedProcesses.size() ? "\n" : "-");
        }
    }

    int maxRuntime;
    int currRuntime = 0;
    private:
    RBTree RBTree_;
    vector<Process> FinishedProcesses;
};

int main(int argc, char* argv[]){
    string filename = argv[1];
	// string filename = "./input_2.txt";
    string outname = regex_replace(filename, regex("input"), "output");
    
    CFS_Sched CFS_Sched_;
    vector<Process> ProcessList;
    ofstream ofile;
    ifstream file;
    ofile.open(outname, ios::trunc); // open a filestream given argv input_*.txt -> output_*.txt
    file.open(filename, ios::in);
    string temp;

    getline(file, temp);
    stringstream s(temp);

    getline(s, temp, ' ');
    int process_count = stoi(temp);
    getline(s, temp);
    CFS_Sched_.maxRuntime = stoi(temp);

    for (int i = 0; i < process_count; i++){
        getline(file, temp);
        stringstream s(temp);

        Process Process_;
        getline(s, temp, ' ');
        Process_.Metadata = temp;
        getline(s, temp, ' ');
        Process_.TimeOfArrival = stoi(temp);
        getline(s, temp);
        Process_.BurstTime = stoi(temp);
        ProcessList.push_back(Process_);
    }
    file.close();
    
    CFS_Sched_.Start(ofile, ProcessList);
    ofile.close();

    return 0;
}