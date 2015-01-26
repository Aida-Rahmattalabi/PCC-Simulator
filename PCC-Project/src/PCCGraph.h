/*
 * PCCGraph.h
 *
 *  Created on: Dec 18, 2014
 *      Author: will
 */

#ifndef PCCGRAPH_H_
#define PCCGRAPH_H_

#include <map>
#include "Process.h"
#include "ngraph.hpp"
#include <fstream>
using namespace NGraph;
using namespace std;

class PCCGraph: public tGraph<Process> {
public:
	PCCGraph();

	void insert_edge(Process* p1, Process* p2);
	void create_graph(string process_file, string graph_file);
	void output_dot();
	void move_obj_to_next(unsigned int idx);
	Process* get_process(unsigned int idx);
	void set_inputs();
	event get_process_status(unsigned int idx);
	void execute_process(unsigned int idx);
	void set_discretization(double discretization);
	void add_objects_to_inputs();

	tGraph<unsigned int> G;
	vector<unsigned int> input_edges;
	map<unsigned int, Process*> m_vec_to_process;
	map<Process*, unsigned int> m_process_to_vec;
	int m_max_vector;
	double m_discretization;

	virtual ~PCCGraph();
};

#endif /* PCCGRAPH_H_ */
