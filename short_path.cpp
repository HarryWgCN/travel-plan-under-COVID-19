#include"header.h"
#include"City.h"
#include"Client.h"
#include"Transport.h"

class City;

void set_plan(Client* client, City* depar, City* desti);
void time_limit_adjust(Client* client, City* depar, City* desti, int time_limit, bool* s, std::vector<City*> n);

void short_path(Client* client, City *depar, City *desti, PREFERENCE pre, int time_limit)
{
	std::vector<City*> n;//�Լ������·���ĳ��м��ϣ��ڹ��������
	n.clear(); 
	bool s[MAX_CITY];//��¼�����Ƿ񱻷�����·��
	for (int i = 0; i < MAX_CITY; i++)
	{//��ʼ��ÿ������Ϊδ����
		s[i] = false;
	}
	n.push_back(depar);//�Ƚ������س��м��뼯��
	s[depar->get_id()] = true;//�����س��б�ʶΪ�ѷ���
	while(!s[desti->get_id()])
	{//ֱ��Ŀ�ĳ��б�����
		float minw = MAX_WEIGHT + 1;//��СȨ��
		City* minc = NULL;//��СȨ�ض�Ӧ�������
		TRANSPORT tran_temp;//��¼��СȨֵ��Ӧ�Ľ�ͨ����
		TRANSPORT tran;//��¼�������յ���СȨֵ���ý�ͨ����
		int depar_time_temp;//��¼����Ȩֵ���ý�ͨ���߳���ʱ��
		int depar_time;//��¼����������СȨֵ���ý�ͨ���߳���ʱ��
		float weight;//Ȩֵ
		for (auto i = n.begin(); i != n.end(); ++i)
		{//�����ѷ���·������
			std::vector<City*> c((*i)->get_neighbor());
			for (auto j = c.begin(); j != c.end(); ++j)
			{//�����ѷ�����·�����е��ڽӳ���,Ѱ��·��Ȩ��+��һ�����ۼ�Ȩ��ֵ��С�ĳ���
				weight = transport[(*i)->get_id()][(*j)->get_id()].get_low_risk_trans(distance[(*i)->get_id()][(*j)->get_id()], now_time, tran_temp, (*i)->get_level(), depar_time_temp);
				if (s[(*j)->get_id()] != true && weight + (*i)->get_path_weight_amount() < minw)
				{//��δ����ĳ������ҵ���СȨֵ·��
					minw = weight;
					minc = *j;
					tran = tran_temp;
					depar_time = depar_time_temp;
					(*j)->set_path_weight_amount(weight + (*i)->get_path_weight_amount());//��¼�ۼ�Ȩֵ
					(*j)->set_path_former(*i);//�����γ����мƻ�ʱ����ʶÿ��;�����е�ǰһ��;������
					(*j)->set_trans_former(tran);//���ڱ�ʶ����ÿ��;���������õĽ�ͨ����
					(*j)->set_depar_time(depar_time);//���ڱ�ʶ����ÿ��;���������ý�ͨ���ߵĳ���ʱ��

				} 
			}
		}
		n.push_back(minc);//���ҵ������·�����м��뵽�ѷ���·�����м���֮��
		minc->set_path_weight_amount(minc->get_path_weight_amount() + minw);//�����ۼ�Ȩ��
		s[minc->get_id()] = true;//���Ϊ�ѷ���
	}
	set_plan(client, depar, desti);
	if (pre == PREFERENCE::SHORT_TIME)
		time_limit_adjust(client, depar, desti, time_limit, s, n);//Ϊ�û�������мƻ�
}

void time_limit_adjust(Client* client, City* depar, City* desti, int time_limit, bool *s, std::vector<City*> n)
{
	for (auto i = client->plan.end() - 1; i != client->plan.begin(); i -= 2)
	{//��planĩβ��ʼ����ȥ�ƻ��ཻͨ��ʽ�ͳ��У����µ��ѷ�����м��Ͽ�ʼ
		if (desti->get_time_amount() < time_limit)
		{
			set_plan(client, depar, desti);
			return;
		}
		s[i->get_location()->get_id()] = false;
		n.pop_back();//����ǰ���һ�������Ƴ��ѷ�����м���
		while (!s[desti->get_id()])
		{//ֱ��Ŀ�ĳ��б�����
			float minw = MAX_WEIGHT + 1;//��СȨ��
			City* minc = NULL;//��СȨ�ض�Ӧ�������
			TRANSPORT tran_temp;//��¼��СȨֵ��Ӧ�Ľ�ͨ����
			TRANSPORT tran;//��¼�������յ���СȨֵ���ý�ͨ����
			int depar_time_temp;//��¼����Ȩֵ���ý�ͨ���߳���ʱ��
			int depar_time;//��¼����������СȨֵ���ý�ͨ���߳���ʱ��
			float weight;//Ȩֵ
			for (auto i = n.begin(); i != n.end(); ++i)
			{//�����ѷ���·������
				std::vector<City*> c((*i)->get_neighbor());
				for (auto j = c.begin(); j != c.end(); ++j)
				{//�����ѷ�����·�����е��ڽӳ���,Ѱ��·��Ȩ��+��һ�����ۼ�Ȩ��ֵ��С�ĳ���
					weight = static_cast<float>(transport[(*i)->get_id()][(*j)->get_id()].get_short_time_trans(distance[(*i)->get_id()][(*j)->get_id()], now_time, tran_temp, (*i)->get_level(), depar_time_temp));
					if (s[(*j)->get_id()] != true && weight + (*i)->get_path_weight_amount() < minw)
					{//��δ����ĳ������ҵ���СȨֵ·��
						minw = weight;
						minc = *j;
						tran = tran_temp;
						depar_time = depar_time_temp;
						(*j)->set_path_weight_amount(weight + (*i)->get_path_weight_amount());//��¼�ۼ�Ȩֵ
						(*j)->set_path_former(*i);//�����γ����мƻ�ʱ����ʶÿ��;�����е�ǰһ��;������
						(*j)->set_trans_former(tran);//���ڱ�ʶ����ÿ��;���������õĽ�ͨ����
						(*j)->set_depar_time(depar_time);//���ڱ�ʶ����ÿ��;���������ý�ͨ���ߵĳ���ʱ��

					}
				}
			}
			n.push_back(minc);//���ҵ������·�����м��뵽�ѷ���·�����м���֮��
			minc->set_path_weight_amount(minc->get_path_weight_amount() + minw);//�����ۼ�Ȩ��
			s[minc->get_id()] = true;//���Ϊ�ѷ���
		}
	}
	std::cout << "Impossible time_limit!!!!!!!!!!!!!!!!!!" << std::endl;
	fs << "Impossible time_limit!!!!!!!!!!!!!!!!!!" << std::endl;
	for (int i = 0; i < 50; ++i)
	{
		outtextxy(50, 50, _T("IMPOSSIBLE"));
		Sleep(TIME_INTERVAL / 50);
	}
	clients.pop_back();
}


