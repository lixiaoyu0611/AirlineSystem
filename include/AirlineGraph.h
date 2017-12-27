#ifndef AIRLINEGRAPH_H
#define AIRLINEGRAPH_H
#include "Airport.h"
#include "Airline.h"
#include "jsonxx.h"
#include "BookOrder.h"
#include "Route.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>

using std::setw;
using namespace jsonxx;

//����ͼ
class AirlineGraph
{
    public:
        AirlineGraph();
        virtual ~AirlineGraph();
        int mAirportNumber; //��������
        Airport** mAirportHeadArray;    //�����
        vector<Airline*>* mAirlineVector;   //���溽��
        Airport* GetAirportByName(string name);    //���һ�������ȡָ��
        int GetAirlineNumber(); //���غ�����Ŀ
        void InsertAirline(Airline* airline);   //�ⲿ����ӿ�
        void RemoveAirline(Airline* airline);
        void ShowAllAirlineToUser();    //Ԥ���Ѿ�������ȫ�����ߵ������Ϣ
        void ShowAirlineByAirport(int no);  //Ԥ��ĳ�������ĺ���
        void ShowAirlineByCity(string city);    //Ԥ��ĳ�����еĺ���
        void ShowAirlineGraph();    //��ӡ���������
        void WriteAirlineJson();    //дjson���ļ�
        void Book(Airline* airline);    //�����ⲿ��Ʊ��Ϣ��������Ʊ
        void Unsubscribe(BookOrder* bookOrder); //�����ⲿ�˶���Ϣ��������Ʊ
        vector<int>* GetAirportIdByLocation(string loc);    //ͨ�����л�ȡ�ó������л�����Id
        string GetAirportLocation(string airportName);  //��û������ڳ���
        vector<Airline*>* FindAirlineByName(string name);//ͨ������Ų���
        Airline* GetMinCostAirline(int f,int t);    //��ȡ����������ͼ۸񺽰�
        vector<Airline*>* GetAirlineByDACity(string departure,string arrival);  //ͨ���������ִ���л�ȡ����
        void ShowDACityAirlineByDiscountPrice(string departure,string arrival); //�۸�˳����ʾ�����м�ֱ�ﺽ��
        void ShowDACityAirlineByDepartureTime(string departure,string arrival); //����ʱ��˳����ʾ�����м�ֱ�ﺽ��
        vector<Route*>* GetAdvisableRouteWithBFS(string departure,string arrival,int departureTime,int arrivalTime);
    protected:

    private:
        Array GenerateAirlineJson();    //����json
        void LoadAirport(); //�ӱ��������������
        void LoadAirline(); //�ӱ������뺽������
        void InsertAirlineGraph(Airport* airport,Airline* airline); //��ͼ�в���ߣ����뺽�ߣ�
        void RemoveAirlineGraph(Airline* airline);
        void DFS(int v,int a,int* InD,int* visit,vector< vector<Airline*> >* mainVec,vector<Airline*> routeVec);
        void BFS(int f,int a,int* InD,int* visit,vector<Route>* mainVec);   //�����������
        Route** Dijkstra(int v);    //Dijkstra�㷨
        friend class System;
};

#endif // AIRLINEGRAPH_H
