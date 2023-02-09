#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;





class AVLTree {


  //Structure for item nodes:
  //    id
  //    Left & Right pointers
  //    Height
  //
  // Root pointer
  struct item {
    int id;
    string title;
    string desc;

    item* left;
    item* right;

    int height;
  };
  
  item* root = NULL;
  ///////////////////////////


  


  // Insert(integer id, node pointer, string title, string desc):
  //      If(node is enpty):
  //            -create new node object
  //            -add key
  //            -add title and desc
  //            -set left and right nodes to NULL
  //      Else (if new key < current key)
  //            - Go left recursively
  //      Else
  //            - Go right recursively
  //      Return balance(node)
  item* insert(int x, item* t, string title, string desc) {
    if(t == NULL) {
      t = new item;
      t->id = x;
      t->title = title;
      t->desc = desc;
      t->left = t->right = NULL;
    }
    else if(x < t->id)
      t->left = insert(x, t->left, title, desc);
    else if(x > t->id)
      t->right = insert(x, t->right, title, desc);
    
    return balance(t);
  }
  /////////////////////////////////////////////////////////////////




  
  //Functions dealing with height
  //  height():
  //     Returns height of node, 0 if Null
  //
  //  updateHeight():
  //     Calculates and updates height in node object
  int height(item* t) {
    return t ? t->height : 0;
  }
  
  void updateHeight(item* t) {
    int hl = height(t->left);
    int hr = height(t->right);
    t->height = (hl>hr ? hl : hr) + 1;
  }
  //////////////////////////////////////////////////




  
  //Roration worker functions to be used in the balance controller
  item* rotateright(item* p) {
    item* q = p->left;
    p->left = q->right;
    q->right = p;
    updateHeight(p);
    updateHeight(q);
    return q;
  }

  item* rotateleft(item* q) {
    item* p = q->right;
    q->right = p->left;
    p->left = q;
    updateHeight(q);
    updateHeight(p);
    return p;
  }
  ////////////////////////////////////////////////////////////////




  
  /////Balance controller:
  //
  //balance_factor(node):
  //    return the difference between height
  //
  //balance(node):
  //    -updateheight
  //    -check for the four conditions to balance
  //    -balance right/left/rightleft/leftright
  int balance_factor(item* t) {
    return height(t->right) - height(t->left);
  }
  
  item* balance(item* t) {
    updateHeight(t);
    
    if(balance_factor(t) > 1){
      if(balance_factor(t->right) < 0){
	cout << "imbalance at: " << t->id << " rotating rightleft" << endl;
	t->right = rotateright(t->right);	
      }
      else{
	cout << "imbalance at: " << t->id <<" rotating left" << endl;
      }
      return rotateleft(t);
    }
    
    if(balance_factor(t) < -1 ) {
      if(balance_factor(t->left) > 0  ){
	cout << "imbalance at: " << t->id << " rotating rightleft" << endl;
	t->left = rotateleft(t->left);
      }
      else{
	cout << "imbalance at: " << t->id <<" rotating right" << endl;
      }
      return rotateright(t);
    }
    return t;
  }
  ///////////////////////////////////////////////////////////////////////////


  

  
  //verify(node):
  //   Verifies the absolute val of the left - right nodes is less than 1, recursively.
  //     That's pretty much it.
  //     It visits each node at most one time
  //          Time complexity: O(n)
  bool verify(item* t){
    if(t == NULL)
      return 1; 

    int hl = height(t->left);
    int hr = height(t->right);
 
    if(abs(hl - hr) <= 1   &&  verify(t->left)   &&  verify(t->right))
      return 1;
 
    return 0;
  }
  ///////////////////////////////////////////////////////////////////////////////////




  
  //postOrder(node):
  //   Displays the id, item title, description, and balance factor
  //   Uses post-order traversal (obviously)
  void postOrder(item* t ){
    if(t == NULL)
      return;
 
    else{
      postOrder(t->left);
      postOrder(t->right);
      cout << t->id << ":" << t->title << ":"
	   << t->desc <<" --  Balance: "
	   << balance_factor(t) << endl;
    }
  }
  /////////////////////////////////////////////////////////////////




  
//Public accessor methods for AVL tree.
public:

  ~AVLTree() {
    root = NULL;
  }

  void insert(int x, string title, string desc) {
    root = insert(x, root, title, desc);
  }

  void displayPostOrder(){
    cout << endl << "#### Displaying objects via post-order traversal ###" << endl;
    postOrder(root);
    cout << endl;
  }

  void displayVerify(){
    bool res;
    res = verify(root);

    if(res == true)
      cout << "The tree is a balanced AVL Tree." <<  endl;
    else
      cout << "The tree is /not/ balanced" << endl;
  }

};
////////////////////////////////////////////////////////////////////////////////////






int main() {

  //Instantiate AVLTree object, load data
  AVLTree t;
  ifstream inFile;
  inFile.open("MOCK_DATA.csv");


  //Exit safely if file is unable to be opened
  if (!inFile) {
    cout << "Unable to open file file";
    return 0;
  }

 
  
  //Read file, call insert function to add the data to AVL Tree
  // Close file
  while(inFile){
    string id;
    string title;
    string desc;
    
    getline(inFile, id, ',');
    getline(inFile, title, ',');
    getline(inFile, desc);

    stringstream ss(id);
    int idVal;
    ss >> idVal;

    
    t.insert(idVal, title, desc);

  }
  inFile.close();
  
  //////////////////////////////////////////////////////////////





  
  // Calls accessor methods to display the tree and display the AVL verification
  t.displayPostOrder();
  cout << endl;
  t.displayVerify();
}

