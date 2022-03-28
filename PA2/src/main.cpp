#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

//void FindMps(int* data, int& N, int** M) {
//    int record = 0;
//    int j = 0, k = 0;
//
//    for(int l=1;l<N;l++){
//        for(int i=0;i<N-l;i++){
//            j = i + l;
//            k = data[j];
//            if(k<i || k>j) M[i][j] = M[i][j-1];
//            else if(k==i) M[i][j] = M[i+1][j-1] + 1;
//            else{
//                if(M[i][j-1] > M[i][k-1] + 1 + M[k+1][j-1]){
//                    M[i][j] = M[i][j-1];
//                }
//                else M[i][j] = M[i][k-1] + 1 + M[k+1][j-1];
//            }
//        }
//    }
//
//    N = M[0][N-1];
// }
int FindMps(int* data, int i, int j, int** M) {
    if(M[i][j]!=0) return M[i][j];
    if(i>=j) return 0;
    int k = data[j];
    if(k<i || k>j){
        M[i][j] = FindMps(data, i, j-1, M);
        return M[i][j];
    }
    else if(k == i){
        M[i][j] = FindMps(data, i+1, j-1, M) + 1;
        return M[i][j];
    }
    else{
        if(FindMps(data, i, j-1, M) > FindMps(data, i, k-1, M) + 1 + FindMps(data, k+1, j-1, M)){
            M[i][j] = FindMps(data, i, j-1, M);
            return M[i][j];
        }
        else{
            M[i][j] = FindMps(data, i, k-1, M) + 1 + FindMps(data, k+1, j-1, M);
            return M[i][j];
        }
    }
}
void find_chord(int** M, int* data, int i, int j, int* rec) {
    if(i>j) return;

    if(data[j]>j || data[j]<i) find_chord(M, data, i, j-1, rec);
    else if(data[j]==i){
        rec[i] = j;
        rec[j] = i;
        find_chord(M, data, i+1, j-1, rec);
    }
    else if(FindMps(data, i, j, M)==FindMps(data, i, data[j]-1, M) + 1 + FindMps(data, data[j]+1, j-1, M)){
        rec[data[j]] = j;
        rec[j] = data[j];
        find_chord(M, data, i, data[j]-1, rec);
        find_chord(M, data, data[j]+1, j-1, rec);
    }
    else find_chord(M, data, i, j-1, rec);
}

int main(int argc, char* argv[])
{
    if(argc!=3){
        cout<<"please check again!";
        return 0;
    }

    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    int N = 0;
    fin >> N;
//    int record_N = N;
    int* data;
    data = new int[N];
    int* rec;
    rec = new int[N];
    for(int i=0;i<N;i++){
        data[i] = -1;
        rec[i] = -1;
    }

    int start_i, end_j = 0;
    while(fin >> start_i >> end_j){
        data[start_i] = end_j;
        data[end_j] = start_i;
    }

    int** M;
    M = new int* [N];
    for (int i=0; i<N; i++){
        M[i] = new int[N];
    }

    int num = FindMps(data, 0, N-1, M);
    fout<<num<<endl;
    find_chord(M, data, 0, N-1, rec);

    for(int i=0;i<N;i++){
        if(rec[i]!=-1){
            fout<<i<<" "<<rec[i]<<endl;
            rec[rec[i]] = -1;
        }
    }
    delete [] data;
    delete [] rec;
    for (int i=0;i<N;i++){
        delete [] M[i];
    }
    delete [] M;
    fin.close();
    fout.close();
    return 0;
}
