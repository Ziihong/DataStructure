#include <iostream>
using namespace std;

class MST{
private:
    int size;
    int *visited;
    int **weighted;
public:
    MST(int size);
    void buildMST(int v1, int v2, int w);
    int prim(int v);
    void printGraph();
    int leastCost(int v);
};

MST::MST(int size){
    this->size=size;
    visited=new int [size];
    weighted=new int *[size];
    for(int i=0; i<size; i++){
        weighted[i]=new int [size];
    }
    //배열 초기화
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            weighted[i][j]=100;
        }
    }
}
void MST::buildMST(int v1, int v2, int w){//undirected
    weighted[v1][v2]=w;
    weighted[v2][v1]=w;
}
int MST::leastCost(int v){
    int min=weighted[v][v+1];
    int idx=v+1;
    for(int i=v+1; i<size; i++){
        if(weighted[v][i] < min){
            min=weighted[v][i];
            idx=i;
        }
    }
    return idx;
}
int MST::prim(int v){
    int n=0;
    int idx=v+1;
    int vertex=v;
    int weight=0;
    while(n < size-1 && visited[vertex]!=1){
        visited[vertex]=1;
        cout << "v"<< vertex+1 << ",";
        int min=weighted[vertex][idx];
        for(int i=0; i<size; i++){
            if(visited[i]!=1){
                if(weighted[vertex][i]<min){
                    min=weighted[vertex][i];
                    idx=i;
                    weight+=weighted[vertex][i];
                }
            }
        }
        vertex=idx;
        cout << "v" <<vertex+1 << endl;
        n++;
    }
    return weight;
}
void MST::printGraph(){
    int n=1;
    cout << "  ";
    for(int i=0; i<size; i++){
        cout << " v" << n;
        n++;
    }
    cout << endl;
    n=1;
    for(int i=0; i<size; i++){
        cout << "v" << n << " ";
        for(int j=0; j<size; j++){
            cout << weighted[i][j] << " ";
        }
        n++;
        cout << endl;
    }
}

int main(){
    MST m(6);
    int inputArray[6][6]={{100, 6, 1, 5, 100, 100},
                          {6, 100, 4, 100, 3, 100},
                          {1, 4, 100, 5, 6, 5},
                          {5, 100, 5, 100, 100, 2},
                          {100, 3, 6, 100, 100, 6},
                          {100, 100, 5, 2, 6, 100}};
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            m.buildMST(i, j, inputArray[i][j]);
        }
    }
    cout << "------Print Graph------" << endl;
    m.printGraph();

    cout << "\n------Minimal Spanning Tree------" << endl;
    cout << "Total Weight: " << m.prim(0) << endl;
    

    return 0;
}