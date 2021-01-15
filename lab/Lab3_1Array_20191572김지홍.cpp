#include <iostream>
using namespace std;

int main(){
    int square[21][21] = {0, };
    int square2[21][21] = {0, };
    int n;

    cout << "Enter number of square:";
    cin >> n;
    int number=1;
    int i=1;
    int j=(n/2)+1;
    square[i][j] = number;
    number++;

    while(number<=n*n){
        if((number-1)%n==0){
            i++;
            square[i][j] = number;
            number++;
        }
        else {
            if(i-1<1){
                i=n;
                j++;
                square[i][j]=number;
                number++;
            }
            else if(j+1>n){
                i--;
                j=1;
                square[i][j]=number;
                number++;
            }
            else{
                i--;
                j++;
                square[i][j]=number;
                number++;
            }
        }
    }

    cout << "Magic square size is " << n << endl;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout << square[i][j] <<" ";
        }
        cout << endl;
    }
    cout << endl;

    number=1;
    i=1;
    j=(n/2)+1;
    square2[i][j] = number;
    number++;

    while(number<=n*n){
        if((number-1)%n==0){
            i++;
            square2[i][j] = number;
            number++;
        }
        else {
            if(i-1<1){
                i=n;
                j--;
                square2[i][j]=number;
                number++;
            }
            else if(j-1<1){
                i--;
                j=n;
                square2[i][j]=number;
                number++;
            }
            else{
                i--;
                j--;
                square2[i][j]=number;
                number++;
            }
        }
    }
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout << square2[i][j] <<" ";
        }
        cout << endl;
    }
    return 0;
}