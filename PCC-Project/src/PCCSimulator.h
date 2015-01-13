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
	void step();
	virtual ~PCCSimulator();
	PCCGraph* graph;
private:
	void process_step(unsigned int cur_idx);
	void finalize_step(unsigned int cur_idx);

	double m_discretization;
};

#endif /* PCCSIMULATOR_H_ */
