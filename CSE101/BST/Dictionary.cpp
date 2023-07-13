#include<iostream>
#include "Dictionary.h"
using namespace std;

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA7
* Dictionary.cpp
* Dictionary C++ File
*********************************************************************************/


 // Creates new Dictionary in the empty state.
Dictionary::Node::Node(keyType k, valType v){
   this->key = k;
   this->val = v;
   this->left = nullptr;
   this->right = nullptr;
   this->parent=nullptr;
}

Dictionary::Dictionary(){
   nil = new Node("zero",-1);
   current = nil;
   root = nil;
   num_pairs = 0;
}

   // Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("zero",-1);
    this->current = nil;
    this->root = nil;
    this->num_pairs = 0;
    preOrderCopy(D.root,D.nil);
}

   // Destructor
Dictionary::~Dictionary(){
    postOrderDelete(this->root);
    delete (this->nil);
}

 // Helper Functions (Optional) ---------------------------------------------

   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R!=this->nil){
        inOrderString(s,R->left);
        s+= R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s,R->right);
    }
}

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string consists of keys only, separated by "\n", with the order determined
   // by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R!=this->nil){
        s+= R->key + "\n";
        preOrderString(s,R->left);
        preOrderString(s,R->right);
    }
}

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R==N)

      return;
      
    setValue(R->key,R->val);
    if(R->left!=N)
    {
      preOrderCopy(R->left,N);
    } 
    if(R->right!=N)
    {
      preOrderCopy(R->right,N);
    }
}

   // postOrderDelete()
   // Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
     if(R->key.compare("zero")!=0){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete (R);
        this->num_pairs--;
     }
}

void Dictionary::Transplant(Node* u,Node* v){//Code provided by Patrick Tantalo in BST Pseudocode 
   if(u->parent == this->nil){
      this->root = v;
   }
   else if (u == u->parent->left){
      u->parent->left = v;
   }
   else{
      u->parent->right = v;
   }
   if(v != this->nil){
      v->parent = u->parent;
   }
}

   // search()
   // Searches the subtree rooted at R for a Node with key==k. Returns
   // the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
   while(R!=this->nil){
       if(R->key.compare(k)>0){
          R = R->left;
       }
       else if(R->key.compare(k)==0){
          return R;
       }
       else{
          R = R->right;
       }
    }
    return this->nil;
}

   // findMin()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){//Code provided by Patrick Tantalo in BST Pseudocode
     while(R->left!=this->nil){
          R = R->left;
     }
     cout << R->key << endl;
     return R;
} 

   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){//Code provided by Patrick Tantalo in BST Pseudocode
     while(R->right!=this->nil){
          R=R->right;
     }
     return R;
}

   // findNext()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk.  If N points to the rightmost 
   // Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){//Code provided by Patrick Tantalo in BST Pseudocode
   if(N->right != this->nil)
   {
       return findMin(N->right);
   }            
   Node* ancestor = N->parent;
   while(ancestor!=nil){
      if(ancestor->key > N->key){
         return ancestor;
      }
      ancestor = ancestor->parent;
   }
   return nil;
}

   // findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){//Code provided by Patrick Tantalo in BST Pseudocode
     if(N->left != this->nil)
   {
       return findMax(N->left);
   }               
   Node* ancestor = N->parent;
   while(ancestor!=nil){
      if(ancestor->key < N->key){
         return ancestor;
      }
      ancestor = ancestor->parent;
   }
   return nil;
}


   // Access functions --------------------------------------------------------

   // size()
   // Returns the size of this Dictionary.
int Dictionary::size() const{
    return this->num_pairs;
}

   // contains()
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
bool Dictionary::contains(keyType k) const{
   Node* temp = this->root;
    if(size()>0){
        Node* r = search(temp,k);
        if(r->key.compare(k)==0){
           return true;
        }
    }
    return false;
}

   // getValue()
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
   Node *r = this->nil;
    if(contains(k)){
       r = search(this->root,k);
    }
    return r->val;
}

   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
bool Dictionary::hasCurrent() const{
    if(this->current != this->nil && size()>0){
       return true;
    }
    return false;
}

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
   if(!hasCurrent()){
      throw logic_error("Dictionary Current Key is invalid");
   }
   return this->current->key;
}

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(!hasCurrent()){
      throw logic_error("Dictionary Current Valid is invalid");
    }
   return this->current->val;
}


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
   this->current = this->root;
   this->postOrderDelete(this->current);
   this->root = this->nil;
}

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
   if(this->root==this->nil){
      Node* node = new Node(k,v);
      node->parent = this->nil;
      node->left = this->nil;
      node->right = this->nil;
      nil->parent = node;
      this->root = node;
      num_pairs++;
   }
   else{
      Node* temp = this->root;
      while(temp!=this->nil){
          if(k < temp->key){
             if(temp->left==this->nil){
                 Node* node = new Node(k,v);
                 node->parent = temp;
                 node->left = this->nil;
                 node->right = this->nil;
                 nil->parent = node;
                 temp->left = node;
                 num_pairs++;
                 break; 
             }
             temp = temp->left;
          }
          else if(temp->key == k){
             temp->val = v;
             break;
          }
          else{
            if(temp->right==this->nil){
                 Node* node = new Node(k,v);
                 node->parent = temp;
                 node->left = this->nil;
                 node->right = this->nil;
                 nil->parent = node;
                 temp->right = node;
                 num_pairs++;
                 break;
             }
             temp = temp->right;
          }
      }
   }
}

   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
void Dictionary::remove(keyType k)//Code provided by Patrick Tantalo in BST Pseudocode
{
    if (!contains(k))
    {
        throw logic_error("Key does not exist in remove");
    }
    if (this->root->left==nil && this->root->right==nil)
    {
        clear();
        this->current = this->nil;
        return;
    }
    Node* check = search(this->root, k);
    if (check->right == this->nil)
    {
        Transplant(check, check->left);
    }
    else if (check->left == nil)
    {
        Transplant(check, check->right);
    }
    else
    { 
        Node* y = findMin(check->right);
        if (y->parent != check)
        {
            Transplant(y, y->right);
            y->right = check->right;
            y->right->parent = y;
        }
        Transplant(check, y);
        y->left = check->left;
        y->left->parent = y;
    }
    if (this->current == check)
    {
        this->current = this->nil;
    }
    delete(check);
    num_pairs--;
}

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
   this->current = this->root;
   if(this->num_pairs>0){
      this->current = findMin(this->current);
      cout << this->current->key << endl;
   }
}

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
   this->current = this->root;
   if(this->num_pairs>0){
      this->current = findMax(this->current);
   }
}

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
void Dictionary::next(){
    this->current = findNext(this->current);
}

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
void Dictionary::prev(){
     this->current = findPrev(this->current);
}


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
     std::string str = "";
     this->inOrderString(str,this->root);
     return str;
}

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
std::string Dictionary::pre_string() const{
   std::string str = "";
   if(size()>0){
     this->preOrderString(str,this->root);
   }
   return str;
}

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
     if(this->to_string() == D.to_string()){
         return true;
     }
     return false;
}


   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
      return stream << D.Dictionary::to_string();
}

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
     return A.equals(B);
}

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
     Dictionary* A = new Dictionary(D);
     return *A;
}

