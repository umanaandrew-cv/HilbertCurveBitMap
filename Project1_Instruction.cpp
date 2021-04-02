#include <iostream>
#include "instruction_list.h"
#include <unordered_map>

using namespace std;

ostream& operator<<(ostream& out , const InstructionList& d)
{
  InstructionList::node_t* cur=d.head;                          //pointer that points to the objects head

  while(cur!=nullptr)                                           //while loop goes through list
  {
    switch(cur->move)                                          //switch determines whats printed out, cur->move points to move instruction
    {
      case 0:
        out<<"F ";
        break;
      case 1:
       out<<"L ";
        break;
      case 2:
        out<<"R ";
        break;
      case 3:
        out<<"O ";
        break;
      case 4:
        out<<"E ";
        break;
    }

    cur=cur->next;                                              //iterates to next pointer
  }

    return out;                                                 //return ostream operator
} 

//Given an instruction, this function adds it to the end of the list
void InstructionList::append(hilbert_t move)
{
  node_t* cur=new node;                                       //create a new node to be appended
  cur->move = move;                                           //Assign move value to the new node
  cur->next = nullptr;                                        //Set the next node to nullptr
  
  if(head==nullptr)                                           //If list is empty, set head node to cur node
  {
    head = cur;
    return;                      
  }
  
  node_t* t = head;                                           //Set node t equal to head
  while(t->next != nullptr)                                   //Loop to traverse the list until the last node
  {
    t = t->next;
  }
  
  t->next = cur;                                              //Point the last node to cur, making cur the last node of the list
  tail = cur;                                                 //Set cur as the tail node

}

//If an instruction in the key of the map is found in the list, it will be replaced by the list in the value of the map
void InstructionList::substitute(const unordered_map<hilbert_t, const InstructionList*>& m) 
{ 
   node_t* cur;
    for(cur = head; cur != nullptr; cur=cur->next)                      //Iterates through the linked list
    {
        if(m.count(cur->move))                                          //Checks if cur->move is present in map
        if(cur->move == (m.find(cur->move))->first)         
        {
          node_t* begin = (m.find(cur->move))->second->head;          //begin is the first node of linked list being substituted
          node_t* after = cur->next;                              //node after cur, new nodes are linked between cur and this node
                
          cur->move = begin->move;                                //Change move of cur to move in the first node of list to sub
          node_t* temp = begin->next;                             //Node points to second node in list to sub
          while(temp != nullptr)                                  //Loop creates a new node for each node in sub list and links them to list
          {
            node_t* newNode = new node_t;                       //Node created to link to cur node
            newNode->move = temp->move;                         //Set new node's move equal to temp node's move(copying over move)
            cur->next = newNode;                                //Linking the new node to cur node, becomes part of list
            newNode->next = after;                              //Setting node->next equal to node after cur node
            if(temp->next != nullptr)                           //Checks if last node in sub list has been reached
              temp = temp->next;                              //If not, continue loop
            else break;                                         //Else break, every node in sub list has been copied
            cur = cur->next;
          } // end while
          cur = cur->next;
        } // end if
    } //end for
} 

//Destructor, deallocates all of the nodes in the list
InstructionList::~InstructionList()
{
  node_t* cur=head;                 //Set cur to point to head of the list
  node_t* temp=nullptr;             //temp node points to nullptr
  while(cur!=nullptr)               //As long as the end of the list has not been reached, loop deletes every node
  {
    temp=cur->next;                 //temp node is the leading node
    cur->next=nullptr;              //Set cur node's next equal to nullptr before deleting
    delete cur;                     //Delete cur node

    head=temp;                      //Makes the leading node the head node
    cur=temp;                       //cur and temp now point to the same node
  }
  
}