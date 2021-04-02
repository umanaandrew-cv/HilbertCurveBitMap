#include <cstring>
#include <iostream>
#include <unordered_map>
using namespace std;

#include "hilbert.h"

const int HILBERT_LEVEL = 8;
const int IMAGE_SIZE = 600;
const string OUTPUT_FILE = "hilbert.bmp";

// image created on hilbert.bmp
int main() {
	HilbertCurve curve(6, IMAGE_SIZE);
	curve.writeToFile(OUTPUT_FILE);

	return 0;
}