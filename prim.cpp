#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
ifstream ifile; //("sample.txt")
ofstream ofile("output_p.txt");
int findMinCost(vector<int>& cost, vector<int>& vis, int n);
int main(){
    string filename;
    cin >> filename;
    ifile.open(filename);

    int e;//number of edges
    ifile >> e;
    int v = e+1;//the max possible number of vertices;
    int cnt_v[v] = {0};//for counting the number of the vertices
    vector<vector<pair<int, int>>> list(v);//the adjacency list to store the edge weight
    char v1, v2;
    int n1, n2;
    int weight;
    for(int i=0; i<e; i++){
        ifile >> v1 >> v2 >> weight;
        n1 = v1 - 97;//transfer aplabet to int(or number index) by -97;
        n2 = v2 - 97;
        cnt_v[n1] = 1;
        cnt_v[n2] = 1;
        list[n1].push_back(make_pair(n2, weight));//fill in the adjacency list
        list[n2].push_back(make_pair(n1, weight));
    }
    //count the number of the vertices
    int num = 0;//counter
    for(int i=0; i<v; i++){
        if(cnt_v[i]==1) num++;
    }//the number of vertices : num

    /*print to see if the list is correct:
    char alph, a;
    for(int i=0; i<num; i++){
        alph = i+97;
        cout << alph << ":";
        for(int j=0; j<list[i].size(); j++){
            a = list[i][j].first + 97;
            cout << "(" << a << "," << list[i][j].second << ")";
        }
        cout << endl;
    }
    */
    vector<int> vis(num, 0);//include in the MST : vis[v]=1, else =0;
    vector<int> cost(num, INT_MAX);//to find the smallest cost each time
    vector<int> parent(num);//store the parent of the vertex

    char s;
    ifile >> s;
    int start = s-97;//the starting vertex
    parent[start] = -1;//set the parent of the starting vertex to -1
    cost[start] = 0;//set the cost of the startong vertex to 0,so that it will be chosen first, since it is the smallest

    //find those num-1 edges to form a MST 
    int check;
    while(1){
        //first find the vertex with the smallest cost(call the findMinCost function), and mark it as visited
        //m is now the vertex which has the smallest cost
        int m = findMinCost(cost,vis,num);
        vis[m] = 1;

        //check if all the verices have been proccessed
        check = 0;
        for(int i=0; i<num; i++){
            if(vis[i]==0) check = 1;
        }
        if(check==0) break;//all preoccessed , break

        //check the neighbors(who are not yet visited) of m
        //update the cost and parent if needed
        int neigh = list[m].size();//the numbers of m's neighbor
        for(int j=0; j<neigh; j++){
            if(vis[list[m][j].first]==0 && (list[m][j].second < cost[list[m][j].first])){
                cost[list[m][j].first] = list[m][j].second;
                parent[list[m][j].first] = m;
            }
        }

    }

    //create a vector to store the value(=cost) and one of the end point of the edge
    vector<pair<int,int>> sort_value;
    char c1, c2;
    int m, value;
    for(int i=0; i<num; i++){
        if(i==start) value = INT_MAX;
        else{
            m = list[parent[i]].size();
            for(int j=0; j<m; j++){
                if(list[parent[i]][j].first==i){
                    value = list[parent[i]][j].second;//find the value of the vertex and its parent
                }
            }
        }
        sort_value.emplace_back(make_pair(value,i));
    }
    //sort by the value(or cost) of edges
    sort(sort_value.begin(),sort_value.end());
    int front, back;
    char v_f, v_b;
    for(int i=0; i<num-1; i++){
        front = sort_value[i].second < parent[sort_value[i].second] ? sort_value[i].second : parent[sort_value[i].second];
        back = sort_value[i].second > parent[sort_value[i].second] ? sort_value[i].second : parent[sort_value[i].second];
        v_f = front + 97;//change int back to char(alphabets)
        v_b = back + 97;
        cout << v_f << " " << v_b << " " << sort_value[i].first << endl;
        ofile << v_f << " " << v_b << " " << sort_value[i].first << endl;
    }

    return 0;
}

int findMinCost(vector<int>& cost, vector<int>& vis, int n){
    int min = INT_MAX;
    int vertex;
    for(int i=0; i<n; i++){
        if(vis[i]==0 && cost[i]<min){
            vertex = i;
            min = cost[i];
        }
    }
    return vertex;
}