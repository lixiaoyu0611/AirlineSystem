#ifndef AIRLINEGRAPH_H
#define AIRLINEGRAPH_H
#include "Airport.h"
#include "Airline.h"
#include "jsonxx.h"
#include "BookOrder.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include<algorithm>

using std::setw;
using namespace jsonxx;

//航线图
class AirlineGraph
{
    public:
        AirlineGraph();
        virtual ~AirlineGraph();
        int mAirportNumber;                         //机场数量
        Airport** mAirportHeadArray;                //顶点表
        vector<Airline*>* mAirlineVector;           //保存航线
        Airport* FindAirportByName(string name);    //查找机场，获取指针
        int GetAirlineNumber();                     //返回航线数目
        void InsertAirline(Airline* airline);       //外部插入接口
        void ShowAllAirlineToUser();                //预览已经建立的全部航线的相关信息
        void ShowAirlineByAirport(int no);           //预览某个机场的航班
        void ShowAirlineByCity(string city);                       //预览某个城市的航班
        void ShowAirlineGraph();                                   //打印输出边链表
        void WriteAirlineJson();                                    //写json到文件
        void Book(Airline* airline);
        void Unsubscribe(BookOrder* bookOrder);
        vector<int>* GetAirportIdByLocation(string loc);
        string GetAirportLocation(string airportName);
        Airport* FindAirportByNo(int number);
        Airport* FindAirlineByName1(string name);                   //通过航班号查找
        Airport* FindAirportByCity(string city);                    //根据城市查询航班
        Airline* FindAirlineByDepartureAirport(string name);        //根据出发城市查找
        void Search(string city1,string city2);                     //根据出发和目的地查找
        void SortByPrice(string name1,string name2);            //按价格排序
        vector<Airline*>* FindAirlineByName(string name);       //通过航班号查找
        void SortByTime(string name1,string name2);             //按时间排序
        void SearchByTime(string time1,string time2,string name1,string name2);//按时间查找
        void SearchByPrice(int price1,int price2,string name1,string name2);//按票价查找
        void SearchCheapest(string city1,string city2);
        int timetransform(string time);                 //时间转换函数
        void Properline(string city1,string city2);     //推荐合理路线
        void ShowBestAirline();                         //推荐最优化线路
        bool timecomp(string time1,string time2);
    protected:

    private:
        Array GenerateAirlineJson();    //生成json
        void LoadAirport(); //从本地载入机场数据
        void LoadAirline(); //从本地载入航线数据
        void InsertAirlineGraph(Airport* airport,Airline* airline); //在图中插入边（插入航线）
};

#endif // AIRLINEGRAPH_H
