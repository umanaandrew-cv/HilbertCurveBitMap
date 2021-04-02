#ifndef __HILBERT_H
#define __HILBERT_H

#include <string>
using namespace std;

#include "instruction_list.h"
#include "turtle.h"

//Class to draw Hilbert curves
class HilbertCurve
{
private:
  Turtle turtle;
  InstructionList rules;
public:
  HilbertCurve(int level, int size);
  void writeToFile(string file) const
    { turtle.outputImage(file); }
};

#endif