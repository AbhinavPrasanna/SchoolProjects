#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include "List.h"

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA4
* List.c 
* List ADT
*********************************************************************************/

typedef struct NodeObj* Node;

typedef struct NodeObj{
        void* data;
            Node previous;
                Node next;
}NodeObj;

typedef struct ListObj{
        int length;
            Node cursor;
                Node front;
                    Node back;
                        int cursorindex;
}ListObj;

typedef struct EntryObj{
   int col;
   double data;
}EntryObj;


Entry newEntry(int column, int value){
    Entry entry = malloc(sizeof(Entry));
    entry->col = column;
    entry->data = value;
    return entry;
}

double data(Entry entry){
    if(entry==NULL){
      printf("Data Error: calling data() on NULL entry object\n");
      exit(EXIT_FAILURE);
    }
   return entry->data;
}

int column(Entry entry){
    if(column<0){
        printf("Column Error: calling column() on nonpositive column\n");
        exit(EXIT_FAILURE);
    }
    return entry->col;
}

List newList(void){
        List list = malloc(sizeof(ListObj));
            list->length = 0;
                list->front = NULL;
                    list->back = NULL;
                        list->cursor = NULL;
                            list->cursorindex = -1;
                                if(list==NULL){
                                            printf("List Error:calling newList() on NULL list reference\n");
                                                    exit(EXIT_FAILURE);
                                                        }
                                    return list;
}

Node newNode(void* data){
          Node N = malloc(sizeof(NodeObj));
          N->data = data;
             N->next = NULL;
                return(N);
}

void freeNode(Node* pN){
       if( pN!=NULL && *pN!=NULL ){
                 free(*pN);
                       *pN = NULL;
                          }
}

void freeList(List* pL){
        if((*pL)!=NULL && pL!=NULL){
                    free((*pL));
                            *pL = NULL;
                                }
            else{
                        printf("List is NULL!\n");
                                exit(EXIT_FAILURE);
                                    }
                
}

int length(List L){
        if(L==NULL){
                    printf("List Error: calling length() on NULL List Reference\n");
                            exit(EXIT_FAILURE);
                                }
            return L->length;
}

