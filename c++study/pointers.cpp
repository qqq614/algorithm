#include <iostream>

using namespace std;

static const int M=45, N=30;

//1 pass by reference
void pass_by_ref(int (&board)[M][N]){
    cout<<endl;
    for (size_t i = 0; i < M; ++i)
    {
        cout << i << ": ";
        for (size_t j = 0; j < N; ++j)
            cout << board[i][j] << '\t';
        cout << endl;
    }
}
//2 pass by pointer
void pass_by_ptr(int (*board)[M][N]){
    cout<<endl;
    for (size_t i = 0; i < M; ++i)
    {
        cout << i << ": ";
        for (size_t j = 0; j < N; ++j)
            cout << (*board)[i][j] << '\t';
        cout << endl;
    }
}

//3 pass by decayed pointer(array to pointer decay)// same as int board[][30]
void pass_by_decayed_ptr(int (*board)[30]){
    cout<<endl;
    for (size_t i = 0; i < M; ++i)
    {
        cout << i << ": ";
        for (size_t j = 0; j < N; ++j)
            cout << board[i][j] << '\t';
        cout << endl;
    }
}

//4. pass by pointer to pointer (same as int *board[30])
void pass_by_double_ptr(int **board){
    cout<<endl;
    for (size_t i = 0; i < M; ++i)
    {
        cout << i << ": ";
        for (size_t j = 0; j < N; ++j)
            cout << board[i][j] << '\t';
        cout << endl;
    }
}


int main()
{
    int board_2d_arr[M][N];
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            board_2d_arr[i][j]=5*i+5*j;
        }
    }
    int *board_array_of_ptr[M];
    for(int i=0;i<M;i++){
        board_array_of_ptr[i]=new int[N];
    }
    
    pass_by_ref(board_2d_arr);

    pass_by_ptr(&board_2d_arr);

    pass_by_decayed_ptr(board_2d_arr);

    pass_by_double_ptr(board_array_of_ptr);
    
    return 0;

}
