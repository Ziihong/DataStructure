/*
Name: 김지홍
Student ID: 20191572
Program ID: Hw3_Miro
Description: 2차원 형태로 만들어진 미로에서 출발점에서 도착점까지의 경로를 탐색한다. 현재의 위치를 저장하기 위해 stack을 이용한다.
Algorithm: 8방향의 좌표값을 초기화한다.
           다음 지점의 좌표는 현재 지점의 좌표에서 갈 수 있는 방향의 좌표값을 더한 값이다.
           만약 다음 지점이 막혀있는 지점이거나 이미 지나온 지점의 경우, 다음 방향을 탐색한다. 이때 방향은 북쪽 방향부터 시계방향으로 8방향이다.
           도착점을 향해 지나가는 지점이면, 이 위치의 좌표를 stack에 저장한다.
           도착점에 도달하기 전까지 이와 같은 탐색을 반복한다.
Variables: struct element=>row, col, dir을 원소로 가지며, 현재의 위치와 방향을 저장하기 위해 사용.
           struct offsets=>vert, horiz을 원소로 가지며, 8방향의 좌표값을 저장하기 위해 사용.
           move[]=> 방향별 좌표가 저장된 배열.
           maze[][]=>2차원 배열 형태로 주어진 미로. 값이 1인 경우에는 가로 막혀 지나지 못하는 지점, 0인 경우에는 지날 수 있는 지점.
           mark[][]=>maze와 같은 2차원 배열 형태로서 지나온 지점의 위치들을 저장한다. 1인 경우에는 이미 지나온 지점, 0인 경우에는 지나지 않은 지점.
           found=>boolean형태로서 1인 경우에는 도착점에 도달, 0인 경우에는 도착점에 도달하지 못함.
           position=>위치의 초기값.
           row, col, dir=>현재의 위치 좌표값과 방향.
           next_row, next_col=>다음 위치 좌표값.
*/
#include <iostream>
#include <stack>
using namespace std;
/*element
Description: 현재의 위치와 방향을 배열에 한 번에 저장하기 위해 사용*/
struct element{
    int row, col, dir;
};
/*offsets
Description: 8방향별로 이동하는 수직, 수평 좌표값을 배열에 한 번에 저장하기 위해 사용*/
struct offsets{
    int vert, horiz;
};

int main(){
    offsets move[8];
    move[0].vert=-1; move[0].horiz=0; //N
    move[1].vert=-1; move[1].horiz=1; //NE
    move[2].vert=0; move[2].horiz=1; //E
    move[3].vert=1; move[3].horiz=1; //SE
    move[4].vert=1; move[4].horiz=0; //S
    move[5].vert=1; move[5].horiz=-1; //SW
    move[6].vert=0; move[6].horiz=-1; //W
    move[7].vert=-1; move[7].horiz=-1; //NW
    int maze[6][6]={0,1,1,1,1,1, 1,0,1,1,1,1, 1,0,0,0,0,1, 1,1,0,1,1,1, 1,0,1,0,0,1, 1,1,1,1,1,0};
    int mark[6][6]={1}; //시작점 0,0은 1로, 나머지는 0으로 초기화
    bool found=0;
    element position; position.col=0; position.row=0; position.dir=0; //초기 위치 초기화
    stack<element> s; s.push(position); //stack에 저장
    while(!s.empty() && !found){
        element temp = s.top(); s.pop();//stack에 저장된 현재 위치를 받아오고 삭제한다.
        int row, col, dir;
        row=temp.row; col=temp.col; dir=temp.dir;
        while(dir<8 && !found){
            int next_row, next_col;
            next_row=row+move[dir].vert; next_col=col+move[dir].horiz; //다음 지점의 좌표=현재 지점의 좌표+방향의 좌표
            if(next_row==5 && next_col==5){//다음 좌표가 도착점이면
                mark[next_row][next_col]=1;
                found=1;//도착점 도달
            }
            else if(!maze[next_row][next_col] && !mark[next_row][next_col]){//미로가 막혀있지 않고 지나온 길이 아니면
                mark[next_row][next_col]=1;
                temp.row=next_row; temp.col=next_col; temp.dir=++dir; //현재의 위치를 stack에 저장
                s.push(temp);
                row=next_row; col=next_col; dir=0;
            }
            else{
                dir++;//다음 방향 탐색
            }
        }

    }
    cout << "The Path is\nrow col" << endl;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            if(mark[i][j]==1){
                cout << i << " " << j << endl;
            }
        }
    }
    cout << "\nMarked Matrix" << endl;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            cout << mark[i][j];
        }
        cout << endl;
    }
    return 0;
}