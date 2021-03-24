#include"header.h"
#include"City.h"
#include"Transport.h"
City Beijing("Beijing", 0, MIDIUM_RISK);
City Kunming("Kunming", 1,  LOW_RISK);
City Guangzhou("Guangzhou", 2, HIGH_RISK);
City Wulumuqi("Wulumuqi", 3, LOW_RISK);
City Hefei("Hefei", 4, LOW_RISK);
City Guiyang("Guiyang", 5, LOW_RISK);
City Haerbin("Haerbin", 6, HIGH_RISK);
City Xining("Xining", 7, LOW_RISK);
City Sanya("Sanya", 8, MIDIUM_RISK);
City Xiamen("Xiamen", 9, HIGH_RISK);
City Wuhan("Wuhan", 10, MIDIUM_RISK);
City Lasa("Lasa", 11, LOW_RISK);
City Xian("Xian", 12, MIDIUM_RISK);
City Chongqing("Chongqing", 13, MIDIUM_RISK);
int distance[MAX_CITY][MAX_CITY];
Transport transport[MAX_CITY][MAX_CITY];
std::vector<City*> cities;
IMAGE background;
IMAGE railway_image;
IMAGE railway_image_cover;
IMAGE flight_image;
IMAGE flight_image_cover;
IMAGE road_image;
IMAGE road_image_cover;
IMAGE waiting_image;
IMAGE waiting_image_cover;
IMAGE terminate_image;
IMAGE terminate_image_cover;
std::ofstream fs;

int graph_location_x[MAX_CITY] = { 820, 606, 794, 425, 845, 689, 949, 591, 741, 866, 790, 457, 712, 678 };
int graph_location_y[MAX_CITY] = { 313, 575, 598, 231, 447, 540, 162, 351, 688, 571, 470, 476, 406, 486 };

void set_pictures()
{
	
	putimage(0, 0, &background);//背景地图
	/*setfillcolor(RGB(180, 180, 180));
	fillrectangle(ADD_BUTTON_X, ADD_BUTTON_Y, ADD_BUTTON_X + BUTTON_WIDTH, ADD_BUTTON_Y + BUTTON_HEIGHT);
	setbkmode(TRANSPARENT);	
	settextcolor(RGB(0, 0, 0));
	setfillcolor(RGB(255, 0, 0));
	settextstyle(CITY_NAME_HEIGHT, 0, _T("Consolas"), 0, 0, 0, 0, 0, 0);//设定字体
	outtextxy(820, 313, _T("Beijing"));
	fillcircle(820, 313, 5);
	outtextxy(606, 575, _T("Kunming"));
	fillcircle(606, 575, 5);
	outtextxy(794, 598, _T("Guangzhou"));
	fillcircle(794, 598, 5);
	outtextxy(425, 231, _T("Wulumuqi"));
	fillcircle(425, 231, 5);
	outtextxy(845, 447, _T("Hefei"));
	fillcircle(845, 447, 5);
	outtextxy(689, 540, _T("Guiyang"));
	fillcircle(689, 540, 5);
	outtextxy(949, 162, _T("Haerbin"));
	fillcircle(949, 162, 5);
	outtextxy(591, 351, _T("Xining"));
	fillcircle(591, 351, 5);
	outtextxy(741, 688, _T("Sanya"));
	fillcircle(741, 688, 5);
	outtextxy(866, 571, _T("Xiamen"));
	fillcircle(866, 571, 5);
	outtextxy(790, 470, _T("Wuhan"));
	fillcircle(790, 470, 5);
	outtextxy(457, 476, _T("Lasa"));
	fillcircle(457, 476, 5);
	outtextxy(712, 406, _T("Xian"));
	fillcircle(712, 406, 5);
	outtextxy(678, 486, _T("Chongqing"));
	fillcircle(678, 486, 5);*/
}

void init_travel(void)
{
	//打开日志文件
	fs.open("./Project1/log/log.txt");
	fs << "open loc.txt" << std::endl;
	if (fs.fail())
	{
		std::cout << "cannot open file log.txt"  << std::endl;
		fs << "cannot open file log.txt" << std::endl;
		exit(0);
	}
	//图形化界面图案路径
	loadimage(&background, _T("./Project1/images/background.png"));
	loadimage(&railway_image, _T("./Project1/images/railway_image.png"));
	loadimage(&railway_image_cover, _T("./Project1/images/railway_image_cover.png"));
	loadimage(&flight_image, _T("./Project1/images/flight_image.png"));
	loadimage(&flight_image_cover, _T("./Project1/images/flight_image_cover.png"));
	loadimage(&road_image, _T("./Project1/images/road_image.png"));
	loadimage(&road_image_cover, _T("./Project1/images/road_image_cover.png"));
	loadimage(&waiting_image, _T("./Project1/images/waiting_image.png"));
	loadimage(&waiting_image_cover, _T("./Project1/images/waiting_image_cover.png"));
	loadimage(&terminate_image, _T("./Project1/images/terminate_image.png"));
	loadimage(&terminate_image_cover, _T("./Project1/images/terminate_image_cover.png"));
	cities.push_back(&Beijing);
	cities.push_back(&Kunming);
	cities.push_back(&Guangzhou);
	cities.push_back(&Wulumuqi);
	cities.push_back(&Hefei);
	cities.push_back(&Guiyang);
	cities.push_back(&Haerbin);
	cities.push_back(&Xining);
	cities.push_back(&Sanya);
	cities.push_back(&Xiamen);
	cities.push_back(&Wuhan);
	cities.push_back(&Lasa);
	cities.push_back(&Xian);
	cities.push_back(&Chongqing);
	for (int i = 0; i < MAX_CITY; i++)
	{
		for (int j = 0; j < MAX_CITY; j++)
		{
			distance[i][j] = -1;
		}
	}
	int kind, depar_id, desti_id, distance_between, trans_type, depar_time;
	std::ifstream fileIn;//用文件输入时间表
	fileIn.open("./Project1/database.txt", std::ios::in);//打开文件
	if (fileIn.is_open())//如果打开成功
	{		
		while (!fileIn.eof())
		{
			fileIn >> kind; //文件此行的数据类型（0代表邻接城市信息，1代表交通时间表信息）
			//邻接城市信息行：类型 出发地 目的地 距离
			//交通时间表信息行：类型 出发地 目的地 交通工具类型（0汽车 1火车 2飞机） 出发时间
			if (kind == 0)
			{
				fileIn >> depar_id >> desti_id >> distance_between;
				distance[depar_id][desti_id] = distance_between;
				distance[desti_id][depar_id] = distance_between;//添加距离信息到距离矩阵中
				cities[depar_id]->set_neighbor(cities[desti_id]);
				cities[desti_id]->set_neighbor(cities[depar_id]);//添加到两个城市的邻接表中
			}
			else
			{
				fileIn >> depar_id >> desti_id >> trans_type >> depar_time;
				switch (trans_type)
				{
				case 0:transport[depar_id][desti_id].add_car(depar_time); break;//添加到交通时间表中
				case 1:transport[depar_id][desti_id].add_railway(depar_time); break;
				case 2:transport[depar_id][desti_id].add_flight(depar_time); break;
				}
			}

		}
		fileIn.close();//关闭文件
	}
	
}