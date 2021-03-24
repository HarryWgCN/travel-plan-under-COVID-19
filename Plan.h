#pragma once
#include"Client.h"

class Plan
{//阶段性计划，一组Plan类组成旅客的完整计划
private:
	int start;//计划开始时间
	int end;//计划结束时间
	CLIENT_STATE state;//计划
	City* loaction;//计划进行时的位置
	int time_amount;//累计时间
	float risk_amount;//累积风险
public:
	Plan() = default;
	Plan(int start_, int end_, CLIENT_STATE state_, City* location_, int time_amount_, float risk_amount_);//初始化
	void set_start(int start_);
	void set_end(int end_);
	void set_state(CLIENT_STATE state_);
	void set_location(City* location_);
	void set_time_amount(int time_amount_);
	void set_risk_amount(float risk_amount_);//设置计划信息
	int get_start()const;
	int get_end()const;
	CLIENT_STATE get_state()const;
	City* get_location()const;
	int get_time_amount()const;
	float get_risk_amount()const;//获取计划信息
};

