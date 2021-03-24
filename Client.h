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
	std::string name;//�ÿ�����
	int id;//���
	City* departure;//������
	City* destination;//Ŀ�ĵ�
	PREFERENCE pre;//����ѡ��
	int location;//ָ��ǰ�ص���plan�е�λ��
	int x;//��ǰxλ��
	int y;//��ǰyλ��
	CLIENT_STATE state;//��ǰ״̬	
public:	
	std::vector<Plan> plan;//���мƻ����ж���
	TRANSPORT trans[MAX_CITY][MAX_CITY];//���мƻ���ͨ��ʽ���У���ʾѡ�õĽ�ͨ��ʽ
	Client(std::string name_, int id_, City *departure_, City *destination_, PREFERENCE pre_);
	void set_state();//�����Ͻ�ͨ���߻�ִ���У��ı�״̬�����ǵִ���У���location++
	void set_x(int x_);
	void set_y(int y_);//������;�иı��ͼ������λ��
	std::string get_name()const;
	int get_id()const;
	City* get_departure()const;
	City* get_destination()const;
	PREFERENCE get_pre()const;
	int get_location()const;
	CLIENT_STATE get_state()const;
	float get_risk_amount()const;
	int get_x()const;
	int get_y()const;//��ȡ�ÿ���Ϣ
};

