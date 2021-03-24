#pragma once
#include<iostream>
#include<vector>
#include"header.h"

class City
{
private:
	std::string name;//城市名称
	int id;//城市编号
	float risk_level;//风险等级
	std::vector<City*> neighbor;//临界城市集合
	int time_amount;
	City* path_former;
	float path_weight_amount;
	TRANSPORT trans_former;
	int depar_time;//记录最短路径四元组，前一个城市，累计权值，来到城市的交通工具，出发来这里的时间
public:
	City(std::string name_, int id, float risk_level_);
	std::string get_name()const;
	void set_neighbor(City *a);
	void set_path_former(City *a);
	void set_path_weight_amount(float a);
	void set_trans_former(TRANSPORT trans_former_);
	void set_depar_time(int depar_time_);
	void set_time_amount(int time_amount_);//设置城市信息
	float get_level()const;
	int get_id()const;
	std::vector<City*> get_neighbor()const;
	City* get_path_former()const;
	float get_path_weight_amount()const;
	TRANSPORT get_trans_former()const;
	int get_depar_time()const;
	int get_time_amount()const;//获取城市信息
};

