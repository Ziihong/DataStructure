#include <iostream>
#include <queue>
using namespace std;


int main(){
    int adj_Matrix1[8][8]={{0,1,1,0,0,0,0,0}, {1,0,0,1,1,0,0,0}, {1,0,0,0,0,1,1,0}, {0,1,0,0,0,0,0,1}, {0,1,0,0,0,0,0,1}, {0,0,1,0,0,0,0,1}, {0,0,1,0,0,0,0,1},{0,0,0,1,1,1,1,0}};
    int adj_Matrix2[6][6]={{0,1,1,0,0,0}, {1,0,1,1,0,0}, {1,1,0,0,0,1}, {0,1,0,0,1,1}, {0,0,0,1,0,1}, {0,0,1,1,1,0}};
    int visited1[8]={0};
    int visited2[6]={0};
    cout << "------Data1 Matrix------" << endl;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            cout << adj_Matrix1[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Data1 BFS: ";
    queue <int> q; int v;
    v=0;
    q.push(v);
    visited1[v]=1;
    while(!q.empty()){
        v=q.front(); q.pop();
        cout << v << " ";
        for(int i=0; i<8; i++){
            if(!visited1[i] && adj_Matrix1[v][i]){
                q.push(i);
                visited1[i]=1;
            }
        }
    }
    cout << endl;
    cout << "------Data2 Matrix------" << endl;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            cout << adj_Matrix2[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Data2 BFS: ";
    v=0;
    q.push(v);
    visited2[v]=1;
    while(!q.empty()){
        v=q.front(); q.pop();
        cout << v << " ";
        for(int i=0; i<8; i++){
            if(!visited2[i] && adj_Matrix2[v][i]){
                q.push(i);
                visited2[i]=1;
            }
        }
    }



    return 0;
}