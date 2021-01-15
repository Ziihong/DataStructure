/*Name: 김지홍
Student ID: 20191572
Program ID: Hw1_SparseMatrix
Description: m*n행렬에서 원소의 대부분이 0인 행렬을 Sparse Matrix를 읽어,Sparse Matrix에서 값이 0이 아닌 원소들만 모아 'Compressed Sparse Matrix'을 만든다.
            저장공간을 줄일 수 있고 행렬을 전치하는데에 용이하다.
Algorithm:  file I/O를 통해 파일 입력 받기=>
            입력 받은 데이터로 Sparse Matrix 만들기=>
            Sparse Matrix 전치=>
            원소가 0이 아닌 Compressed Sparse Matrix 만들기=>
            Compressed Sparse Matrix 전치=>
            개선된 방안을 이용하여 Compressed Sparse Matrix 전치 
Variables:  main()=>originalMatrix 구현, 출력
            transpose()=>전치된 originalMatrix 구현, 출력
            class Matrix=> 자료형이 Matrix인 Compressed Sparse Matrix 배열에서 클래스 변수 사용
            class CompressedMatrix=>원소의 값이 0이 아닌 원소들만 저장
            CompressedMatrix.traspose()=>전치된 Compressed Sparse Matrix 구현, 출력
            CompressedMatrix.fast_transpose()=>개선된 방안으로 전치된 Compressed Sparse Matrix 구현, 출력
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
using namespace std;
/* transpose()  목적: 원래의 행렬을 전치하는 함수
                변수: original_transMatrix=>원래의 행렬을 전치한 행렬을 담을 배열*/
void transpose(int (*originalMatrix)[6], int r, int c){

    int origin_transMatrix[6][6];
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            origin_transMatrix[i][j] = originalMatrix[j][i];
            cout << origin_transMatrix[i][j] << " ";
        }
        cout << endl;
    }
}
/*class Matrix  목적: 클래스 변수인 row, col, value를 사용. 배열로 저장하는 것보다 용이*/
class Matrix{
    public:
        int row, col, value;
};
/*class CompressedMatrix    목적: 원소가 0이 아닌 값만 저장한 Compressed Sparse Matrix와 관련된 함수들을 포함
                            변수: matirx[]=>Matrix형태의 배열 선언

CompressedMatrix(생성자 함수)   목적: Compressed Sparse Matrix 만들고 (row, col, value)의 튜플형태로 배열

CompressedMatrix.transpose()    목적: Compressed SparseMatrix 전치
                                변수: matrix2[]=> 전치된 Compressed Sparse Matrix 저장 

CompressedMatrix.fast_transpose()   목적: 개선된 방안으로 Compressed Sparse Matrix 전치
                                    변수: matrix3[]=> 전치된 Compressed Sparse Matrix 저장
*/

class CompressedMatrix{
    public: 
        Matrix matrix[9];

    CompressedMatrix(int (*originalMatrix)[6], int r, int c){
    int index = 0;
    matrix[index].row=6; //전체 row크기
    matrix[index].col=6; //전체 col크기
    matrix[index].value=8;//0이 아닌 원소 개수
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if((originalMatrix[i][j])!=0){
                tuple <int, int, int> t(i, j, originalMatrix[i][j]); //튜플 형태로 저장
                cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
                index++;
                matrix[index].row=i;
                matrix[index].col=j;
                matrix[index].value=originalMatrix[i][j];
            }
        }
    }

    }
    void transpose(){
    Matrix matrix2[9];
    matrix2[0].row=matrix[0].col;
    matrix2[0].col=matrix[0].row;
    matrix2[0].value=matrix[0].value;
    if(matrix[0].value>0){ //0이 아닌 행렬
        int current=1;
        for(int i=0; i<matrix[0].col; i++){
            for(int j=1; j<=matrix[0].value; j++){
                if(matrix[j].col==i){ //현재의 열로부터 원소를 찾음
                    matrix2[current].row=matrix[j].col;
                    matrix2[current].col=matrix[j].row;
                    matrix2[current].value=matrix[j].value;
                    cout << matrix2[current].row << " " << matrix2[current].col << " " << matrix2[current].value << endl;
                    current++;
                }
            }
        }
    }
    }
    void fast_transpose(){ 
        Matrix matrix3[9];
        int row_terms[6], starting_pos[6];
        int i, j, num_cols=matrix[0].col, num_terms=matrix[0].value;
        matrix3[0].row = num_cols;
        matrix3[0].col = matrix[0].row;
        matrix3[0].value = num_terms;
        if(num_terms>0){ //0이 아닌 행렬
            for(i=0; i<num_cols; i++){
                row_terms[i]=0;
            }
            for(i=1; i<=num_terms; i++){ //행에 대한 원소 수 결정
                row_terms[matrix[i].col]++;
            }
            starting_pos[0]=1;
            for(i=1; i<num_cols; i++){ //각 행의 시작 위치 구하기
                starting_pos[i]=starting_pos[i-1] + row_terms[i-1];
            }
            for(i=1; i<=num_terms; i++){//전치 행렬의 올바른 위치로 옮기기
                j=starting_pos[matrix[i].col]++;
                matrix3[j].row=matrix[i].col;
                matrix3[j].col=matrix[i].row;
                matrix3[j].value=matrix[i].value;
            }
            for(int i=1; i<=num_terms; i++){
                cout << matrix3[i].row << " " << matrix3[i].col << " " << matrix3[i].value << endl;
            }
        }
        
    }
};
/*main()    목적: 파일을 읽어 들여 Sparse Matrix인 originalMatrix 저장, 각각의 조건에 맞는 행렬 출력을 위해 함수 호출
            변수: file=>file I/O를 위한 선언
                  line=>파일을 한 줄 씩 읽어서 저장할 변수
                  originalMatrix=>파일에서 읽어온 Sparse Matrix
                  ss=>한줄 씩 읽어들인 line에서 필요한 정보를 빼내기 위해 stringstream 선언
                  a=>한줄씩 읽어들인 line에서 정수형태의 정보를 뽑아 a에 저장
 */

int main(){
    ifstream file;
    string line;
    file.open("C_C++_PROJECTS\\data_hw\\hw1.txt");
    if(file.is_open()!=true){
        cout << "Error!" << endl;
    }
    cout << "Original Matrix A:" << endl;
    int originalMatrix[6][6]; 
    for(int i=0; i<6; i++){
        getline(file, line);//한 줄 읽어오기
        stringstream ss(line);
        int j=0;
        int a;
        while(ss >> a){//ss를 이용하여 line에서, a와 매칭하는 필요한 값 저장
            originalMatrix[i][j]=a;
            cout << a << " ";
            j++;
        }
        cout << endl;
    }
    cout << endl;
    cout << "Transpose of Original matrix:" << endl;
    transpose(originalMatrix, 6, 6);
    cout << endl;
    cout << "Sparse Matrix of A-row major:" << endl;
    CompressedMatrix CRM = CompressedMatrix(originalMatrix, 6, 6);
    cout << endl;
    cout << "Transpose of Sparse matrix A - column major:" << endl;
    CRM.transpose();
    cout << endl;
    cout << "Fast transpose of Sparse matrix A:" << endl;
    CRM.fast_transpose();
    
    return 0;
}