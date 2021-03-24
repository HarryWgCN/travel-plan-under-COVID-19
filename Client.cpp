#include "Client.h"

Client::Client(std::string name_, int id_, City* departure_, City* destination_, PREFERENCE pre_)
{
	this->name = name_;
	this->id = id_;
	this->departure = departure_;
	this->destination = destination_;
	this->pre = pre_;
	this->location  = 0;
	this->state = CLIENT_STATE::waiting;
	this->plan.clear();
	this->x = graph_location_x[this->departure->get_id()];
	this->y = graph_location_y[this->departure->get_id()];
}

void Client::set_state()
{
	this->location++;
	this->state = this->plan[location].get_state();
	this->x = graph_location_x[this->plan[this->get_location()].get_location()->get_id()];
	this->y = graph_location_y[this->plan[this->get_location()].get_location()->get_id()];
}

void Client::set_x(int x_)
{
	this->x = x_;
}

void Client::set_y(int y_)
{
	this->y = y_;
}

std::string Client::get_name()const
{
	return this->name;
}

int Client::get_id()const
{
	return this->id;
}

City* Client::get_departure()const
{
	return this->departure;
}

City* Client::get_destination()const
{
	return this->destination;
}

PREFERENCE Client::get_pre()const
{
	return this->pre;
}

int Client::get_location()const
{
	return this->location;
}

float Client::get_risk_amount()const
{
	return this->plan[this->get_location()].get_risk_amount();
}

CLIENT_STATE Client::get_state()const
{
	return this->state;
}

int Client::get_x()const
{
	return this->x;
}

int Client::get_y()const
{
	return this->y;
}