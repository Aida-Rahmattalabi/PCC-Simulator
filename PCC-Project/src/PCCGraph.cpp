/*
 * PCCGraph.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: will
 */

#include "PCCGraph.h"

PCCGraph::PCCGraph() {

}

std::istream & operator>>(std::istream &s, map<unsigned int, Process*> &m)
{
    std::string line;

    while (getline(s, line))
    {
      int v1;
      Process* p1 = new Process();

      if (line[0] == '%' || line[0] == '#')
        continue;

      std::istringstream L(line);
      L >> v1;

      string name;
      L >> name;
      p1->m_name = name;

      double time_cost;
      L >> time_cost;
      p1->m_time_cost = time_cost;
	  m.insert(make_pair(v1, p1));
    }
    return s;
}

void PCCGraph::create_graph(string process_file, string graph_file)
{
    ifstream s_process;
    s_process.open(process_file.c_str());
    s_process >> m_vec_to_process;

    ifstream s_graph;
    s_graph.open(graph_file.c_str());
    s_graph >> G;
    set_inputs();
}

void PCCGraph::set_inputs()
{
	for (Graph::const_iterator p = G.begin(); p != G.end(); p++)
	{
		const Graph::vertex_set &in = Graph::in_neighbors(p);
		if(in.empty())
		{
			input_edges.push_back(Graph::node(p));
		}
	}
}
void PCCGraph::insert_edge(Process* p1, Process* p2)
{
	int edge1,edge2;
	map<Process*, unsigned int>::iterator process_it = m_process_to_vec.find(p1);
	if (process_it == m_process_to_vec.end())
	{
		edge1 = m_max_vector;
		m_process_to_vec.insert(make_pair(p1, edge1));
	}
	else edge1 = process_it->second;

	process_it = m_process_to_vec.find(p2);
	if (process_it == m_process_to_vec.end())
	{
		edge2 = m_max_vector;
		m_process_to_vec.insert(make_pair(p2, edge2));
	}
	else edge2 = process_it->second;

    G.insert_edge(edge1,edge2);
}

Process* PCCGraph::get_process(unsigned int idx)
{
	map<unsigned int, Process*>::iterator it = m_vec_to_process.find(idx);
	if(it == m_vec_to_process.end())
	{
		throw;
	}
	Process* cur_process = it->second;
	return cur_process;
}

event PCCGraph::get_process_status(unsigned int idx)
{
	return m_vec_to_process.find(idx)->second->get_status();
}

void PCCGraph::execute_process(unsigned int idx)
{
	m_vec_to_process.find(idx)->second->execute(m_discretization);
}

void PCCGraph::set_discretization(double discretization)
{
	m_discretization = discretization;
}

void PCCGraph::move_obj_to_next(unsigned int cur_idx)
{
	Process* from_process = m_vec_to_process.find(cur_idx)->second;
	unsigned int object = from_process->m_cur_object;

	Graph::const_iterator p = G.find(cur_idx);
	const Graph::vertex_set &out = Graph::out_neighbors(p);

	//TODO: Logic for choosing which out neighbors to send things to. Currently doing the first output.
	const Graph::vertex_iterator first = out.begin();
	Process* to_process = m_vec_to_process.find(*first)->second;

	//If the next process is also done, recursively call this function.
	if(to_process->get_status() == DONE)
	{
		move_obj_to_next(*first);
	}

	if(to_process->get_status() == WAITING)
	{
		to_process->m_cur_object = object;
		to_process->status = WORKING;
	}
	else if(to_process->get_status() == WORKING)
	{
		to_process->m_objects_waiting.push_back(object);
	}
	from_process->status = WAITING;
	from_process->m_cur_object = 0;
}
void PCCGraph::output_dot()
{
	cout << "digraph G{\n";


	for (Graph::const_iterator p = G.begin(); p != G.end(); p++)
	{
		Process* cur_process = m_vec_to_process.find(Graph::node(p))->second;
		cout << Graph::node(p) << "[label=\"" << cur_process->m_name <<"\"]; \n";
	}
	for (Graph::const_iterator p = G.begin(); p != G.end(); p++)
	{
	  if (Graph::out_neighbors(p).size() == 0  &&
		  Graph::in_neighbors(p).size() == 0)
	  {
		cout << Graph::node(p) << ";\n";
	  }
	}
	for (Graph::const_iterator p = G.begin(); p != G.end(); p++)
	{
	  const Graph::vertex_set &out = Graph::out_neighbors(p);
	  Graph::vertex from = Graph::node(p);
	  for (Graph::vertex_set::const_iterator q = out.begin();
				  q != out.end(); q++)
	  {
		   cout << from << "->" << *q << " ;\n";
	  }
	}
	cout << "}";
}
PCCGraph::~PCCGraph() {
	// TODO Auto-generated destructor stub
}

