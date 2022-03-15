#include <bits/stdc++.h>

using namespace std;

int main()
{
    int sparse_matrix[3][3] =
    {
        {1,0,0},
        {0,4,0},
        {0,0,7}
    };

    map<pair<int,int>,int> new_matrix;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(sparse_matrix[i][j]!=0){
                new_matrix[make_pair(i,j)]=sparse_matrix[i][j];
            }
        }
    }
    for(auto i = new_matrix.begin();i!=new_matrix.end();i++){
        cout<<"("<<i->first.first<<","<<i->first.second<<"): "<<i->second<<endl;
    }
    return 0;
}