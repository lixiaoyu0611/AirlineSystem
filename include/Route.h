#ifndef ROUTE_H
#define ROUTE_H
#include "Airline.h"
#include <iostream>
#include <iomanip>
#include <vector>

class Route
{
    public:
        Route();
        virtual ~Route();
        int mPrevNo;    //����������
        int mTotalCost; //·���ܻ���
        vector<Airline*> mAirlineVec;   //;������
        Route& operator=(const Route& r);   //���� =
        void ShowRoute();   //��ʾ����
        bool CheckPass(string airport); //����Ƿ�����������ĳ������
        int GetRouteLength();   //��ȡת������
        int SumToatalCost();    //�۸����
    protected:

    private:
};

#endif // ROUTE_H
