#pragma once
#include<vector>
#include<iostream>
#include<Windows.h>
#include<thread>
#include<easyx.h>
#include<graphics.h>
#include<fstream>
#include<string>
#include<atlstr.h>

class City;
class Client;
class Transport;

enum class PREFERENCE { LOW_RISK, SHORT_TIME };//旅客策略
enum class CLIENT_STATE { on_flight, on_road, on_rail, waiting };//状态
enum class TRANSPORT { flight, railway, car };//交通工具

constexpr int MAX_CITY = 30;//城市数量上限
constexpr float HIGH_RISK = 0.9f;
constexpr float MIDIUM_RISK = 0.5f;
constexpr float LOW_RISK = 0.2f;//风险等级对应数值
constexpr double MAX_WEIGHT = 10000;//权值上限
constexpr int TIME_INTERVAL = 10000;//更新状态时间间隔，为了方便展示暂时设为1s
constexpr int CAR_SPEED = 1;//汽车速度
constexpr int RAILWAY_SPEED = 2;//铁路速度
constexpr int FLIGHT_SPEED = 5;//飞机速度
constexpr int CAR_RISK = 2;//汽车风险值
constexpr int RAILWAY_RISK = 5;//铁路风险值
constexpr int FLIGHT_RISK = 9;//飞机风险值
constexpr int MAX_TIME = 24;//一天的时间总数
constexpr int TIME_DIVIDE = 30;//将一小时旅行时间/10s真实程序时间，切割为多段以进行连贯动画

constexpr int GRAPH_WIDTH = 1280;
constexpr int GRAPH_HEIGHT = 720;
constexpr int CITY_NAME_TEXT_HEIGHT = 10;
constexpr int CITY_NAME_TEXT_WIDTH = 10;
constexpr int CITY_NAME_HEIGHT = 25;
constexpr int ADD_BUTTON_X = 1082;
constexpr int ADD_BUTTON_Y = 223;
constexpr int BUTTON_HEIGHT = 50;
constexpr int BUTTON_WIDTH = 120;//图形化界面参数
constexpr COLORREF NAME_COLOR = RGB(255, 0, 0);//旅客姓名颜色
constexpr COLORREF INFO_COLOR = RGB(0, 0, 0);//旅客信息颜色


extern City Beijing;
extern City Kunming;
extern City Guangzhou;
extern City Wulumuqi;
extern City Hefei;
extern City Guiyang;
extern City Haerbin;
extern City Xining;
extern City Sanya;
extern City Xiamen;
extern City Wuhan;
extern City Lasa;
extern City Xian;
extern City Chongqing;//设置城市

extern int distance[MAX_CITY][MAX_CITY];//记录城市间距离
extern Transport transport[MAX_CITY][MAX_CITY];//记录城市之间交通时间表
extern int graph_location_x[MAX_CITY];//城市在地图上的x坐标
extern int graph_location_y[MAX_CITY];//城市在地图上的y坐标
extern std::vector<Client> clients;//用户集合
extern std::vector<City*> cities;//城市集合
extern int now_time;//绝对时间
extern bool pause;//有系统输入时不计时，停止计时

extern IMAGE background;
extern IMAGE railway_image;
extern IMAGE railway_image_cover;
extern IMAGE flight_image;
extern IMAGE flight_image_cover;
extern IMAGE road_image;
extern IMAGE road_image_cover;
extern IMAGE waiting_image;
extern IMAGE waiting_image_cover;
extern IMAGE terminate_image;
extern IMAGE terminate_image_cover;
extern IMAGE waiting_image_cover;//图形化界面图案对象

extern std::ofstream fs;//日志文件指针

void init_travel(void);//初始化城市信息
void short_path(Client* client, City* depar, City* desti, PREFERENCE pre, int time_limit);//最短路线算法
void wait_for_keyboard();//等待用户用键盘输入指令线程
void wait_for_mouse();//等待用户用鼠标输入指令线程
void out_clients();//输出所有用户信息
void out_clients(Client* client);//输出指定用户信息
void add_client();
void add_client(std::string name, int depar_id, int desti_id, int pre, int time_limit);//添加用户