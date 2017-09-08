#include "fpArrayTester.h"
uint32 ArrayValue::Index = 0;
uint32 ArrayValue::FillerLength = 12;
uint32 fpArrayTester::TestedLength = 0;
fpArray<ArrayValue>* fpArrayTester::Array = nullptr;
vector<ArrayValue>* fpArrayTester::Vector = nullptr;
