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

enum class PREFERENCE { LOW_RISK, SHORT_TIME };//�ÿͲ���
enum class CLIENT_STATE { on_flight, on_road, on_rail, waiting };//״̬
enum class TRANSPORT { flight, railway, car };//��ͨ����

constexpr int MAX_CITY = 30;//������������
constexpr float HIGH_RISK = 0.9f;
constexpr float MIDIUM_RISK = 0.5f;
constexpr float LOW_RISK = 0.2f;//���յȼ���Ӧ��ֵ
constexpr double MAX_WEIGHT = 10000;//Ȩֵ����
constexpr int TIME_INTERVAL = 10000;//����״̬ʱ������Ϊ�˷���չʾ��ʱ��Ϊ1s
constexpr int CAR_SPEED = 1;//�����ٶ�
constexpr int RAILWAY_SPEED = 2;//��·�ٶ�
constexpr int FLIGHT_SPEED = 5;//�ɻ��ٶ�
constexpr int CAR_RISK = 2;//��������ֵ
constexpr int RAILWAY_RISK = 5;//��·����ֵ
constexpr int FLIGHT_RISK = 9;//�ɻ�����ֵ
constexpr int MAX_TIME = 24;//һ���ʱ������
constexpr int TIME_DIVIDE = 30;//��һСʱ����ʱ��/10s��ʵ����ʱ�䣬�и�Ϊ����Խ������ᶯ��

constexpr int GRAPH_WIDTH = 1280;
constexpr int GRAPH_HEIGHT = 720;
constexpr int CITY_NAME_TEXT_HEIGHT = 10;
constexpr int CITY_NAME_TEXT_WIDTH = 10;
constexpr int CITY_NAME_HEIGHT = 25;
constexpr int ADD_BUTTON_X = 1082;
constexpr int ADD_BUTTON_Y = 223;
constexpr int BUTTON_HEIGHT = 50;
constexpr int BUTTON_WIDTH = 120;//ͼ�λ��������
constexpr COLORREF NAME_COLOR = RGB(255, 0, 0);//�ÿ�������ɫ
constexpr COLORREF INFO_COLOR = RGB(0, 0, 0);//�ÿ���Ϣ��ɫ


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
extern City Chongqing;//���ó���

extern int distance[MAX_CITY][MAX_CITY];//��¼���м����
extern Transport transport[MAX_CITY][MAX_CITY];//��¼����֮�佻ͨʱ���
extern int graph_location_x[MAX_CITY];//�����ڵ�ͼ�ϵ�x����
extern int graph_location_y[MAX_CITY];//�����ڵ�ͼ�ϵ�y����
extern std::vector<Client> clients;//�û�����
extern std::vector<City*> cities;//���м���
extern int now_time;//����ʱ��
extern bool pause;//��ϵͳ����ʱ����ʱ��ֹͣ��ʱ

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
extern IMAGE waiting_image_cover;//ͼ�λ�����ͼ������

extern std::ofstream fs;//��־�ļ�ָ��

void init_travel(void);//��ʼ��������Ϣ
void short_path(Client* client, City* depar, City* desti, PREFERENCE pre, int time_limit);//���·���㷨
void wait_for_keyboard();//�ȴ��û��ü�������ָ���߳�
void wait_for_mouse();//�ȴ��û����������ָ���߳�
void out_clients();//��������û���Ϣ
void out_clients(Client* client);//���ָ���û���Ϣ
void add_client();
void add_client(std::string name, int depar_id, int desti_id, int pre, int time_limit);//����û