void set_plan(Client* client, City* depar, City* desti)
{
	City* now = desti;
	int start, end, dis,start_former = -1;//����start_formerΪ�ϸ�����Ľ�ͨ+����Plan��ϵĿ�ʼʱ�䣬Ϊ-1��ʾ�����ص���п�ʼ����
	int speed = 0, time_amount = 0;
	float risk_amount = 0;
	CLIENT_STATE state;
	client->plan.clear();
	while(now != depar)
	{//���յ���п�ʼ��Plan�е�����ӵ�����еĽ�ͨ+������ϣ����յ�ֻʣ�³�����û����ӵ�Plan��
		start = now->get_depar_time();
		switch (now->get_trans_former())
		{
		case TRANSPORT::car:speed = CAR_SPEED; state = CLIENT_STATE::on_road; break;
		case TRANSPORT::railway:speed = RAILWAY_SPEED; state = CLIENT_STATE::on_rail; break;
		case TRANSPORT::flight:speed = FLIGHT_SPEED; state = CLIENT_STATE::on_flight; break;
		default:speed = CAR_SPEED; state = CLIENT_STATE::on_road;
		}
		dis = distance[now->get_path_former()->get_id()][now->get_id()];
		end = (start + (dis / speed)) % MAX_TIME;
		client->plan.insert(client->plan.begin(), Plan(end, start_former, CLIENT_STATE::waiting, now, 0, 0));
		//�ȼӳ��мƻ�
		client->plan.insert(client->plan.begin(), Plan(start, end, state, now->get_path_former(), 0, 0));
		//�ټӵ�����еĽ�ͨ�ƻ�
		start_former = start;
		now = now->get_path_former();//����ǰһ������
	}
	client->plan.insert(client->plan.begin(), Plan(now_time, start_former, CLIENT_STATE::waiting, depar, 0, 0));//��һ�����п�ʼʱ��Ϊ��ʱʱ��
	risk_amount = 0;
	time_amount = 0;
	for (auto i = client->plan.begin(); i != client->plan.end(); ++i)
	{//�������п�ʼ��Plan��������ӵ�������ۼ�ʱ��ͷ���ֵ
		if (i->get_end() == -1)
		{
			i->get_location()->set_time_amount(time_amount);
			i->set_time_amount(time_amount);	
			i->set_risk_amount(risk_amount);
			break;
		}

		i->get_location()->set_time_amount(time_amount + ((i->get_end() - i->get_start() + MAX_TIME) % MAX_TIME));
		i->set_time_amount(time_amount + ((i->get_end() - i->get_start() + MAX_TIME) % MAX_TIME));
		time_amount += ((i->get_end() - i->get_start() + MAX_TIME) % MAX_TIME);
		switch (i->get_state())
		{
		case CLIENT_STATE::waiting:risk_amount += ((i->get_end() - i->get_start() + MAX_TIME) % MAX_TIME) * i->get_location()->get_level(); break;
		case CLIENT_STATE::on_road:risk_amount += CAR_RISK * ((i->get_end() - i->get_start() + MAX_TIME) % MAX_TIME) * i->get_location()->get_level(); break;
		case CLIENT_STATE::on_rail:risk_amount += RAILWAY_RISK * ((i->get_end() - i->get_start() + MAX_TIME) % MAX_TIME) * i->get_location()->get_level(); break;
		case CLIENT_STATE::on_flight:risk_amount += FLIGHT_RISK * ((i->get_end() - i->get_start() + MAX_TIME) % MAX_TIME) * i->get_location()->get_level(); break;
		}
		i->set_risk_amount(risk_amount);
	}
}