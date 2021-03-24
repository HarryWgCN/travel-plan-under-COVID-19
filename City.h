#pragma once
#include<iostream>
#include<vector>
#include"header.h"

class City
{
private:
	std::string name;//��������
	int id;//���б��
	float risk_level;//���յȼ�
	std::vector<City*> neighbor;//�ٽ���м���
	int time_amount;
	City* path_former;
	float path_weight_amount;
	TRANSPORT trans_former;
	int depar_time;//��¼���·����Ԫ�飬ǰһ�����У��ۼ�Ȩֵ���������еĽ�ͨ���ߣ������������ʱ��
public:
	City(std::string name_, int id, float risk_level_);
	std::string get_name()const;
	void set_neighbor(City *a);
	void set_path_former(City *a);
	void set_path_weight_amount(float a);
	void set_trans_former(TRANSPORT trans_former_);
	void set_depar_time(int depar_time_);
	void set_time_amount(int time_amount_);//���ó�����Ϣ
	float get_level()const;
	int get_id()const;
	std::vector<City*> get_neighbor()const;
	City* get_path_former()const;
	float get_path_weight_amount()const;
	TRANSPORT get_trans_former()const;
	int get_depar_time()const;
	int get_time_amount()const;//��ȡ������Ϣ
};

