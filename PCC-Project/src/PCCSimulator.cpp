/*
 * PCCSimulator.cpp
 *
 *  Created on: Dec 30, 2014
 *      Author: will
 */

#include "PCCSimulator.h"

PCCSimulator::PCCSimulator() {
	graph = new PCCGraph();
	string homedir = getenv("HOME");
	string process_file = homedir + "/PCC-Simulator/PCC-Project/src/process.csv";
	string graph_file = homedir + "/PCC-Simulator/PCC-Project/src/graph.csv";
	//cout << "Looking for files:" << endl;
	//cout << process_file << endl;
	//cout << graph_file << endl;
	graph->create_graph(process_file, graph_file);
	//graph->set_discretization(m_discretization);

	cur_step = 0;
}


void PCCSimulator::run_simulation(unsigned int timesteps, unsigned int object_generation_rate)
{
	m_object_generation_rate = object_generation_rate;
	for(unsigned int i = 0; i < timesteps; i++)
	{
		step();
	}
}

void PCCSimulator::set_discretization(double discretization)
{
	graph->set_discretization(discretization);
}

void PCCSimulator::step()
{
	if(cur_step % m_object_generation_rate == 0)
	{
		cur_step = 0;
		graph->add_objects_to_inputs();
		cur_step++;
		return;
	}
	for (Graph::const_iterator p = graph->G.begin(); p != graph->G.end(); p++)
	{
		Graph::vertex cur_vertex = Graph::node(p);
		process_step(cur_vertex);
	}
	for (Graph::const_iterator p = graph->G.begin(); p != graph->G.end(); p++)
	{
		Graph::vertex cur_vertex = Graph::node(p);
		finalize_step(cur_vertex);
	}
	cur_step++;
}

void PCCSimulator::process_step(unsigned int cur_idx)
{
	event cur_proccess_status = graph->get_process_status(cur_idx);
	if(cur_proccess_status == WAITING) return;
	if(cur_proccess_status == DONE) throw;
	graph->execute_process(cur_idx);
}

void PCCSimulator::finalize_step(unsigned int cur_idx)
{
	event cur_proccess_status = graph->get_process_status(cur_idx);
	if(cur_proccess_status == DONE)
	{
		graph->move_obj_to_next(cur_idx);
	}
}

PCCSimulator::~PCCSimulator() {
	// TODO Auto-generated destructor stub
}

