#include "Plan.h"
Plan::Plan(int start_, int end_, CLIENT_STATE state_, City* location_, int time_amount_, float risk_amount_)
{
	this->start = start_;
	this->end = end_;
	this->state = state_;
	this->loaction = location_;
	this->time_amount = time_amount_;
	this->risk_amount = risk_amount_;
}

void Plan::set_start(int start_)
{
	this->start = start_;
}

void Plan::set_end(int end_)
{
	this->end = end_;
}

void Plan::set_state(CLIENT_STATE state_)
{
	this->state = state_;
}

void Plan::set_location(City* location_)
{
	this->loaction = location_;
}

void Plan::set_time_amount(int time_amount_)
{
	this->time_amount = time_amount_;
}

void Plan::set_risk_amount(float risk_amount_)
{
	this->risk_amount = risk_amount_;
}

int Plan::get_start()const
{
	return this->start;
}

int Plan::get_end()const
{
	return this->end;
}

CLIENT_STATE Plan::get_state()const
{
	return this->state;
}

City* Plan::get_location()const
{
	return this->loaction;
}

int Plan::get_time_amount()const
{
	return this->time_amount;
}

float Plan::get_risk_amount()const
{
	return this->risk_amount;
}