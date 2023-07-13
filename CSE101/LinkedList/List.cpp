#include "List.h"
using namespace std;

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA5
* List.cpp
* List C++ File
*********************************************************************************/

List::Node::Node(ListElement x){//Code Provided by Professor Tantalo
   data = x;
   next = nullptr;
   prev = nullptr;
}

List::List(){
   frontDummy = new Node(0);
   backDummy = new Node(0);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

List::List(const List& L){//Code Provide by Professor Tantalo
   frontDummy = new Node(0);
   backDummy = new Node(0);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
   Node *node = L.frontDummy->next;
   while(node!=L.backDummy){
       this->insertBefore(node->data);
       node = node->next;
   }
}
List::~List(){
   clear();
   pos_cursor = 0;
   num_elements = 0;
}

int List::length() const{
    return num_elements;
}

ListElement List::front() const{
    if(length()>0){
        return this->frontDummy->next->data;
    }
    return this->frontDummy->data;
}

ListElement List::back() const{
    if(length()>0){
        return this->backDummy->prev->data;
    }
    return this->backDummy->data;
}

int List::position() const{
    return this->pos_cursor;
}

ListElement List::peekNext() const{
     if(length()>0){
        return afterCursor->data;
     }
     return frontDummy->data;
}

ListElement List::peekPrev() const{
     if(length()!=0 && position()!=0){
        return this->beforeCursor->data;
     }
     return this->backDummy->data;
}

void List::clear(){
    moveFront();
    while(length()!=0){
        eraseAfter();
    }
}

void List::moveFront(){
    if(length()>0){
        pos_cursor=0;
        beforeCursor=this->frontDummy;
        afterCursor=this->frontDummy->next;
    }
}

void List::moveBack(){
    if(length()>0){
      pos_cursor=length();
      beforeCursor=this->backDummy->prev;
      afterCursor=this->backDummy;
    }
}

ListElement List::moveNext(){
    if(length()>0){
        afterCursor = afterCursor->next;
        beforeCursor = beforeCursor->next;
        pos_cursor++;
    }
    return beforeCursor->data;
}
ListElement List::movePrev(){
    if(length()>0){
        afterCursor = afterCursor->prev;
        beforeCursor = beforeCursor->prev;
        pos_cursor--;
    }
    return afterCursor->data;
}
void List::insertAfter(ListElement x){
    Node* node = new Node(x);
    Node* temp = afterCursor;
    beforeCursor->next = node;
    node->prev = beforeCursor;
    afterCursor = node;
    node->next = temp;
    temp->prev = afterCursor;
    num_elements++;
}
void List::insertBefore(ListElement x){
    Node *node = new Node(x);
    Node* temp = beforeCursor;
    afterCursor->prev = node;
    node->prev = temp;
    beforeCursor = node;
    node->next = afterCursor;
    temp->next = node;
    pos_cursor++;
    num_elements++;
}

void List::setAfter(ListElement x){
     if(pos_cursor<length()){
        afterCursor->data = x;
     }
}

void List::setBefore(ListElement x){
    if(pos_cursor>0){
        beforeCursor->data = x;
    }
}

void List::eraseAfter(){
    if(position()<length()){
        Node* temp = afterCursor;
        beforeCursor->next = afterCursor->next;
        afterCursor = afterCursor->next;
        afterCursor->prev = beforeCursor;
        delete temp;
        num_elements--;
    }
}

void List::eraseBefore(){
    if(pos_cursor>0){
        Node *temp2 = beforeCursor;
        afterCursor->prev = beforeCursor->prev;
        beforeCursor=beforeCursor->prev;
        beforeCursor->next = afterCursor;
        num_elements--;
        pos_cursor--;
        delete temp2;
    }
}

 int List::findNext(ListElement x){
    while(peekNext()!=0){
        if(peekNext()==x){
            moveNext();
            return pos_cursor-1;
        }
        moveNext();
    }
    moveBack();
    return -1;   
 }

 int List::findPrev(ListElement x){
    while(peekPrev()!=0){
        if(peekPrev() == x){
            movePrev();
            return pos_cursor+1;
        }
        movePrev();
    }
    moveFront();
    return -1; 
}

void List::cleanup(){
    int savedelement = 0;
    int savedindex = 0;
    for(moveFront();peekNext()!=0;moveNext()){
       savedelement = peekNext();
       savedindex = position();
       for(moveFront();peekNext()!=0;moveNext()){
             if(savedelement == peekNext() && position()!=savedindex){
                eraseAfter();
                /*if(savedindex<pos_cursor){
                    pos_cursor--;
                }*/
                if(peekNext()==0){
                    break;
                }
             }
        }
        while(peekNext()!=savedelement){
            movePrev();
        }      
    }
}

List List::concat(const List& L) const{
    List l;
    Node* node = frontDummy->next;
    Node* mode = (L.frontDummy)->next;
    while(node != this->backDummy){
        l.insertBefore(node->data);
        node = node->next;
    }
    while(mode != L.backDummy){
        l.insertBefore(mode->data);
        mode = mode->next;
    }
    l.moveFront();
    return l;
}

std::string List::to_string() const{//Code provided by Tantalo
   Node* node = frontDummy->next;
   std::string s = "";

   while(node!=backDummy){
       if(node==backDummy->prev){
          s += std::to_string(node->data);
       }
       else{
           s += std::to_string(node->data)+",";
       }
       node = node->next;
   }
   return s;
}

bool List::equals(const List& R) const{
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;
   eq = ( this->length() == R.length() );
   N = this->frontDummy->next;
   M = R.frontDummy->next;
   while(eq && N!=backDummy){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Overriden Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of Q, as defined by member function 
// to_string(), into stream.
std::ostream& operator<< ( std::ostream& stream,  const List& L ){//Code provided by Tantalo
   return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if Queue A equals Queue B, as defined by member
// member function equals().
bool operator== (const List& A, const List& B){
   return A.List::equals(B);
}

// operator=()
// Overwrites the state of this Queue with state of Q, then returns a reference
// to this Queue.
List& List::operator=( const List& L ){
   if( this != &L ){ // not self assignment
      // make a copy of Q
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(this->frontDummy, temp.frontDummy);
      std::swap(this->backDummy, temp.backDummy);
      std::swap(this->num_elements, temp.num_elements);
      std::swap(this->beforeCursor,temp.beforeCursor);
      std::swap(this->afterCursor,temp.afterCursor);
      std::swap(this->pos_cursor,temp.pos_cursor);
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}











