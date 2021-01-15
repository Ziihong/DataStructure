#include <iostream>
#define MAX 999
using namespace std;


int **dataArray1;
int **dataArray2;
void testCase1();
void testCase2();
void printGraph(int size, int **arr);
void shortestPath(int vertex, int size, int **arr);

void testCase1(){
    int data1[6][6]={
        {MAX, 20, 15, MAX, MAX, MAX},
        {MAX, MAX, MAX, MAX, 10, 30},
        {MAX, 4, MAX, MAX, MAX, 10},
        {MAX, MAX, MAX, MAX, MAX, MAX},
        {MAX, MAX, MAX, 15, MAX, MAX},
        {MAX, MAX, MAX, 4, 10, MAX}
    };

    int size=6;
    dataArray1=new int *[size];
    for(int i=0; i<size; i++){
        dataArray1[i]=new int [size];
        for(int j=0; j<size; j++){
            dataArray1[i][j]=data1[i][j];
        }
    }
    printGraph(size, dataArray1);
    shortestPath(0, size, dataArray1);
}

void testCase2(){
    int data2[6][6]={
        {MAX, 50, 10, MAX, 45, MAX},
        {MAX, MAX, 15, MAX, 10, MAX},
        {20, MAX, MAX, 15, MAX, MAX},
        {MAX, 20, MAX, MAX, 35, MAX},
        {MAX, MAX, MAX, 30, MAX, MAX},
        {MAX, MAX, MAX, 3, MAX, MAX}
    };

    int size=6;
    dataArray2=new int *[size];
    for(int i=0; i<size; i++){
        dataArray2[i]=new int [size];
        for(int j=0; j<size; j++){
            dataArray2[i][j]=data2[i][j];
        }
    }
    printGraph(size, dataArray2);
    shortestPath(0, size, dataArray2);
}

void printGraph(int size, int **arr){
    cout << "-------Adjacency Matrix-------" << endl;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void shortestPath(int vertex, int size, int **array){
    cout << "----------Shortest Path----------" << endl;
    int distance[size];
    int found[size]={0};

    for(int i=0; i<size; i++){
        distance[i]=array[vertex][i];
    }
    distance[vertex]=0;
    found[vertex]=1;

    //Start distance 출력
    cout << "Start from vertex(" << vertex << "): ";
    for(int i=0; i<size; i++){
        cout << distance[i] << " ";
    }
    cout << endl;

    int count=0;
    while(count < size-1){
        //min cost 찾기
        int idx, min_cost=1000000;
        for(int i=0; i<size; i++){
            if(distance[i] < min_cost && !found[i]){
                min_cost=distance[i];
                idx=i;
            }
        }
        found[idx]=1;

        for(int i=0; i<size; i++){
            if(!found[i]){
                if(distance[idx]+array[idx][i] < distance[i])
                    distance[i]=distance[idx]+array[idx][i];
            }
        }

        //distance 출력
        cout << "Select Node(" << idx << "): ";
        for(int i=0; i<size; i++){
            cout << distance[i] << " ";
        }
        cout << endl;
        count++;
    }
    cout << endl;
}

int main(){
    cout << "Test Case1>>" << endl;
    testCase1();
    cout << endl << "Test Case2>>" << endl;
    testCase2();
    return 0;
}