#include <iostream>
#include <fstream>
#include <cstdlib> // Needed to use the exit function
#include <queue> // for printing in level order
using namespace std;
ifstream ifile; //("sample.txt")
ofstream ofile("output.txt");
struct Node{
    int data;
    Node* left;
    Node* right;
};

Node* create_node(int data){//function for creating new node, called by the insert();
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
//if the search_data is smaller, recursively search left; if larger then search right
bool Search(Node* node, int search_data){
    if(node==NULL) return false;
    else if(node->data == search_data) return true;
    else if(node->data >= search_data) return Search(node->left, search_data);
    else return Search(node->right, search_data);
}
Node* Insert(Node* node, int insert_data){
    if(node==NULL){//empty tree
        node = create_node(insert_data);
    }
    else{
        if(node->data < insert_data){//keep on comparing to the right
            node->right = Insert(node->right, insert_data);
        }
        else{//keep on comparing to the left
            node->left = Insert(node->left, insert_data);
        }
    }
    return node; //update root
}
Node* FindMin(Node* node){//find the smallest in the right subtree
	while(node->left != NULL) node = node->left;
	return node;
}
Node* Delete(Node *node, int data){
    //search for the number to be deleted
	if(node == NULL) return node; 
	else if(node->data > data) node->left = Delete(node->left,data);
	else if (node->data < data) node->right = Delete(node->right,data);
	else {
		// Case 1:  No child
		if(node->left == NULL && node->right == NULL) { 
			delete node;
			node = NULL;
		}
		//Case 2: One child 
		else if(node->left == NULL) {
			Node *temp = node;
			node = node->right;
			delete temp;
		}
		else if(node->right == NULL) {
			struct Node *temp = node;
			node = node->left;
			delete temp;
		}
		// case 3: 2 children
		else { 
			Node *temp = FindMin(node->right);
			node->data = temp->data;
			node->right = Delete(node->right,temp->data);
		}
	}
	return node;
}
void level_order(Node* root){
    if(root == NULL) return;
	queue<Node*> q;
	q.push(root);  
	//while there is at least one discovered node
	while(!q.empty()) {
		Node* current = q.front();
		q.pop(); // removing the element at front
		cout << current->data << " ";
        ofile << current->data << " ";
		if(current->left != NULL) q.push(current->left);
		if(current->right != NULL) q.push(current->right);
	}
}
void preorder(struct Node *root){
	// base condition for recursion
	// if tree/sub-tree is empty, return and exit
	if(root == NULL) return;

    cout << root->data << " ";// Print data
    ofile << root->data << " ";
	preorder(root->left);     // Visit left subtree
	preorder(root->right);    // Visit right subtree
}

//Function to visit nodes in Inorder
void inorder(Node *root){
	if(root == NULL) return;

	inorder(root->left);       //Visit left subtree
	cout << root->data << " ";  //Print data
    ofile << root->data << " ";
	inorder(root->right);      // Visit right subtree
}

//Function to visit nodes in Postorder
void postorder(Node *root) {
	if(root == NULL) return;

	postorder(root->left);    // Visit left subtree
	postorder(root->right);   // Visit right subtree
	cout << root->data << " "; // Print data
    ofile << root->data << " ";
}
void print_menu(){
    //print the operations menu in the beginning of each round
    cout << "(I)nsert a number." << endl;//console
    cout << "(D)elete a number." << endl;
    cout << "(S)earch a number." << endl;
    cout << "(P)rint 4 kinds of orders." << endl;
    cout << "(E)xit" << endl;
    cout << endl;
    ofile << "(I)nsert a number." << endl;//output file
    ofile << "(D)elete a number." << endl;
    ofile << "(S)earch a number." << endl;
    ofile << "(P)rint 4 kinds of orders." << endl;
    ofile << "(E)xit" << endl;
    ofile << endl;
}
int main(){
    cout << "Enter file name: ";
    ofile << "File name: ";
    string filename;
    cin >> filename;
    ofile << filename;
    ifile.open(filename);
    cout << endl;
    ofile << endl;
    Node* root = NULL;
    char c;
    int num;
    while(1){
        cout << endl;
        ofile << endl;
        print_menu();
        ifile >> c;
        if(c=='I'||c=='i'){
            cout << "Insert:" << endl;
            ofile << "Insert:" << endl;
            ifile >> num;
            while(num!=-1){
                if(!Search(root, num)){
                    root = Insert(root, num);
                    cout << "Number " << num << " is inserted." << endl;
                    ofile << "Number " << num << " is inserted." << endl;
                }
                else{
                    cout << "Error! Number " << num << " exists." << endl;
                    ofile << "Error! Number " << num << " exists." << endl;
                }
                ifile >> num;
            }
        }
        else if(c=='D'||c=='d'){
            cout << "Delete:" << endl;
            ofile << "Delete:" << endl;
            ifile >> num;
            while(num!=-1){
                if(Search(root, num)){
                    root = Delete(root, num);
                    cout << "Number " << num << " is deleted." << endl;
                    ofile << "Number " << num << " is deleted." << endl;
                }
                else{
                    cout << "Number " << num << " is not exist." << endl;
                    ofile << "Number " << num << " is not exist." << endl;
                }
                ifile >> num;
            }       
        }
        else if(c=='S'||c=='s'){
            cout << "Search:" << endl;
            ofile << "Search:" << endl;
            ifile >> num;
            while(num!=-1){
                if(Search(root, num)){
                    cout << "Bingo! " << num << " is found." << endl;
                    ofile << "Bingo! " << num << " is found." << endl;
                }
                else{
                    cout << "Sorry! " << num << " is not found." << endl;
                    ofile << "Sorry! " << num << " is not found." << endl;
                }
                ifile >> num;
            }
        }
        else if(c=='P'||c=='p'){
            cout << "Print:" << endl;
            ofile << "Print:" << endl;
            //preorder
            cout << "The tree in prefix order: ";
            ofile << "The tree in prefix order: ";
            preorder(root);
            cout << endl;
            ofile << endl;
            //inorder
            cout << "The tree in infix order: ";
            ofile << "The tree in infix order: ";
            inorder(root);
            cout << endl;
            ofile << endl;
            //postorder
            cout << "The tree in post order: ";
            ofile << "The tree in post order: ";
            postorder(root);
            cout << endl;
            ofile << endl;
            //level order
            cout << "The tree in level order: ";
            ofile << "The tree in level order: ";
            level_order(root);
            cout << endl;
            ofile << endl;
        }
        else if(c=='E'||c=='e'){
            cout << "Exit" << endl;
            ofile << "Exit" << endl;
            exit(0);
        }
    }

    return 0;

}