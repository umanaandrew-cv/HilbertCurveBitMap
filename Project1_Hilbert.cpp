
#include <iostream>
#include <unordered_map>
#include <cstring>
#include <cmath>
using namespace std;

#include "hilbert.h"

//Constructor for HilbertCurve class, initializes InstructionList and Turtle objects to draw a Hilbert curve
HilbertCurve::HilbertCurve(int level, int size)
  :turtle(size,size),rules()   
{                                                                           
  double distance= size/(pow(2,level));                        //sets the distance, call InstructionList::setDistance()
  rules.setDistance(distance);                                 //getDistance() is automatically called later
  rules.append(ODD);                                               //appending original ODD move
 
  InstructionList* ptr;                                        //pointer that points to instruction list
  unordered_map<hilbert_t, const InstructionList*> map;        //declaration of our map that we will pass to substitute
  
  InstructionList odd;                                         //substitution rules for odd
  odd.append(TURN_LEFT);
  odd.append(EVEN);
  odd.append(FORWARD);
  odd.append(TURN_RIGHT);
  odd.append(ODD);
  odd.append(FORWARD);
  odd.append(ODD);
  odd.append(TURN_RIGHT);
  odd.append(FORWARD);
  odd.append(EVEN);
  odd.append(TURN_LEFT);

  InstructionList e;    
  e.append(TURN_RIGHT);                                        //substitution rules for even
  e.append(ODD);
  e.append(FORWARD);
  e.append(TURN_LEFT);
  e.append(EVEN);
  e.append(FORWARD);
  e.append(EVEN);
  e.append(TURN_LEFT);
  e.append(FORWARD);
  e.append(ODD);
  e.append(TURN_RIGHT);

  ptr = &odd;                                                  //maps out odd
  map[ODD] = ptr;
  
  ptr = &e;                                                    //maps out even
  map[EVEN] = ptr;
                          
  for (int i=0; i<level; i++)                                  //for loop that iterates # of levels
  {
    rules.substitute(map);
  }
  
  turtle.follow(rules);                                       //Calls follow function which follows the instructions in rules list

}