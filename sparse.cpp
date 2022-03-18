#include <bits/stdc++.h>
#define MAX_SIZE 1000
const int row = 3;
const int column = 3;

using namespace std;

std::map<pair<int, int>, int> sparsify(int dense_matrix[row][column]){
    map<pair<int,int>,int> new_matrix;
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            if(dense_matrix[i][j]!=0){
                new_matrix[make_pair(i,j)]=dense_matrix[i][j];
            }
        }
    }
    return new_matrix;
}
void print_mapped_matrix(std::map<pair<int, int>, int> new_matrix){
    for(auto i = new_matrix.begin();i!=new_matrix.end();i++){
        cout<<"("<<i->first.first<<","<<i->first.second<<"): "<<i->second<<endl;
    }
}

std::map<pair<int, int>, int> add_sparse_matrix(std::map<pair<int, int>, int> new_matrix, std::map<pair<int, int>, int> new_matrix2){
    std::map<pair<int, int>, int> result;
    int apos = 0, bpos = 0, len = new_matrix.size();
    for(auto i = new_matrix.begin(), j = new_matrix2.begin();i!=new_matrix2.end();i++,j++){
        if(i->first.first > j->first.first || i->first.first == j->first.first && i->first.second > j->first.second){
            result[make_pair(j->first.first,j->first.second)]=j->second;
            bpos++;
        }
        else if(i->first.first < j->first.first || i->first.first == j->first.first && i->first.second < j->first.second){
            result[make_pair(i->first.first,i->first.second)]=i->second;
            apos++;
        }
        else{
            int val = i->second + j->second;
            if(val!=0){
                result[make_pair(i->first.first,i->first.second)]= val;
            }
            apos++;
            bpos++;
        }
        while(apos<len){
        apos++;
        result[make_pair(i->first.first,i->first.second)]=i->second;
        }
        while(bpos<len){
            bpos++;
            result[make_pair(j->first.first,j->first.second)]=j->second;
        }
    }
    
    return result;
}

int main()
{
    int dense_matrix[3][3] =
    {
    {1,0,0},
    {0,4,0},
    {0,0,6}
    };
    int dense_matrix2[3][3] =
    {
    {1,0,0},
    {0,4,0},
    {0,0,6}
    };
    map<pair<int,int>,int> new_matrix = sparsify(dense_matrix);
    print_mapped_matrix(new_matrix);
    
    map<pair<int,int>,int> new_matrix2 = sparsify(dense_matrix2);
    print_mapped_matrix(new_matrix2);
    map<pair<int,int>,int> result = add_sparse_matrix(new_matrix,new_matrix2);
    //print_mapped_matrix(result);
    
    //cout<<sizeof(new_matrix)<<endl;
    //cout<<sizeof(sparse_matrix);
    return 0;
}