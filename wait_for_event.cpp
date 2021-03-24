#include"header.h"
#include"Client.h"


void add_client();
void add_client(std::string name, int depar_id, int desti_id, int pre, int time_limit);

void wait_for_keyboard()
{
	for (;;)
	{
		char mode;
		int id;
		std::cin >> mode;
		pause = true;
		switch (mode)
		{
		case 'i'://输入i，添加用户，输入用户信息，屏幕上出现系统分配的添加的用户的id
			fs << "user typed i to add client" << std::endl;
			add_client();
			break;
		case 'o'://输入o，开始输出所有用户信息
			fs << "user typed o to show clients' information" << std::endl;
			out_clients();
			break;
		case 's'://输入s，输入查询用户的id，输出指定用户的信息
			std::cin >> id;
			fs << "user typed s to show client " << id << " 's information" << std::endl;
			if (id >= static_cast<int>(clients.size()))
			{
				std::cout << "ERROR!! client id is out of range" << std::endl;
				fs << "ERROR!! client id is out of range" << std::endl;
				break;
			}
			out_clients(&clients[id]); break;
		}
		pause = false;
	}
}

void wait_for_mouse()
{//鼠标按ADD按钮,指示闪烁五下后输入
	for (;;)
	{
		MOUSEMSG mouse;
		if (MouseHit() && GetMouseMsg().mkLButton)
		{//有鼠标按下时间
			mouse = GetMouseMsg();
			if (mouse.x <= ADD_BUTTON_X + BUTTON_WIDTH && mouse.x >= ADD_BUTTON_X && mouse.y >= ADD_BUTTON_Y && mouse.y <= ADD_BUTTON_Y + BUTTON_HEIGHT)
			{//如果是在ADD按钮内，执行操作
				pause = true;
				fs << "user pressed ADD button to add client" << std::endl;
				{
					char s[20];
					bool not_add = false;
					int depar, desti, pre, time_limit = 0;
					std::string str;
					setbkmode(TRANSPARENT);
					settextcolor(INFO_COLOR);
					settextstyle(CITY_NAME_HEIGHT, 0, _T("Consolas"), 0, 0, 0, 0, 0, 0);//设定字体
					for (int i = 0; i < 10; ++i)
					{
						outtextxy(50, 50, _T("Add CLient"));
						Sleep(TIME_INTERVAL / 50);
					}
					//读入输入框的内容
					if (InputBox(s, 20, NULL, _T("Name"), NULL, BUTTON_HEIGHT, BUTTON_WIDTH, false) == false)
						not_add = true;
					str += s;
					if (InputBox(s, 20, NULL, _T("Departure id"), NULL, BUTTON_HEIGHT, BUTTON_WIDTH, false) == false)
						not_add = true;
					if (s[1] != '\0')
						depar = ((s[0] - 48) * 10) + s[1] - 48;
					else
						depar = s[0] - 48;
					if (InputBox(s, 20, NULL, _T("Destination id"), NULL, BUTTON_HEIGHT, BUTTON_WIDTH, false) == false)
						not_add = true;					
					if (s[1] != '\0')
						desti = ((s[0] - 48) * 10)+ s[1] - 48;
					else
						desti = s[0] - 48;
					if (InputBox(s, 20, NULL, _T("Preference"), NULL, BUTTON_HEIGHT, BUTTON_WIDTH, false) == false)
						not_add = true;
					pre = s[0] - 48;
					if (pre == 1)
					{//如果是规定时间内风险最小策略，读入时间限制
						if (InputBox(s, 20, NULL, _T("Time_limit, at most 999"), NULL, BUTTON_HEIGHT, BUTTON_WIDTH, false) == false)
							not_add = true;
						if (s[1] != '\0')
						{
							if (s[2] != '\0')
								time_limit = ((s[0] - 48) * 100) + ((s[1] - 48) * 10) + s[2] - 48;
							else
								time_limit = ((s[0] - 48) * 10) + s[1] - 48;
						}
						else
							time_limit = s[0] - 48;
					}
					if(!not_add)//如果有关闭的输入框，取消添加
						add_client(str, depar, desti, pre, time_limit);
				}
				pause = false;//恢复时间流动
			}
		}
	}
}

void add_client()
{
	std::string name;
	int depar_id, desti_id, pre, time_limit;
	Client* now_client;
	//输出信息
	std::cout << "Please type in your name, your departure city id, your destination city id, ";
	std::cout << "preference(0 for low_risk first, 1 for short_time first)" << std::endl;
	std::cin >> name >> depar_id >> desti_id >> pre;
	if (pre == 1)
		std::cin >> time_limit;
	std::cout << "ID : " << clients.size() << " user added" << std::endl;
	fs << "ID : " << clients.size() << " user added" << std::endl;
	fs << "ID : " << clients.size() << " NAME : " << name << " departure_id : " << depar_id << " destination_id : " << desti_id;
	pre == 0 ? fs << " preference : LOW_RISK" << std::endl : fs << " preference : SHORT_TIME time_limit : " << time_limit << std::endl;
	pre == 0 ? clients.push_back(Client(name, clients.size(), cities[depar_id], cities[desti_id], PREFERENCE::LOW_RISK)) : clients.push_back(Client(name, clients.size(), cities[depar_id], cities[desti_id], PREFERENCE::SHORT_TIME));
	now_client = &clients[clients.size() - 1];
	//制定旅行计划
	short_path(&(*now_client), cities[(*now_client).get_departure()->get_id()], cities[(*now_client).get_destination()->get_id()], (*now_client).get_pre(), time_limit);
}

void add_client(std::string name, int depar_id, int desti_id, int pre, int time_limit)
{
	Client* now_client;
	std::cout << "ID : " << clients.size() << " user added" << std::endl;
	fs << "ID : " << clients.size() << " user added" << std::endl;
	pre == 0 ? clients.push_back(Client(name, clients.size(), cities[depar_id], cities[desti_id], PREFERENCE::LOW_RISK)) : clients.push_back(Client(name, clients.size(), cities[depar_id], cities[desti_id], PREFERENCE::SHORT_TIME));
	fs << "ID : " << clients.size() - 1 << " NAME : " << name << " departure_id : " << depar_id << " destination_id : " << desti_id;
	pre == 0 ? fs << " preference : LOW_RISK" << std::endl : fs << " preference : SHORT_TIME time_limit : " << time_limit << std::endl;
	now_client = &clients[clients.size() - 1];
	//指定旅行计划
	short_path(&(*now_client), cities[(*now_client).get_departure()->get_id()], cities[(*now_client).get_destination()->get_id()], (*now_client).get_pre(), time_limit);
}