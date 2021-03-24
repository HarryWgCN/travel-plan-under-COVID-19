#include"header.h"
#include"City.h"
#include"Client.h"
#include"Transport.h"

class City;

void set_plan(Client* client, City* depar, City* desti);
void time_limit_adjust(Client* client, City* depar, City* desti, int time_limit, bool* s, std::vector<City*> n);

void short_path(Client* client, City *depar, City *desti, PREFERENCE pre, int time_limit)
{
	std::vector<City*> n;//以计算最短路径的城市集合，在过程中添加
	n.clear(); 
	bool s[MAX_CITY];//记录城市是否被分配了路径
	for (int i = 0; i < MAX_CITY; i++)
	{//初始化每个城市为未分配
		s[i] = false;
	}
	n.push_back(depar);//先将出发地城市加入集合
	s[depar->get_id()] = true;//出发地城市标识为已分配
	while(!s[desti->get_id()])
	{//直到目的城市被分配
		float minw = MAX_WEIGHT + 1;//最小权重
		City* minc = NULL;//最小权重对应到达城市
		TRANSPORT tran_temp;//记录最小权值对应的交通工具
		TRANSPORT tran;//记录计算最终的最小权值所用交通工具
		int depar_time_temp;//记录计算权值所用交通工具出发时间
		int depar_time;//记录计算最终最小权值所用交通工具出发时间
		float weight;//权值
		for (auto i = n.begin(); i != n.end(); ++i)
		{//遍历已分配路径城市
			std::vector<City*> c((*i)->get_neighbor());
			for (auto j = c.begin(); j != c.end(); ++j)
			{//遍历已分配了路径城市的邻接城市,寻找路径权重+上一城市累计权重值最小的城市
				weight = transport[(*i)->get_id()][(*j)->get_id()].get_low_risk_trans(distance[(*i)->get_id()][(*j)->get_id()], now_time, tran_temp, (*i)->get_level(), depar_time_temp);
				if (s[(*j)->get_id()] != true && weight + (*i)->get_path_weight_amount() < minw)
				{//从未分配的城市里找到最小权值路线
					minw = weight;
					minc = *j;
					tran = tran_temp;
					depar_time = depar_time_temp;
					(*j)->set_path_weight_amount(weight + (*i)->get_path_weight_amount());//记录累计权值
					(*j)->set_path_former(*i);//用于形成旅行计划时，标识每个途径城市的前一个途径城市
					(*j)->set_trans_former(tran);//用于标识到达每个途径城市所用的交通工具
					(*j)->set_depar_time(depar_time);//用于标识到达每个途径城市所用交通工具的出发时间

				} 
			}
		}
		n.push_back(minc);//将找到的最短路径城市加入到已分配路径城市集合之中
		minc->set_path_weight_amount(minc->get_path_weight_amount() + minw);//更新累计权重
		s[minc->get_id()] = true;//标记为已分配
	}
	set_plan(client, depar, desti);
	if (pre == PREFERENCE::SHORT_TIME)
		time_limit_adjust(client, depar, desti, time_limit, s, n);//为用户添加旅行计划
}

void time_limit_adjust(Client* client, City* depar, City* desti, int time_limit, bool *s, std::vector<City*> n)
{
	for (auto i = client->plan.end() - 1; i != client->plan.begin(); i -= 2)
	{//从plan末尾开始依次去计划类交通方式和城市，以新的已分配城市集合开始
		if (desti->get_time_amount() < time_limit)
		{
			set_plan(client, depar, desti);
			return;
		}
		s[i->get_location()->get_id()] = false;
		n.pop_back();//将当前最后一个城市移出已分配城市集合
		while (!s[desti->get_id()])
		{//直到目的城市被分配
			float minw = MAX_WEIGHT + 1;//最小权重
			City* minc = NULL;//最小权重对应到达城市
			TRANSPORT tran_temp;//记录最小权值对应的交通工具
			TRANSPORT tran;//记录计算最终的最小权值所用交通工具
			int depar_time_temp;//记录计算权值所用交通工具出发时间
			int depar_time;//记录计算最终最小权值所用交通工具出发时间
			float weight;//权值
			for (auto i = n.begin(); i != n.end(); ++i)
			{//遍历已分配路径城市
				std::vector<City*> c((*i)->get_neighbor());
				for (auto j = c.begin(); j != c.end(); ++j)
				{//遍历已分配了路径城市的邻接城市,寻找路径权重+上一城市累计权重值最小的城市
					weight = static_cast<float>(transport[(*i)->get_id()][(*j)->get_id()].get_short_time_trans(distance[(*i)->get_id()][(*j)->get_id()], now_time, tran_temp, (*i)->get_level(), depar_time_temp));
					if (s[(*j)->get_id()] != true && weight + (*i)->get_path_weight_amount() < minw)
					{//从未分配的城市里找到最小权值路线
						minw = weight;
						minc = *j;
						tran = tran_temp;
						depar_time = depar_time_temp;
						(*j)->set_path_weight_amount(weight + (*i)->get_path_weight_amount());//记录累计权值
						(*j)->set_path_former(*i);//用于形成旅行计划时，标识每个途径城市的前一个途径城市
						(*j)->set_trans_former(tran);//用于标识到达每个途径城市所用的交通工具
						(*j)->set_depar_time(depar_time);//用于标识到达每个途径城市所用交通工具的出发时间

					}
				}
			}
			n.push_back(minc);//将找到的最短路径城市加入到已分配路径城市集合之中
			minc->set_path_weight_amount(minc->get_path_weight_amount() + minw);//更新累计权重
			s[minc->get_id()] = true;//标记为已分配
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
	int start, end, dis,start_former = -1;//设置start_former为上个处理的交通+城市Plan组合的开始时间，为-1表示到达重点城市开始游玩
	int speed = 0, time_amount = 0;
	float risk_amount = 0;
	CLIENT_STATE state;
	client->plan.clear();
	while(now != depar)
	{//从终点城市开始向Plan中倒叙添加到达城市的交通+城市组合，最终到只剩下出发点没有添加到Plan中
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
		//先加城市计划
		client->plan.insert(client->plan.begin(), Plan(start, end, state, now->get_path_former(), 0, 0));
		//再加到达城市的交通计划
		start_former = start;
		now = now->get_path_former();//处理前一个城市
	}
	client->plan.insert(client->plan.begin(), Plan(now_time, start_former, CLIENT_STATE::waiting, depar, 0, 0));//第一个城市开始时间为此时时间
	risk_amount = 0;
	time_amount = 0;
	for (auto i = client->plan.begin(); i != client->plan.end(); ++i)
	{//从起点城市开始向Plan中正序添加到达城市累计时间和风险值
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