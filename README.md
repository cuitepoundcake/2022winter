# 2022winter
data structure practice


### practice 1: maze problem
- Given a 17*17 matrix as a maze. Zeros represent the open path and ones are barriers. The rat would start its journey from the top left (representing [1,0]) and end at bottom right (representing [15, 16]).
- There are only nine directions to move, and must follow the clockwise order to find the possible path, or it will be no scores for not following the order. The order starts from going right. Finally, output the journey of the rat and whether it escapes the maze or not.

> my solution:
> 
> first of all, create a matrix and clear all the value to 0
> then read the file, read in the digits in char form then change them to int by -48
> 
> create a stack using vector
> each element in stack is a coordinate
> first, push the starting coordinate (1,0) into the stack
>
> while the stack is not empty
> check all eight directions of the top of the stack
> if the direction(element) is marked 0(availble), then push it in the stack
> and change the mark from 0 to 2
> and, if this available element==(15,16), then successed of find a way out

> if there is no any available direction to go (surrounded by either 1 or 2)
> then set the current element to 1 and pop it out of the stack
> print the top element of the stack,
> if the top element right now == (1,0), then failed to find a path out, so break out of the loop,
> otherwise continue the loop


### practice 2: implement a binary search tree
- Implement the binary search tree (BST) operations with linked list.
- 1. Insert: Enter “i” or “I”, then enter a sequence of numbers and ended with “-1” to build a BST.
- 2. Delete: Enter “d” or “D”, then enter a sequence of numbers ended with “-1” to delete those nodes.
- 3. Search: Enter “s” or “S”, then enter a sequence ended with -1 to search whether the number is in the BST. If the number is not in the BST then print the number is not found.
- 4. Enter “p” or “P” to print prefix -> infix -> postfix and level order of the BST.
- 5. Enter “e” or “E” to exit the program.

> my solution:
>
> in the main funtion, after reading in the input file name,
> there is a while loop to continuously ask the user to input different command,
> until the user want it to exit.
> when the case is "insert", call the search function to search if the number exists or not, if not exist, then call the Insert function,
> int the function, we recursively compare the number to be insert with the nodes starting from the root,
> finally find the right position, and insert it
> 
> when the case is "Delete", call the search funtion, if the number exists , then call the Delete function,
> recursively search for the number, if the deleted node is a leaf, then delete it directly.
> if the deleted node has a child, then replace the deleted node with its child.
> finally, if the deleted node has left and right sub-tree, then call the FindMin function to find the smallest node of the right sub-tree,
> and replace the deleted node with the smallest node of the right sub-tree.
> 
> if the case is "search", then call the search funtion, the function will return 1 if exist, return 0 if doesn't exist.
> 
> if the case is "print", call the preorder, inorder, postorder, and level order function,
> in the level_order function, search and output all the nodes using BFS, so after we find all the child of the node,
> take it out of the queue.
> 
> finally if the case is "Exit", print exit and finished the program.


### practice 2-1: Implement Prim’s algorithm to find minimal spanning tree.
### practice 2-2: Implement Dijkstra’s algorithm to solve shortest path problem

The input consists of three parts. The first line is the numbers of edges (n). Then, n lines of edge will be entered in the format (v1 v2 w), v1 and v2 are the vertex of this edge, w is its weight, and there will have space to separate them. The last line of input is the starting point.
*The input format for both questions is the same.
*Every vertex will be represented by a lowercase English alphabet.
*check the attached files named sample_p.txt and sample_d.txt to see the full input

> #### solution to Prim’s algorithm:
>
> enter the filename to open the input file,
> create a vector of vector as an adjacency list to store the endpoints of the edges and its weight,
> (change the endpoint from char(alphabet) to int by -97)
> count the number of the vertices at the same time, the number of the vertices is num,
> 
> create a vector vis to see if the vertex has been proccessed
> create a vector cost to record the cost of every vertex, inorder to find the vertex with the smallest cost
> create a vertor parent to record the parent of each vertex
> 
> set the parent of the starting vertex to -1
> set the cost of the startong vertex to 0,so that it will be chosen first in the loop,
> since it has the smallest cost
> 
> 
> in the while loop, find those num-1 edges to form a MST
> {
> call the findMinCost() to find the vertex, m,  which has the smallest cost among all unproccessed vertices
> 
> check if all the vertixes are proccessed, break if it is true,
> 
> now scan through all the neighbors, j, of m,
> if it is unvisited and the current cost is larger than the weight of m-j edge,
> then update the cost and set the neighbor of j to m,
> }
> 
> create a vector to store the value and one of the end point of every edge
> find the value of the vertex and its parent, and store it in the vector
> than sort the vector in ascending order by the value
> 
> find the another end point, compare them and print the smaller one first, and then the larger one, 
> and finally print the value.


> #### solution to Dijkstra’s algorithm::
>
> enter the filename to open the input file,
> create a vector of vector as an adjacency list to store the endpoints of the edges and its weight,
> (change the endpoint from char(alphabet) to int by -97)
> count the number of the vertices at the same time, the number of the vertices is num,
> 
> create a vector vis to see if the vertex has been proccessed
> create a vector cost to record the cost of every vertex, inorder to find the vertex with the smallest cost
> 
> set the cost of the startong vertex to 0,so that it will be chosen first in the loop,
> 
> in the while loop{
> first check if all verices have been proccesed, break if it is true
> 
> then call the findMindCost() to find vertex, m,  which has the smallest cost among all unproccessed vertices
> set m as visited
> 
> visited all the neighbors, j, of m, 
> if the current cost of j is larger than cost[m]+(the weight of edge m-j), 
> then change the cost of j to the latter,
> }
> 
> create a vector of pair, and make pair all the vertex and its cost(which means the cost of the shortest path)
> sort the vector according to the cost
> and then print the result
