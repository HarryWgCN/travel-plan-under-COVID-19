#pragma once
#include<vector>
#include"header.h"
class Transport
{
private:
	std::vector<int> car;
	std::vector<int> railway;
	std::vector<int> flight;
public:
	Transport();
	void add_car(int time);//添加汽车时间
	void add_railway(int time);//添加铁路时间
	void add_flight(int time);//添加飞机时间
	float get_low_risk_trans(int distance, int now, TRANSPORT& tran, float depar_risk, int& depar_time);//获取当前路径可能的最低风险权值
	int get_short_time_trans(int distance, int now, TRANSPORT& tran, float depar_risk, int& depar_time);//获取当前路径可能的最短时间权值
};
