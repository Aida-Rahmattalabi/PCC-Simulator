/*
 * PCCSimulator.h
 *
 *  Created on: Dec 30, 2014
 *      Author: will
 */

#ifndef PCCSIMULATOR_H_
#define PCCSIMULATOR_H_

#include <string.h>
#include "PCCGraph.h"



class PCCSimulator {
public:
	PCCSimulator();
	void run_simulation(unsigned int timesteps, unsigned int object_generation_rate);
	void set_discretization(double discretization);
	virtual ~PCCSimulator();
	PCCGraph* graph;
	int cur_step;
	unsigned int m_object_generation_rate;
private:
	void step();
	void process_step(unsigned int cur_idx);
	void finalize_step(unsigned int cur_idx);
	double m_discretization;
};

#endif /* PCCSIMULATOR_H_ */
