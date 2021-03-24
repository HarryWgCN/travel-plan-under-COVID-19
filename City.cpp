#include "City.h"


City::City(std::string name_, int id_, float risk_level_)
{
	this->name = name_;
	this->id = id_;
	this->risk_level = risk_level_;
	this->path_former = NULL;
	this->path_weight_amount = 0;
	this->neighbor.clear();
}

void City::set_neighbor(City *a)
{
	this->neighbor.push_back(a);
}

void City::set_path_former(City *a)
{
	this->path_former = a;
}

void City::set_path_weight_amount(float a)
{
	this->path_weight_amount = a;
}

void City::set_trans_former(TRANSPORT trans_former_)
{
	this->trans_former = trans_former_;
}

void City::set_depar_time(int depar_time_)
{
	this->depar_time = depar_time_;
}

void City::set_time_amount(int time_amount_)
{
	this->time_amount = time_amount_;
}

std::string City::get_name()const
{
	return this->name;
}

int City::get_id()const
{
	return this->id;
}

float City::get_level()const
{
	return this->risk_level;
}

City* City::get_path_former()const
{
	return this->path_former;
}

float City::get_path_weight_amount()const
{
	return this->path_weight_amount;
}

TRANSPORT City::get_trans_former()const
{
	return this->trans_former;
}

int City::get_depar_time()const
{
	return this->depar_time;
}

std::vector<City*> City::get_neighbor()const
{
	return this->neighbor;
}

int City::get_time_amount()const
{
	return this->time_amount;
}