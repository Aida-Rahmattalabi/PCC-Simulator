/*
 * PCCSimulator.cpp
 *
 *  Created on: Dec 30, 2014
 *      Author: will
 */

#include "PCCSimulator.h"

PCCSimulator::PCCSimulator(bool debug): m_debug(debug) {
	graph = new PCCGraph();
	string homedir = getenv("HOME");
	string process_file = homedir + "/PCC-Simulator/PCC-Project/src/process.csv";
	string graph_file = homedir + "/PCC-Simulator/PCC-Project/src/graph.csv";
	if(m_debug)
	{
		cout << "Looking for files:" << endl;
		cout << process_file << endl;
		cout << graph_file << endl;
	}
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
	if(m_debug) debug_output();

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
	if(m_debug) debug_output();
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

void PCCSimulator::debug_output()
{
	cout << "current step: " << cur_step << endl;
	for (Graph::const_iterator p = graph->G.begin(); p != graph->G.end(); p++)
	{
		Graph::vertex cur_vertex = Graph::node(p);
		cout << "vertex: " << cur_vertex << ": " << graph->get_name(cur_vertex) << ", ";

		event cur_proccess_status = graph->get_process_status(cur_vertex);
		string hr_status;
		if(cur_proccess_status == WAITING) hr_status = "WAITING";
		if(cur_proccess_status == DONE) hr_status = "DONE";
		cout << hr_status << " ";

		int cur_object = graph->get_object(cur_vertex);
		cout << cur_object << endl;

		if(cur_proccess_status == WAITING && cur_object != -1) throw;

		vector<unsigned int> cur_objects_waiting = graph->get_objects_waiting(cur_vertex);
		cout << "Waiting for: ";
		for(vector<unsigned int>::iterator it = cur_objects_waiting.begin(); it != cur_objects_waiting.end(); it++)
		{
			cout << *it << ", ";
		}
		cout << endl;

	}
}

PCCSimulator::~PCCSimulator() {
	// TODO Auto-generated destructor stub
}

