/*
 * Process.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: will
 */

#include "Process.h"

Process::Process() {
	status = WAITING;
	m_cur_object = -1;

}
event Process::get_status()
{
	return status;
}

void Process::execute(double discretization)
{
	if(status == WAITING && m_objects_waiting.size() != 0)
	{
		status = WORKING;
		m_cur_object = m_objects_waiting[0];
		m_objects_waiting.erase(m_objects_waiting.begin());
		return;
	}
	else if(status == WAITING) return;

	m_time_taken += discretization;
	if(m_time_taken > m_time_cost)
	{
		status = DONE;
	}
}
bool operator<(const Process &p1, const Process &p2)
{
	if (p1.m_time_cost < p2.m_time_cost) return true;
	return false;
}

bool operator==(const Process &p1, const Process &p2)
{
	if (p1.m_time_cost == p2.m_time_cost) return true;
	return false;
}

Process::~Process() {
	// TODO Auto-generated destructor stub
}

