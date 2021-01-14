#include <iostream>
#include <list>
#include <vector>
#include <memory>
using namespace std;


class BFS{


  private:

    vector<int> *graph_;
    vector<string> words_;
    vector<bool> visited;
    vector<int> rpath;
    vector<string> path;
    list<int> queing;
    string srcword_;
    string targetword_;
    int foundat;

  public:
    void getWords();
    void graphEdges();
    bool wordWithOneCharDifferent(const string& word1, const string& word2);
    bool findtargetqord();
    void printGraph();
    void getSearchWords();
    BFS(){};
};

void BFS::getSearchWords(){

    string str;
    cin>>str;

    int pos = str.find(',');
    srcword_ = str.substr(0 , pos);
    targetword_ = str.substr(pos+1);

    return;
}
bool BFS::findtargetqord(){
    do{
        int q = queing.front();
        queing.pop_front();
        for(auto it = graph_[q].begin() ; it != graph_[q].end() ; ++it){
            if(visited.at(*it) == false){
                visited.at(*it) = true;
                queing.push_back(*it);
                rpath.at(*it) = q;
                if(words_.at(*it) == targetword_){
                    foundat = *it;
                    return true;
                }

            }
        }

    }while(!queing.empty());
    return false;
}
void BFS::printGraph(){

   path.push_back(words_.at(foundat));
    while(rpath.at(foundat) != -1){
        path.push_back(words_.at(rpath.at(foundat)));
        foundat = rpath.at(foundat);
    }

    for(auto it = path.rbegin(); it != path.rend(); ++it){
        if(*it != *(path.rend()-1))
            cout<<*it<<" -> ";
        else cout<<*it<<endl;
    }
    return;
}
void BFS::graphEdges(){
    for(auto it = 0u; it != words_.size()-1 ; ++it){
        for(auto itr = it+1; itr != words_.size() ; ++itr){
            if(wordWithOneCharDifferent(words_.at(it) ,words_.at(itr))){
                graph_[itr].push_back(it);
                graph_[it].push_back(itr);
            }
        }
    }
    return;
}

bool BFS::wordWithOneCharDifferent(const string& word1, const string& word2){
    auto charDiff = 0u;
    for(auto it = 0u ; it != word1.length() ; ++it){
        if(word1.at(it) != word2.at(it)) charDiff++;
    }
    if(charDiff==1) return true;
    return false;
}
void BFS::getWords(){
    string word;
    while(cin>>word && word != "-1"){
        words_.push_back(word);
        visited.push_back(false);
        rpath.push_back(-1);
        if(srcword_ == word)
            foundat = words_.size() -1;

    }
    queing.push_back(foundat);
    visited.at(foundat) = true;
    graph_ = new vector<int>[words_.size()];
    return;
}

int main(){

    unique_ptr<BFS> bfs = make_unique<BFS>();
    bfs->getSearchWords();
    bfs->getWords();
    bfs->graphEdges();
    if(bfs->findtargetqord())
        bfs->printGraph();
    return 0;
}
