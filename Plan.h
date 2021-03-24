#pragma once
#include"Client.h"

class Plan
{//�׶��Լƻ���һ��Plan������ÿ͵������ƻ�
private:
	int start;//�ƻ���ʼʱ��
	int end;//�ƻ�����ʱ��
	CLIENT_STATE state;//�ƻ�
	City* loaction;//�ƻ�����ʱ��λ��
	int time_amount;//�ۼ�ʱ��
	float risk_amount;//�ۻ�����
public:
	Plan() = default;
	Plan(int start_, int end_, CLIENT_STATE state_, City* location_, int time_amount_, float risk_amount_);//��ʼ��
	void set_start(int start_);
	void set_end(int end_);
	void set_state(CLIENT_STATE state_);
	void set_location(City* location_);
	void set_time_amount(int time_amount_);
	void set_risk_amount(float risk_amount_);//���üƻ���Ϣ
	int get_start()const;
	int get_end()const;
	CLIENT_STATE get_state()const;
	City* get_location()const;
	int get_time_amount()const;
	float get_risk_amount()const;//��ȡ�ƻ���Ϣ
};

