#include "Transport.h"
#include"header.h"
Transport::Transport()
{
	this->car.clear();
	this->flight.clear();
	this->railway.clear();
}

void Transport::add_car(int time)
{
	this->car.push_back(time);
}
void Transport::add_railway(int time)
{
	this->railway.push_back(time);
}
void Transport::add_flight(int time)
{
	this->flight.push_back(time);
}

float Transport::get_low_risk_trans(int dis, int now, TRANSPORT& tran, float depar_risk, int& depar_time)
{
	float min;
	int min_temp = now - 1;
	//ǰ��Ϊ���ֽ�ͨ���߱Ƚϵ���Сֵ�����ֽ�ͨ������Ȩֵ��С�ģ�������Ϊ��ͨ���������������ͬ�ֽ�ͨ����������ģ�
	for (auto i = this->car.begin(); i != this->car.end(); ++i)
	{
		if (((*i - now + MAX_TIME) % MAX_TIME) < (min_temp - now + MAX_TIME) % MAX_TIME)
		{
			min_temp = *i;
		}
	}
	depar_time = min_temp;
	min = ((dis * CAR_RISK * depar_risk) / CAR_SPEED) + (((min_temp - now + MAX_TIME) % MAX_TIME) * depar_risk);
	tran = TRANSPORT::car;
	//·;�����ۼƺ͵ȴ������ۻ�
	min_temp = now - 1;
	for (auto i = this->railway.begin(); i != this->railway.end(); ++i)
	{
		if (((*i - now + MAX_TIME) % MAX_TIME) < (min_temp - now + MAX_TIME) % MAX_TIME)
		{
			min_temp = *i;
		}
	}
	if (((dis * RAILWAY_RISK * depar_risk) / RAILWAY_SPEED) + (((min_temp - now + MAX_TIME) % MAX_TIME) * depar_risk) < min)
	{
		min = ((dis * RAILWAY_RISK * depar_risk) / RAILWAY_SPEED) + (((min_temp - now + MAX_TIME) % MAX_TIME) * depar_risk);
		tran = TRANSPORT::railway;
		depar_time = min_temp;
	}
	min_temp = now - 1;
	//�Ƚ�railway 
	for (auto i = this->flight.begin(); i != this->flight.end(); ++i)
	{
		if (((*i - now + MAX_TIME) % MAX_TIME) < (min_temp - now + MAX_TIME) % MAX_TIME)
		{
			min_temp = *i;
		}
	}
	if (((dis * FLIGHT_RISK * depar_risk) / FLIGHT_SPEED) + (((min_temp - now + MAX_TIME) % MAX_TIME) * depar_risk) < min)
	{
		min = ((dis * FLIGHT_RISK * depar_risk) / FLIGHT_SPEED) + (((min_temp - now + MAX_TIME) % MAX_TIME) * depar_risk);
		tran = TRANSPORT::flight;
		depar_time = min_temp;
	}
	//�Ƚ�flight
	return min;
}

int Transport::get_short_time_trans(int dis, int now, TRANSPORT& tran, float depar_risk, int& depar_time)
{
	int min;
	
	int min_temp = now - 1;
	//ǰ��Ϊ���ֽ�ͨ���߱Ƚϵ���Сֵ�����ֽ�ͨ������Ȩֵ��С�ģ�������Ϊ��ͨ��������̣�����ͬ�ֽ�ͨ����������ģ�
	for (auto i = this->car.begin(); i != this->car.end(); ++i)
	{
		if (((*i - now + MAX_TIME) % MAX_TIME) < (min_temp - now + MAX_TIME) % MAX_TIME)
		{
			min_temp = *i;
		}
	}
	depar_time = min_temp;
	min = (dis / CAR_SPEED) + ((min_temp - now + MAX_TIME) % MAX_TIME);
	tran = TRANSPORT::car;
	//·;ʱ���ۼƺ͵ȴ�ʱ���ۻ�
	min_temp = now - 1;
	for (auto i = this->railway.begin(); i != this->railway.end(); ++i)
	{
		if (((*i - now + MAX_TIME) % MAX_TIME) < (min_temp - now + MAX_TIME) % MAX_TIME)
		{
			min_temp = *i;
		}
	}
	if ((dis / RAILWAY_SPEED) + ((min_temp - now + MAX_TIME) % MAX_TIME) < min)
	{
		min = (dis / RAILWAY_SPEED) + ((min_temp - now + MAX_TIME) % MAX_TIME);
		tran = TRANSPORT::railway;
		depar_time = min_temp;
	}
	min_temp = now - 1;
	//�Ƚ�railway
	for (auto i = this->flight.begin(); i != this->flight.end(); ++i)
	{
		if (((*i - now + MAX_TIME) % MAX_TIME) < (min_temp - now + MAX_TIME) % MAX_TIME)
		{
			min_temp = *i;
		}
	}
	if ((dis / FLIGHT_SPEED) + ((min_temp - now + MAX_TIME) % MAX_TIME) < min)
	{
		min = (dis / FLIGHT_SPEED) + ((min_temp - now + MAX_TIME) % MAX_TIME);
		tran = TRANSPORT::flight;
		depar_time = min_temp;
	}
	//�Ƚ�flight
	return min;
}