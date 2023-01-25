#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>//for sorting
using namespace std;
ifstream ifile; //("sample.txt")
ofstream ofile("output_d.txt");
int findMinCost(vector<int>& cost, vector<int>& vis, int n);
int main(){
    string filename;
    cin >> filename;
    ifile.open(filename);

    int e;//number of edges
    ifile >> e;
    int v = e+1;//the max possible number of vertices;
    int cnt_v[v] = {0};//for counting the number of vertices
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
        list[n1].push_back(make_pair(n2, weight));
    }
    //count the number of the vertices
    int num = 0;//counter
    for(int i=0; i<v; i++){
        if(cnt_v[i]==1) num++;
    }//the number of the vertices : num


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

    vector<int> cost(num,INT_MAX);//initialize all the cost to inf
    vector<int> vis(num, 0);//check if the vertex has been proccessed, =1 means proccessed

    char s;
    ifile >> s;
    int start = s-97;
    cost[start] = 0;//set the cost of the starting vertex to 0 (current smallest)
    int check;
    while(1){
        //check if all verices have been proccesed
        check = 0;
        for(int i=0; i<num; i++){
            if(vis[i]==0) check = 1;
        }
        if(check==0) break;//all preoccessed , break

        //call the findMinCost function to find the vertex with the smallest cost
        //m is vertex that we are going to proccess right now
        int m = findMinCost(cost, vis, num);
        vis[m] = 1;
        //visit all the neighbor of m
        //if the conditions are satisfied, update the cost of m's neighbor
        int len = list[m].size();
        for(int i=0; i<len; i++){
            if(vis[list[m][i].first]==0 && (cost[list[m][i].first] > (cost[m]+list[m][i].second))){
                cost[list[m][i].first] = cost[m]+list[m][i].second;
            }
        }
    }

    //make pair all the vertex and it cost, in order to sort later
    vector<pair<int,char>> pair;
    char c;
    for(int i=0; i<num; i++){
        if(cost[i]!=INT_MAX){
            c = i+97;
            pair.emplace_back(make_pair(cost[i],c));
        }
    }
    sort(pair.begin(),pair.end());//sort the vector according to the cost

    //print the result
    int l = pair.size();
    for(int i=0; i<l; i++){
        cout << pair[i].second << " " << pair[i].first << endl;
        ofile << pair[i].second << " " << pair[i].first << endl;
    }

    return 0;
}

int findMinCost(vector<int>& cost, vector<int>& vis, int n){
    int min = INT_MAX;
    int vertex;
    for(int i=0; i<n; i++){//make sure if there are one ore more vertices that can't be reached
        if(vis[i]==0 && cost[i]==min){
            min = cost[i];
            vertex = i;
        }
    }
    for(int i=0; i<n; i++){
        if(vis[i]==0 && cost[i]<min){
            min = cost[i];
            vertex = i;
        }
    }
    return vertex;
}