int index(List L){
        if(L==NULL){
                    printf("List Error:calling index() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            if((L->cursor)!=NULL){
                        return L->cursorindex;
                            }
                else{
                            return -1;
                                }
}

void* front(List L){
        if(L==NULL){
                    printf("List Error:calling front() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            return (L->front)->data;
}

void* back(List L){
        if(L==NULL){
                    printf("List Error: calling back() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            else if((L->back)!=NULL){
                        return (L->back)->data;
                            }
                else{
                            return (L->front)->data;
                                }
}

void* get(List L){
        if(L==NULL){
                    printf("List Error: calling get() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            if(L->cursorindex==-1){
                        printf("Cursor Index out of bound!\n");
                                exit(EXIT_FAILURE);
                                    }
                else if(L->cursor==NULL){
                            printf("Cursor == NULL\n");
                                    exit(EXIT_FAILURE);
                                        }
                    else if(L->length==0){
                                printf("List is EMPTY!\n");
                                        exit(EXIT_FAILURE);
                                            }
                        return (L->cursor)->data;
}


/*bool equals(List A, List B){
        if( A==NULL || B==NULL )
               {
                         return true;
                            }
           else if(A==NULL){
                      return false;
                         }
              else if(B==NULL){
                         return false;
                            }
                 else if(A->length != B->length){
                            return false;
                               }
                    Node N = A->front;
                       Node M = B->front;
                          for(int i=0;i<A->length;i++){
                                     if(N->data!=M->data){
                                                    return false;
                                                           }
                                            N = N->next;
                                                   M = M->next;
                                                      }
                             return true;
}*/
void clear(List L){
        //printf("Calling Clear\n");
        if(L==NULL){
                   printf("List Error: calling clear() on NULL List reference\n");
                          exit(EXIT_FAILURE);
                              }
            //printf("Temp Called\n");
            Node node = L->front;
                if (L->length>0)
                        {
                                    while(node->next!=NULL){
                                                    node = node->next;
                                                                freeNode(&node->previous);
                                                                        }
                                            L->length = 0;
                                                    L->cursor = NULL;
                                                            L->cursorindex = -1;
                                                                }
}
void set(List L, void* x){
        if(L==NULL){
                  printf("List Error: calling set() on NULL List reference\n");
                        exit(EXIT_FAILURE);
                            }
            if(index(L)>=0){
                       (L->cursor)->data = x;
                           }
}
void moveFront(List L){
        if(L==NULL){
                  printf("List Error: calling moveFront() on NULL List reference\n");
                        exit(EXIT_FAILURE);
                            }
            if(L->length>0){
                        L->cursorindex = 0;
                                L->cursor = L->front;
                                    }
}

void moveBack(List L){
        if(L==NULL){
                    printf("List Error: calling moveBack() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            if(L->length>0){
                        L->cursor = L->back;
                                L->cursorindex = length(L) - 1;
                                    }
}

void movePrev(List L){
        if(L==NULL){
                    printf("List Error:calling MovePrevious on NULL List reference");
                            exit(EXIT_FAILURE);
                                }
            if(index(L)<=0){
                        L->cursorindex=-1;
                                L->cursor=NULL;
                                        return;
                                            }
                L->cursorindex--;
                    L->cursor = (L->cursor)->previous;
}

void moveNext(List L){
        if(L==NULL){
                    printf("List Error:calling moveNext() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            if(index(L)>=length(L)-1){
                        L->cursorindex = -1;
                                L->cursor = NULL;
                                //printf("%d\n",L->cursorindex);
                                        return;
                                            }
                L->cursorindex++;
                    L->cursor = (L->cursor)->next;
}

void prepend(List L,void* x){
        //printf("Prepended!\n");
        if(L==NULL){
                    printf("List Error:calling prepend() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            Node node = newNode(x);
                if(length(L)==0){
                            L->front = node;
                                    L->back = L->front;
                                            //L->cursor = L->front;
                                        }
                    else if(length(L)==1){
                                L->front = node;
                                        (L->front)->next = L->back;
                                                (L->back)->previous = L->front;
                                                    }
                        else{
                                    //printf("%d -> %d\n",L->front->data,L->front->next->data);
                                    Node temp = L->front;
                                            L->front = node;
                                                    (L->front)->next = temp;
                                                            temp->previous = L->front;
                                                                    //printf("%d -> %d -> %d\n",L->front->data,L->front->next->data,temp->next->data);
                                                                    //L->cursor = L->front;
                                                                    //L->cursorindex--;
                                                                }
                            if(L->cursorindex!=-1){
                                        L->cursorindex++;
                                            }
                                L->length++;
}

void append(List L, void* x){
        //printf("Appended!\n");
        if(L==NULL){
                    printf("List Error:calling append() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            Node node = newNode(x);
                //printf("node->data = x\n");
                if(length(L)==0){
                            L->front = node;
                                    L->back = node;
                                            //printf("L->front = node\n");
                                        }
                    else{
                                 Node temp = L->back;
                                          L->back = node;
                                                   (L->back)->previous = temp;
                                                            temp->next = L->back;
                                                                     //L->cursor = L->back;
                                                                     //L->cursorindex++;
                                                                     //printf("L->back = node\n");
                                                                }
                        if(L->cursorindex==-1){
                                    L->cursorindex++;
                                        }
                            L->length++;
}

void insertBefore(List L, void* x){
        if(L==NULL){
                    printf("List Error:calling insertBefore() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            if(L->length == 0){
                        printf("List is Empty!\n");
                                exit(EXIT_FAILURE);
                                    }
                if(L->cursor == NULL){
                            printf("Cursor is NULL\n");
                                    exit(EXIT_FAILURE);
                                        }
                    if(index(L) < 0){
                                printf("Cursor is NULL\n");
                                        exit(EXIT_FAILURE);
                                            }
                        Node node = newNode(x);
                            if(index(L)>0){
                                            //printf("%d -> %d\n",L->cursor->previous->data,L->cursor->data);
                                            Node temp = (L->cursor)->previous;
                                                        (L->cursor)->previous = node;
                                                                    node->previous = temp;
                                                                                temp->next = node;
                                                                                            node->next = L->cursor;
                                                                                                        //printf("%d -> %d -> %d\n",temp->data,L->cursor->previous->data,L->cursor->data);
                                                                                                }
                                else{
                                            Node temp = L->front;
                                                    node->next = temp;
                                                            temp->previous = node;
                                                                    L->front = node;
                                                                        }
                                    L->length++;
                                        L->cursorindex++;
}

void insertAfter(List L, void* x){
        if(L==NULL){
                    printf("List Error:calling insertBefore() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            Node node = newNode(x);
                if(index(L)<length(L)-1){
                            Node temp = (L->cursor)->next;
                                    Node temp2 = L->cursor;
                                            temp2->next = node;
                                                    node->previous = temp2;
                                                            node->next = temp;
                                                                    temp->previous = node;
                                                                             //L->cursor = node;
                                                                             //L->cursorindex++;   
                                                                        }
                    else{
                                Node temp = L->back;
                                        temp->next = node;
                                                node->previous = temp;
                                                        L->back = node;
                                                            }
                        L->length++;
}

void deleteFront(List L){
        if(L==NULL){
                    printf("List Error:calling insertBefore() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            if(length(L)==0){
                        printf("Length == 0\n");
                                exit(EXIT_FAILURE);
                                    }
                if(length(L)==1){
                            freeNode(&L->front);
                                    L->cursorindex--;
                                        }
                    else{
                                Node temp = L->front->next;
                                        freeNode(&L->front);
                                                L->front = temp;
                                                        L->cursorindex--;
                                                            } 
                        L->length--;
}

void deleteBack(List L){
        if(L==NULL){
                    printf("List Error:calling deleteBack() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            if(L->length==0){
                        printf("List is EMPTY! \n");
                                exit(EXIT_FAILURE);
                                    }
                if(length(L)==1){
                            freeNode(&L->back);
                                    L->cursorindex--;
                                        }
                    else{
                              Node temp = L->back->previous;
                                    freeNode(&L->back);
                                          L->back = temp;
                                                if(index(L)==length(L)-1){
                                                              L->cursorindex = -1;
                                                                    }
                                                    }
                        L->length--;
}

void delete(List L){
        if(L==NULL){
                    printf("List Error:calling delete() on NULL List reference\n");
                            exit(EXIT_FAILURE);
                                }
            if(index(L)>=0 && length(L)>0){
                      if(index(L)==L->length-1){
                                   deleteBack(L);
                                            return;
                                                  }
                            else if(index(L)==0){
                                        deleteFront(L);
                                                return;
                                                      }
                                  else{
                                              Node temp = (L->cursor)->previous;
                                                      Node temp2 = (L->cursor)->next;
                                                              temp->next = temp2;
                                                                      temp2->previous = temp2;
                                                                              freeNode(&L->cursor);
                                                                                      L->cursorindex--;
                                                                                            }
                                      L->length--;
                                          }
}

void printList(FILE *out,List L){
         for(moveFront(L);index(L)>=0;moveNext(L)){
                      fprintf(out,"(%d, %.1f) ",column(get(L)),data(get(L)));
                               //printf("%d ->",get(L));
                           }
          fprintf(out,"\n");
}

/*List copyList(List L){
        List list = newList();
            if(L==NULL){
                        printf("LIST IS NULL!\n");
                                exit(EXIT_FAILURE);
                                    }

                if(length(L) < 0) {
                            printf("LIST IS NULL!\n");
                                    exit(EXIT_FAILURE);
                                        }
                    for(moveFront(L);index(L)>=0;moveNext(L)){
                                 append(list,get(L));
                                     }
                        moveFront(L);
                            return list;
}*/

List concatList(List A, List B){
        List list = newList();
            for(moveFront(A);index(A)>=0;moveNext(A)){
                        append(list,get(A));
                            }
                for(moveFront(B);index(B)>=0;moveNext(B)){
                            append(list,get(B));
                                }
                    return list;
}

