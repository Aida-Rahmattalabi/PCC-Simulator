/*
 * Process.h
 *
 *  Created on: Dec 16, 2014
 *      Author: will
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <string>
#include <vector>
using namespace std;

enum event {WAITING, WORKING, DONE};

class Process {
public:
	Process();

	double m_time_cost;
	double m_time_taken;
	unsigned int m_cur_object;
	vector<unsigned int> m_objects_waiting;
	string m_name;
	event status;

	event get_status();
	void execute(double discretization);
	friend bool operator<(const Process &p1, const Process &p2);
	friend bool operator==(const Process &p1, const Process &p2);
	virtual ~Process();
};

#endif /* PROCESS_H_ */
