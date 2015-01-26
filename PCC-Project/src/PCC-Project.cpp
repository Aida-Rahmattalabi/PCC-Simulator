//============================================================================
// Name        : PCC-Project.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "ngraph.hpp"
#include "Process.h"
#include "PCCGraph.h"
#include "PCCSimulator.h"
#include <string.h>
using namespace std;
using namespace NGraph;


int main(int argc, const char* argv[]) {
	//cout << argv[1] << endl; // prints !!!Hello World!!!
	PCCSimulator* s = new PCCSimulator();

	if(argc > 1)
	{
		string s2 = argv[1];

		if(s2 == "-v")
		{
			s->graph->output_dot();
		}
	}


	s->run_simulation(20, 100);
	return 0;
}
