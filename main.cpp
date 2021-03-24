#include"header.h"
#include"City.h"
#include"Client.h"
#include"Plan.h"

int now_time = 0;//����ʱ��
void update_clients();
void out_clients();//��������û���Ϣ
void out_clients(Client* client);//���ָ���û���Ϣ
std::string to_string(PREFERENCE pre);//�ַ���ת������
std::string to_string(CLIENT_STATE state);//�ַ���ת������
std::string to_string(TRANSPORT trans);//�ַ���ת������
void set_pictures();//ͼ�λ����汳��
std::vector<Client> clients;//�ÿͼ���
bool pause = false;//ʱ����ͣ������ʶ
 
int main()
{	
	initgraph(GRAPH_WIDTH, GRAPH_HEIGHT, EW_SHOWCONSOLE);//��ʼ��ͼ�λ�����
	init_travel();//��ʼ��������Ϣ
	std::thread keyboard(wait_for_keyboard);
	std::thread mouse(wait_for_mouse);
	set_pictures();//������������ͼ��ʶ
	/*for (;;)
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if(m.mkLButton)
			std::cout << m.x << " " << m.y << std::endl;
	}*/
    for (;;)
	{//ÿʱ������ǰ�ƽ�1Сʱ
		//�����Ϣ
		std::cout << "@@@@@@@@@@@   now_time : " << now_time << "   @@@@@@@@@@@" << std::endl << std::endl;
		fs << "@@@@@@@@@@@   now_time : " << now_time << "   @@@@@@@@@@@" << std::endl << std::endl;
		set_pictures();
		BeginBatchDraw();//ƽ����ͼ
		IMAGE* now;
		IMAGE* now_cover;
		for (int i = 0; i < TIME_DIVIDE; ++i)
		{//��ͼ
			while (pause == true);
			set_pictures();
			setfillcolor(RGB(255, 180, 0));
			now_cover = &waiting_image_cover;
			for (auto j = clients.begin(); j != clients.end(); ++j)
			{//��ÿ���ÿ�ִ�в���
				int depar_x, desti_x, depar_y, desti_y, period;
				std::string str = j->get_name();
				if (j->get_state() != CLIENT_STATE::waiting)
				{//�����ÿ�״̬��Ϣ
					switch (j->get_state())
					{//ͼ��ѡ��
					case CLIENT_STATE::on_road:now = &road_image; now_cover = &road_image_cover; break;
					case CLIENT_STATE::on_rail:now = &railway_image; now_cover = &railway_image_cover; break;
					case CLIENT_STATE::on_flight:now = &flight_image; now_cover = &flight_image_cover; break;
					default:now = &waiting_image; now_cover = &waiting_image_cover;
					}
					depar_x = j->get_x();
					depar_y = j->get_y();
					desti_x = graph_location_x[j->plan[j->get_location() + 1].get_location()->get_id()];
					desti_y = graph_location_y[j->plan[j->get_location() + 1].get_location()->get_id()];//��ͼλ��ȷ��
					period = (j->plan[j->get_location()].get_end() - now_time + MAX_TIME) % MAX_TIME;
					char s[50];
					if (period == 0)
					{
						period++;
					}
					strcpy_s(s, str.c_str());
					settextcolor(NAME_COLOR); 
					settextstyle(CITY_NAME_HEIGHT, 0, _T("Consolas"), 0, 0, 0, 0, 0, 0);//�趨����
					//�����ÿ�
					outtextxy(depar_x + i * (((desti_x - depar_x) / period) / TIME_DIVIDE), depar_y + i * (((desti_y - depar_y) / period) / TIME_DIVIDE) - BUTTON_HEIGHT, s);
					putimage(depar_x + i * (((desti_x - depar_x) / period) / TIME_DIVIDE), depar_y + i * (((desti_y - depar_y) / period) / TIME_DIVIDE), now_cover, SRCPAINT);
					putimage(depar_x + i * (((desti_x - depar_x) / period) / TIME_DIVIDE), depar_y + i * (((desti_y - depar_y) / period) / TIME_DIVIDE), now, SRCAND);
					j->set_x(depar_x + i * (((desti_x - depar_x) / period) / TIME_DIVIDE));
					j->set_y(depar_y + i * (((desti_y - depar_y) / period) / TIME_DIVIDE));
				}
				else
				{
					if (j->plan[j->get_location()].get_end() == -1)
					{//ͼ��ѡ��
						now = &terminate_image;
						now_cover = &terminate_image_cover;
						str += " time : ";
						str += std::to_string(j->plan[j->get_location()].get_time_amount());
						str += " risk : ";
						str += std::to_string(j->plan[j->get_location()].get_risk_amount());
					}
					else
					{
						now = &waiting_image;
						now_cover = &waiting_image_cover;
					}
					char s[60];					
					strcpy_s(s, str.c_str());
					settextcolor(NAME_COLOR);
					settextstyle(CITY_NAME_HEIGHT, 0, _T("Consolas"), 0, 0, 0, 0, 0, 0);//�趨����
					//�����ÿ�
					outtextxy(graph_location_x[j->plan[j->get_location()].get_location()->get_id()], graph_location_y[j->plan[j->get_location()].get_location()->get_id()] - BUTTON_HEIGHT, s);
					putimage(graph_location_x[j->plan[j->get_location()].get_location()->get_id()], graph_location_y[j->plan[j->get_location()].get_location()->get_id()], now_cover, SRCPAINT);
					putimage(graph_location_x[j->plan[j->get_location()].get_location()->get_id()], graph_location_y[j->plan[j->get_location()].get_location()->get_id()], now, SRCAND);
				}
			}
			//fillcircle(0 + i * (TIME_INTERVAL / TIME_DIVIDE), 0 + i * (TIME_INTERVAL / TIME_DIVIDE), 10);
			Sleep(TIME_INTERVAL / TIME_DIVIDE);
			FlushBatchDraw();//ƽ����ͼ
		}//���ӳ�5000ms
		update_clients();//�����ÿ���Ϣ
		out_clients();//����ÿ���Ϣ
		now_time = (now_time + 1) % MAX_TIME;//ʱ������
	}
	fs.close();//�ر��ļ�
	system("pause");
	return 0;
}

