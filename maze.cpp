#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <ios>
using namespace std;

ifstream ifile;
ofstream ofile("output.txt");

int main(){
    cout << "enter filename : ";
    string filename;
    cin >> filename;
    ifile.open(filename);
    //clear the maze all to zero
    int maze[17][17];
    for(int i=0; i<17; i++){
        for(int j=0; j<17; j++){
            maze[i][j] = 0;
        }
    }
    
    //read in the digits in char form
    //then change them to int by -48
    char digit;
    for(int i=0; i<17; i++){
        for(int j=0; j<17; j++){
            ifile >> digit;
            maze[i][j] = digit - 48;
            cout << maze[i][j] << " ";
        }
        ws(ifile); //clear all the white space
        cout << endl;
    }

    //create a stack using vector
    //each element in stack is a coordinate
    //push the starting coordinate (1,0) into the stack
    vector<pair<int, int>> stack;
    stack.push_back(make_pair(1,0));
    maze[1][0] = 1;//
    int cnt = 0;
    ofile << cnt  << ":" << 1 << "," << 0 << endl;
    //while the stack is not empty
    //check all eight directions of the top of the stack
    //if the direction(element) is marked 0, then push it in the stack
    //and change the mark from 0 to 2
    //if this available element==(15,16), then successed
    while(!stack.empty()){
        int last_index = stack.size()-1;
        pair<int,int> top = stack[last_index];
        //i+1:down  i-1:up  j+1:right  j-1:left
        int down = top.first + 1;
        int up = top.first - 1;
        int left = top.second - 1;
        int right = top.second + 1;

        //check all 8 directions
        if(maze[top.first][right]==0){ //right 1
            cnt++;
            ofile << cnt  << ":" << top.first << "," << right << endl;
            cout << cnt  << ":" << top.first << "," << right << endl;
            stack.push_back(make_pair(top.first, right));
            maze[top.first][right]=2;
            if((top.first==15)&&(right==16)){
                ofile << "successfully escaped!!";
                cout << "successfully escaped!!";
                break;
            }
        }
        else if(maze[down][right]==0){//down right (lower right) 2
            cnt++;
            ofile << cnt  << ":" << down << "," << right << endl;
            cout << cnt  << ":" << down << "," << right << endl;
            stack.push_back(make_pair(down, right));
            maze[down][right]=2;
            if((down==15)&&(right==16)){
                ofile << "successfully escaped!!";
                cout << "successfully escaped!!";
                break;
            }
        }
        else if(maze[down][top.second]==0){//down 3
            cnt++;
            ofile << cnt  << ":" << down << "," << top.second << endl;
            cout << cnt  << ":" << down << "," << top.second << endl;
            stack.push_back(make_pair(down, top.second));
            maze[down][top.second]=2;
            if((down==15)&&(top.second==16)){
                ofile << "successfully escaped!!";
                cout << "successfully escaped!!";
                break;
            }
        }
        else if(maze[down][left]==0){//down left 4
            cnt++;
            ofile << cnt  << ":" << down << "," << left << endl;
            cout << cnt  << ":" << down << "," << left << endl;
            stack.push_back(make_pair(down, left));
            maze[down][left]=2;
            if((down==15)&&(left==16)){
                ofile << "successfully escaped!!";
                cout << "successfully escaped!!";
                break;
            }
        }
        else if(maze[top.first][left]==0){ //left 5
            cnt++;
            ofile << cnt  << ":" << top.first << "," << left << endl;
            cout << cnt  << ":" << top.first << "," << left << endl;
            stack.push_back(make_pair(top.first, left));
            maze[top.first][left]=2;
            if((top.first==15)&&(left==16)){
                ofile << "successfully escaped!!";
                cout << "successfully escaped!!";
                break;
            }
        }
        else if(maze[up][left]==0){ //up left 6
            cnt++;
            ofile << cnt  << ":" << up << "," << left << endl;
            cout << cnt  << ":" << up << "," << left << endl;
            stack.push_back(make_pair(up, left));
            maze[up][left]=2;
            if((up==15)&&(left==16)){
                ofile << "successfully escaped!!";
                cout << "successfully escaped!!";
                break;
            }
        }
        else if(maze[up][top.second]==0){ //up 7
            cnt++;
            ofile << cnt  << ":" << up << "," << top.second << endl;
            cout << cnt  << ":" << up << "," << top.second << endl;
            stack.push_back(make_pair(up, top.second));
            maze[up][top.second]=2;
            if((up==15)&&(top.second==16)){
                ofile << "successfully escaped!!";
                cout << "successfully escaped!!";
                break;
            }
        }
        else if(maze[up][right]==0){ //up right 8
            cnt++;
            ofile << cnt  << ":" << up << "," << right << endl;
            cout << cnt  << ":" << up << "," << right << endl;
            stack.push_back(make_pair(up, right));
            maze[up][right]=2;
            if((up==15)&&(right==16)){
                ofile << "successfully escaped!!";
                cout << "successfully escaped!!";
                break;
            }
        }
        //if there is no any available direction to go
        //then set the current element to 1 and pop it out of the stack
        //print the top element of the stack
        //if the top element==(1,0), then failed
        //otherwise continue the loop
        else{//go backward
            maze[top.first][top.second] = 1;
            stack.pop_back();
            cnt++;
            ofile << cnt  << ":" << stack[stack.size()-1].first;
            ofile << "," << stack[stack.size()-1].second << endl;
            cout << cnt  << ":" << stack[stack.size()-1].first;
            cout << "," << stack[stack.size()-1].second << endl;
            if((stack[stack.size()-1].first==1)&&(stack[stack.size()-1].second==0)){
                ofile << "fail to escape.";
                cout << "Failed to escape.";
                break;
            }
        }

    }

    return 0;
}