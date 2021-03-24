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
	void add_car(int time);//�������ʱ��
	void add_railway(int time);//�����·ʱ��
	void add_flight(int time);//��ӷɻ�ʱ��
	float get_low_risk_trans(int distance, int now, TRANSPORT& tran, float depar_risk, int& depar_time);//��ȡ��ǰ·�����ܵ���ͷ���Ȩֵ
	int get_short_time_trans(int distance, int now, TRANSPORT& tran, float depar_risk, int& depar_time);//��ȡ��ǰ·�����ܵ����ʱ��Ȩֵ
};
