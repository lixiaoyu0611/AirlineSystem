#ifndef BOOKORDER_H
#define BOOKORDER_H
#include <string>

using namespace std;

class BookOrder
{
    public:
        BookOrder();
        virtual ~BookOrder();
        string mName;
        string mIdNumber;
        string mAirlineName;        //�����
        string mCompany;            //���๫˾
        string mDepartureCity;      //��ɳ���
        string mDepartureAirport;   //��ɻ���
        string mArrivalCity;        //�������
        string mArrivalAirport;     //�������
        string mDepartureTime;      //���ʱ��
        string mArrivalTime;        //����ʱ��
        string mAirplaneModel;      //����
        int mPrice;                 //�۸�
    protected:

    private:
};

#endif // BOOKORDER_H