void update_clients()
{
	for (auto i = clients.begin(); i != clients.end(); ++i)
	{
		int start, end;
		start = i->plan[i->get_location()].get_start();
		end = i->plan[i->get_location()].get_end();
		if ((start <= now_time && now_time < end) || (start <= now_time && end < start) || (now_time < end && end < start) || end == -1)
		{
			//���ڵ�ǰ�ƻ��׶�֮�У�����ʱ�䷶Χ���+end == -1���ִ��յ���У�
			//����������ĳ���һ��ĵȴ�ʱ���ͨʱ�䣬��˿���������������������������ֻ��ڴ˼ƻ��׶�֮�г���start<end<now_time
		}
		else
		{
			i->set_state();
		}
		
	}
}

void out_clients()
{
	//���������
	if (clients.empty())
		return;
	std::cout << "These are the clients" << std::endl;
	std::cout << "������������������������������������������������������������������������������������������������������������������" << std::endl;
	for (auto i = clients.begin(); i != clients.end(); ++i)
	{
		std::cout << (*i).get_name() << " ";
		std::cout << "id : " << (*i).get_id() << " ";
		std::cout << "Location : " << i->plan[i->get_location()].get_location()->get_name();
		std::cout << "  State : " << to_string(i->plan[i->get_location()].get_state()) << std::endl;
		std::cout << "  Time_amount so far : " << i->plan[i->get_location()].get_time_amount() << std::endl;
		std::cout << "  Risk_amount so far : " << i->get_risk_amount() << std::endl;
		std::cout << "Plan of trip: " << std::endl;
		for (auto j = (*i).plan.begin(); j != (*i).plan.end(); ++j)
		{
			std::cout << "location : " << j->get_location()->get_name() << " ";
			std::cout << "||start_time : " << j->get_start() << " ||state : " << to_string(j->get_state()) << " ||end_time : " << j->get_end() << std::endl;
		}
		std::cout << std::endl;
	}
	//��־�ļ����
	if(!clients.empty())
		fs << R"(\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\)" << std::endl << std::endl;
	fs << "These are the clients" << std::endl;
	fs << "������������������������������������������������������������������������������������������������������������������" << std::endl;
	for (auto i = clients.begin(); i != clients.end(); ++i)
	{
		fs << (*i).get_name() << " ";
		fs << "id : " << (*i).get_id() << " ";
		fs << "Location : " << i->plan[i->get_location()].get_location()->get_name();
		fs << "  State : " << to_string(i->plan[i->get_location()].get_state()) << std::endl;
		fs << "  Time_amount so far : " << i->plan[i->get_location()].get_time_amount() << std::endl;
		fs << "  Risk_amount so far : " << i->get_risk_amount() << std::endl;
		fs << "Plan of trip: "  << std::endl;
		for (auto j = (*i).plan.begin(); j != (*i).plan.end(); ++j)
		{
			fs << "location : " << j->get_location()->get_name() << " ";
			fs << "||start_time : " << j->get_start() << " ||state : " << to_string(j->get_state()) << " ||end_time : " << j->get_end() << std::endl;
		}
		fs << std::endl;
	}
	if (!clients.empty())
		fs << R"(\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\)" << std::endl << std::endl;
}

