// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
template<typename T>
class test
{};

#define get_genearated_ClassType(name) \
	generated_##name

#define declare_class_degin(name)\
	class  generated_##name{\
	public: generated_##name(){};

#define declare_class_end() };

#define declare_class_field(fType,fName)\
	fType fName

#define declare_class_function(clName,fnName,body)\
	int get_genearated_ClassType(clName)::fnName(){\
	return body; \
	}


declare_class_degin(genTest);
	declare_class_field(int, field1);
	declare_class_field(float, field2);
	declare_class_function(genTest, Function1, 3 * 4;);
declare_class_end();



int _tmain(int argc, _TCHAR* argv[])
{
	get_genearated_ClassType(genTest) LOOOOL = get_genearated_ClassType(genTest)();
	test<get_genearated_ClassType(genTest)> o_O;
	std::cout << LOOOOL.Function1() << std::endl;
	system("PAUSE");
	return 0;
}

