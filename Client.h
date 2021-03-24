#pragma once
#include<iostream>
#include<vector>
#include"header.h"
#include"City.h"
#include"Plan.h"
class Plan;

class Client
{
private:
	std::string name;//旅客姓名
	int id;//编号
	City* departure;//出发地
	City* destination;//目的地
	PREFERENCE pre;//策略选择
	int location;//指向当前地点在plan中的位置
	int x;//当前x位置
	int y;//当前y位置
	CLIENT_STATE state;//当前状态	
public:	
	std::vector<Plan> plan;//旅行计划城市队列
	TRANSPORT trans[MAX_CITY][MAX_CITY];//旅行计划交通方式队列，表示选用的交通方式
	Client(std::string name_, int id_, City *departure_, City *destination_, PREFERENCE pre_);
	void set_state();//当做上交通工具或抵达城市，改变状态，若是抵达城市，则location++
	void set_x(int x_);
	void set_y(int y_);//在旅行途中改变地图上坐标位置
	std::string get_name()const;
	int get_id()const;
	City* get_departure()const;
	City* get_destination()const;
	PREFERENCE get_pre()const;
	int get_location()const;
	CLIENT_STATE get_state()const;
	float get_risk_amount()const;
	int get_x()const;
	int get_y()const;//获取旅客信息
};