void out_clients(Client* client)
{
	//���������
	std::cout << "Client inquiry received " << std::endl;
	std::cout << "This is client "<< std::endl;
	std::cout << "������������������������������������������������������������������������������������������������������������������" << std::endl;
	std::cout << "id : " << (*client).get_id() << " ";
	std::cout << "Location : " << client->plan[client->get_location()].get_location()->get_name();
	std::cout << "  Time_amount so far : " << client->plan[client->get_location()].get_time_amount() << std::endl;
	std::cout << "  State : " << to_string(client->plan[client->get_location()].get_state()) << std::endl;
	std::cout << "  Risk_amount so far : " << client->get_risk_amount() << std::endl;
	std::cout << "Plan of trip:  "  << std::endl;
	for (auto j = client->plan.begin(); j != client->plan.end(); ++j)
	{
		std::cout << "location : " << j->get_location()->get_name() << " ";
		std::cout << "||start_time : " << j->get_start() << " ||state : " << to_string(j->get_state()) << " ||end_time : " << j->get_end() << std::endl;
	}
	std::cout << std::endl;
	std::cout << R"(\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\)" << std::endl << std::endl;
	//��־�ļ����
	fs << "Client inquiry received " << std::endl;
	fs << "This is client " << std::endl;
	fs << "������������������������������������������������������������������������������������������������������������������" << std::endl;
	fs << "id : " << (*client).get_id() << " ";
	fs << "Location : " << client->plan[client->get_location()].get_location()->get_name();
	fs << "  Time_amount so far : " << client->plan[client->get_location()].get_time_amount() << std::endl;
	fs << "  State : " << to_string(client->plan[client->get_location()].get_state()) << std::endl;
	fs << "  Risk_amount so far : " << client->get_risk_amount() << std::endl;
	fs << "Plan of trip:  " << std::endl;
	for (auto j = client->plan.begin(); j != client->plan.end(); ++j)
	{
		fs << "location : " << j->get_location()->get_name() << " ";
		fs << "||start_time : " << j->get_start() << " ||state : " << to_string(j->get_state()) << " ||end_time : " << j->get_end() << std::endl;
	}
	fs << std::endl;
	fs << R"(\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\)" << std::endl << std::endl;
}

std::string to_string(PREFERENCE pre)
{
	switch (pre)
	{
	case PREFERENCE::LOW_RISK:return "LOW_RISK"; break;
	case PREFERENCE::SHORT_TIME:return "SHORT_TIME"; break;
	default:return "NO PREFERENCE";
	}
}

std::string to_string(CLIENT_STATE state)
{
	switch (state)
	{
	case CLIENT_STATE::on_road:return "on_road"; break;
	case CLIENT_STATE::on_rail:return "on_rail"; break;
	case CLIENT_STATE::on_flight:return "on_flight"; break;
	case CLIENT_STATE::waiting:return "waiting"; break;
	default:return "NO STATE";
	}
}

std::string to_string(TRANSPORT trans)
{
	switch (trans)
	{
	case TRANSPORT::car:return "car"; break;
	case TRANSPORT::railway:return "railway"; break;
	case TRANSPORT::flight:return "flight"; break;
	default:return "NO STATE";
	}
}