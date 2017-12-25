#ifndef SYSTEM_H
#define SYSTEM_H
#include "AirlineGraph.h"
#include "BookOrder.h"
#include <fstream>

class System
{
    public:
        System();
        virtual ~System();
        AirlineGraph* mAirlineGraph;
        vector<BookOrder*>* mBookOrderVector;
        void InsertAirlineInfo();   //���뺽����Ϣ
        void ShowAllAirlineToUser();    //Ԥ���Ѿ�������ȫ�����ߵ������Ϣ
        void ShowAirlineByAirport(int no);  //Ԥ��ĳ�������ĺ���
        void ShowAirlineByCity(string city);    //Ԥ��ĳ�����еĺ���
        void SearchAirline(string name);    //ͨ������Ų鿴��ϸ��Ϣ
        void LoadBookOrder();
        int GetBookOrderNum();
        void Book();    //��Ʊ
        void ShowBookList();
        void Unsubscribe(); //��Ʊ
        void UnsubscribeByName(string name); //ͨ��������Ʊ
        void UnsubscribeByIdNum(string Id); //ͨ��֤������Ʊ
        void UnsubscribeByNo(int no); //ͨ�������Ʊ
    protected:

    private:
        Array GenerateBookJson();    //����json
};

#endif // SYSTEM_H
