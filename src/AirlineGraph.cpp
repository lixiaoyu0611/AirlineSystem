#include "AirlineGraph.h"

AirlineGraph::AirlineGraph()
{
    LoadAirport();
    LoadAirline();
   // ShowAirlineGraph();
    //WriteAirlineJson();
    Properline("����","����");
    cout<<timetransform("08:00");

}

AirlineGraph::~AirlineGraph()
{
    //dtor
}
//���������Ϣ
void AirlineGraph::LoadAirport()
{
    Array AirportArray;
    ifstream infile;
    string s;
    infile.open("Airport.json");
    ostringstream tmp;
    tmp<<infile.rdbuf();
    s=tmp.str();
    AirportArray.parse(s);  //����json
    mAirportNumber=AirportArray.size();
  //  cout<<mAirportNumber<<endl;
    mAirportHeadArray=new Airport*[mAirportNumber];
    for(int i=0;i<mAirportNumber;i++)   //���ɶ����
    {
        mAirportHeadArray[i]=new Airport();
        mAirportHeadArray[i]->No=AirportArray.get<Object>(i).get<Number>("���");
        mAirportHeadArray[i]->mAirportName=AirportArray.get<Object>(i).get<String>("����");
        mAirportHeadArray[i]->mShortName=AirportArray.get<Object>(i).get<String>("��������");
        mAirportHeadArray[i]->mLocation=AirportArray.get<Object>(i).get<String>("����");
    }
    //cout<<AirportArray.json();
}
//���뺽����Ϣ
void AirlineGraph::LoadAirline()
{
    Array AirlineArray;
    ifstream infile;
    string s;
    infile.open("Airline.json");
    ostringstream tmp;
    tmp<<infile.rdbuf();
    s=tmp.str();
    AirlineArray.parse(s);  //����json
    mAirlineVector=new vector<Airline*>();
    for(int i=0;i<AirlineArray.size();i++)  //���溽�ߵ�vector
    {
        Airline* airline=new Airline();
        airline->mAirlineName=AirlineArray.get<Object>(i).get<String>("�����");
        airline->mCompany=AirlineArray.get<Object>(i).get<String>("��˾");
        airline->mDepartureAirport=AirlineArray.get<Object>(i).get<String>("��ɻ���");
        airline->mArrivalAirport=AirlineArray.get<Object>(i).get<String>("�������");
        airline->mDepartureTime=AirlineArray.get<Object>(i).get<String>("���ʱ��");
        airline->mArrivalTime=AirlineArray.get<Object>(i).get<String>("����ʱ��");
        airline->mAirplaneModel=AirlineArray.get<Object>(i).get<String>("����");
        airline->mDepartureCity=AirlineArray.get<Object>(i).get<String>("��ʼ����");
        airline->mArrivalCity=AirlineArray.get<Object>(i).get<String>("�������");
        airline->mPrice=AirlineArray.get<Object>(i).get<Number>("�۸�");
        airline->mIntDiscount=AirlineArray.get<Object>(i).get<Number>("����ۿ�");
        airline->mCapacity=AirlineArray.get<Object>(i).get<Number>("����");
        airline->mCurrentNumber=AirlineArray.get<Object>(i).get<Number>("��ǰ����");
        mAirlineVector->push_back(airline);

        Airport* airport=FindAirportByName(airline->mDepartureAirport);
        if(airport!=NULL)   //�жϻ����Ƿ����
        {
            InsertAirlineGraph(airport,airline);    //���뵽ͼ
        }
    }
    infile.close();
    //cout<<AirlineArray.json();
}
//ͨ�������һ���
Airport* AirlineGraph::FindAirportByCity(string city)
{
    for(int i=0;i<mAirportNumber;i++)
    {
        if(mAirportHeadArray[i]->mLocation==city)
        {

          //  cout<<mAirportHeadArray[i]->mAirportName;
            return mAirportHeadArray[i];
        }
    }
    return NULL;
    }

//ͨ������Ų�ѯ����
Airport* AirlineGraph::FindAirportByName(string name)
{
    for(int i=0;i<mAirportNumber;i++)
    {
        if(mAirportHeadArray[i]->mAirportName==name)
        {

          //  cout<<mAirportHeadArray[i]->mAirportName;
            return mAirportHeadArray[i];
        }
    }
    return NULL;
}

void AirlineGraph::InsertAirlineGraph(Airport* airport,Airline* airline)
//���뺽�� ����ʱ����
{
    Airline* line=airport->mAdjAirline;
    if(line==NULL)
    {
        airport->mAdjAirline=airline;
    }else
    {
        //cout<<line->mAirlineName;
        while(line->mNextAirline!=NULL)
        {
            line=line->mNextAirline;
        }
        line->mNextAirline=airline;
    }
}
//չʾ����
void AirlineGraph::ShowAirlineGraph()
{
    cout.setf(ios::left);
    cout<<endl;

    for(int i=0;i<mAirportNumber;i++)
    {
        cout<<endl;
      //  cout<<"======================================================================================================================";
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
      //  cout<<endl<<"��"<<airport->mLocation<<" - "<<airport->mAirportName<<"��"<<"\t"<<endl<<endl;
        while(airline!=NULL)
        {
         //   cout<<airline->mAirlineName<<"\t";
            /*cout<<setw(25)<<airline->mAirlineName<<setw(25);
            cout<<airline->mCompany<<setw(35);
            cout<<airline->mDepartureAirport<<setw(25);
            cout<<airline->mArrivalAirport<<setw(25);
            cout<<airline->mDepartureTime<<setw(13);
            cout<<airline->mArrivalTime<<setw(13);
            cout<<airline->mAirplaneModel<<setw(13);
            cout<<airline->mDepartureCity<<setw(13);
            cout<<airline->mArrivalCity;
            cout<<endl;*/
            airline=airline->mNextAirline;
        }
    }
   // cout<<endl<<"======================================================================================================================"<<endl;
}
//�����ļ�����
Array AirlineGraph::GenerateAirlineJson()
{
    Array jsonArray;
    for(int i=0;i<mAirportNumber;i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            Object jsonObj;
            jsonObj<<"��˾"<<airline->mCompany;
            jsonObj<<"�����"<<airline->mAirlineName;
            jsonObj<<"��ʼ����"<<airline->mDepartureCity;
            jsonObj<<"��ɻ���"<<airline->mDepartureAirport;
            jsonObj<<"�������"<<airline->mArrivalCity;
            jsonObj<<"�������"<<airline->mArrivalAirport;
            jsonObj<<"���ʱ��"<<airline->mDepartureTime;
            jsonObj<<"����ʱ��"<<airline->mArrivalTime;
            jsonObj<<"����"<<airline->mAirplaneModel;
            jsonObj<<"�۸�"<<airline->mPrice;
            jsonObj<<"����ۿ�"<<airline->mIntDiscount;
            jsonObj<<"����"<<airline->mCapacity;
            jsonObj<<"��ǰ����"<<airline->mCurrentNumber;

            jsonArray<<jsonObj;
            //cout<<airline->mAirlineName<<"\t";
            /*cout<<setw(25)<<airline->mAirlineName<<setw(25);
            cout<<airline->mCompany<<setw(35);
            cout<<airline->mDepartureAirport<<setw(25);
            cout<<airline->mArrivalAirport<<setw(25);
            cout<<airline->mDepartureTime<<setw(13);
            cout<<airline->mArrivalTime<<setw(13);
            cout<<airline->mAirplaneModel<<setw(13);
            cout<<airline->mDepartureCity<<setw(13);
            cout<<airline->mArrivalCity;
            cout<<endl;*/
            airline=airline->mNextAirline;
        }
    }
    return jsonArray;
}

void AirlineGraph::WriteAirlineJson()
{
    ofstream outfile;
    outfile.open("Airline.json");
    Array jsonArray=GenerateAirlineJson();
    //cout<<jsonArray.json();
    outfile<<jsonArray.json();
    outfile.close();
}

int AirlineGraph::GetAirlineNumber()
{
    return mAirlineVector->size();
}

void AirlineGraph::InsertAirline(Airline* airline)
{
    Airport* dAirport=FindAirportByName(airline->mDepartureAirport);
    Airport* aAirport=FindAirportByName(airline->mArrivalAirport);

    if(dAirport==NULL||aAirport==NULL)
    {
        cout<<endl<<"���������ڣ�";
        return;
    }else if(dAirport->mLocation!=airline->mDepartureCity||aAirport->mLocation!=airline->mArrivalCity)
    {
        cout<<endl<<"����λ����Ϣ��ƥ�䣡";
        return;
    }else
    {
        mAirlineVector->push_back(airline);
        InsertAirlineGraph(dAirport,airline);    //���뵽ͼ
    }
}


string AirlineGraph::GetAirportLocation(string airportName)
{
    return FindAirportByName(airportName)->mLocation;
}
//��ɳ��в�ѯ
Airline* AirlineGraph::FindAirlineByDepartureAirport(string name)
{
    for(int i=0;i<mAirportNumber;i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mArrivalCity==name)
            {
                /*cout<<"�����:"<<airline->mAirlineName<<endl;
                cout<<"��˾:"<<airline->mCompany<<endl;
                cout<<"��ʼ����:"<<airline->mDepartureCity<<endl;
                cout<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
                cout<<"�������:"<<airline->mArrivalCity<<endl;
                cout<<"�������:"<<airline->mArrivalAirport<<endl;
                cout<<"���ʱ��:"<<airline->mDepartureTime<<endl;
                cout<<"����ʱ��:"<<airline->mArrivalTime<<endl;
                cout<<"����:"<<airline->mAirplaneModel<<endl;
                cout<<"�۸�:"<<airline->mPrice<<endl;
                cout<<"����ۿ�:"<<airline->mIntDiscount<<endl;
                cout<<"����:"<<airline->mCapacity<<endl;
                cout<<"��ǰ����:"<<airline->mCurrentNumber<<endl;*/

            }
            airline=airline->mNextAirline;
        }
    }
    return NULL;
}
//��ѯĳ�����ߵ���������뺽���
vector<Airline*>* AirlineGraph::FindAirlineByName(string name)
{
    vector<Airline*>* vec=new vector<Airline*>();
    for(int i=0;i<mAirportNumber;i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mAirlineName==name)
            {
                /*cout<<"�����:"<<airline->mAirlineName<<endl;
                cout<<"��˾:"<<airline->mCompany<<endl;
                cout<<"��ʼ����:"<<airline->mDepartureCity<<endl;
                cout<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
                cout<<"�������:"<<airline->mArrivalCity<<endl;
                cout<<"�������:"<<airline->mArrivalAirport<<endl;
                cout<<"���ʱ��:"<<airline->mDepartureTime<<endl;
                cout<<"����ʱ��:"<<airline->mArrivalTime<<endl;
                cout<<"����:"<<airline->mAirplaneModel<<endl;
                cout<<"�۸�:"<<airline->mPrice<<endl;
                cout<<"����ۿ�:"<<airline->mIntDiscount<<endl;
                cout<<"����:"<<airline->mCapacity<<endl;
                cout<<"��ǰ����:"<<airline->mCurrentNumber<<endl;*/
                vec->push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    return vec;
}

void AirlineGraph::ShowAllAirlineToUser()
{
    cout.setf(ios::left);
    cout<<endl;

    for(int i=0;i<mAirportNumber;i++)
    {
        ShowAirlineByAirport(i);
    }
    cout<<endl<<"========================================================================================================================================================================"<<endl;
}


void AirlineGraph::ShowAirlineByAirport(int no)
{
    cout.setf(ios::left);
    cout<<endl;
    cout<<"========================================================================================================================================================================"<<endl;
    Airport* airport=mAirportHeadArray[no];
    Airline* airline=airport->mAdjAirline;
    cout<<endl<<"��"<<airport->mLocation<<" - "<<airport->mAirportName<<"��"<<"\t"<<endl<<endl;

    cout<<setw(10)<<"�����";
    cout<<setw(25)<<"���չ�˾";
    cout<<setw(10)<<"������";
    cout<<setw(20)<<"��ɻ���";
    cout<<setw(10)<<"Ŀ�ĵ�";
    cout<<setw(20)<<"��½����";
    cout<<setw(10)<<"���ʱ��";
    cout<<setw(10)<<"�ִ�ʱ��";
    cout<<setw(8)<<"����";
    cout<<setw(8)<<"Ʊ��";
    cout<<setw(8)<<"�ۿ�";
    cout<<setw(9)<<"�ۺ�Ʊ��";
    cout<<setw(8)<<"�ؿ���";
    cout<<setw(8)<<"����";
    cout<<setw(8)<<"��Ʊ";
    cout<<endl<<endl;

    while(airline!=NULL)
    {
        cout<<setw(10)<<airline->mAirlineName;
        cout<<setw(25)<<airline->mCompany;
        cout<<setw(10)<<airline->mDepartureCity;
        cout<<setw(20)<<airline->mDepartureAirport;
        cout<<setw(10)<<airline->mArrivalCity;
        cout<<setw(20)<<airline->mArrivalAirport;
        cout<<setw(10)<<airline->mDepartureTime;
        cout<<setw(10)<<airline->mArrivalTime;
        cout<<setw(8)<<airline->mAirplaneModel;
        cout<<setw(8)<<airline->mPrice;
        cout<<setw(8)<<airline->mIntDiscount/1000.0;
        cout<<setw(9)<<airline->mPrice*(1-airline->mIntDiscount/1000.0);
        cout<<setw(8)<<airline->mCapacity;
        cout<<setw(8)<<airline->mCurrentNumber;
        cout<<setw(8)<<airline->mCapacity-airline->mCurrentNumber;
        cout<<endl;
        airline=airline->mNextAirline;
    }
}

vector<int>* AirlineGraph::GetAirportIdByLocation(string loc)
{
    vector<int>* vec=new vector<int>();
    for(int i=0; i<mAirportNumber; i++)
    {
        if(mAirportHeadArray[i]->mLocation==loc)
        {
            vec->push_back(i);
        }
    }

    cout<<endl<<"========================================================================================================================================================================"<<endl;
return vec;
}

void AirlineGraph::ShowAirlineByCity(string city)
{
    vector<int>* vec=GetAirportIdByLocation(city);
    for(int i=0;i<vec->size();i++)
    {
        ShowAirlineByAirport((*vec)[i]);
    }
    if(vec->size()>0)
    {
        cout<<endl<<"========================================================================================================================================================================"<<endl;
    }else
    {
        cout<<endl<<"�޺�����Ϣ��"<<endl;
    }
}
int AirlineGraph::timetransform(string t)
{
    if(t.length()==5)
        return (600*(t[0]-'0')+60*(t[1]-'0')+10*(t[3]-'0')+t[4]-'0');
    if(t.length()==4)
        return (60*(t[0]-'0')+6*(t[2]-'0')+(t[3]-'0'));
}
//���۸�����
void AirlineGraph::SearchByPrice(int price1,int price2,string name1,string name2)
{
    vector<Airline*> Count;
    vector<Airline*>::iterator iter=Count.begin();
    vector<Airline*>::iterator temp;
    for(int i=0; i<mAirportNumber; i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mDepartureCity==name1&&airline->mArrivalCity==name2)
            {
                Count.push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    for(int i=price1; i<price2; i++)
    {
        for(vector<Airline*>::iterator m = Count.begin(); m != Count.end(); m++ )    //�õ������ķ�ʽ������������ֵ
        {
            if((*m)->mPrice==i&&((*m)->flag==0))
            {
                cout<<"�����:"<<(*m)->mAirlineName<<endl;
                cout<<"��˾:"<<(*m)->mCompany<<endl;
                cout<<"��ʼ����:"<<(*m)->mDepartureCity<<endl;
                cout<<"��ɻ���:"<<(*m)->mDepartureAirport<<endl;
                cout<<"�������:"<<(*m)->mArrivalCity<<endl;
                cout<<"�������:"<<(*m)->mArrivalAirport<<endl;
                cout<<"���ʱ��:"<<(*m)->mDepartureTime<<endl;
                cout<<"����ʱ��:"<<(*m)->mArrivalTime<<endl;
                cout<<"����:"<<(*m)->mAirplaneModel<<endl;
                cout<<"�۸�:"<<(*m)->mPrice<<endl;
                cout<<"����ۿ�:"<<(*m)->mIntDiscount<<endl;
                cout<<"����:"<<(*m)->mCapacity<<endl;
                cout<<"��ǰ����:"<<(*m)->mCurrentNumber<<endl;
                (*m)->flag==1;
            }
        }
    }
}
//��ʱ������
void AirlineGraph::SearchByTime(string time1,string time2,string name1,string name2)//��ʱ�����
{
    vector<Airline*> Count;
    vector<Airline*>::iterator iter=Count.begin();
    vector<Airline*>::iterator temp;
    for(int i=0; i<mAirportNumber; i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            airline->transformtime=timetransform(airline->mDepartureTime);
            if(airline->mDepartureCity==name1&&airline->mArrivalCity==name2)
            {
                Count.push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    for(int i=timetransform(time1); i<timetransform(time2);i++)
    {
        for(vector<Airline*>::iterator m = Count.begin(); m != Count.end(); m++ )    //�õ������ķ�ʽ������������ֵ
        {
            if((*m)->transformtime==i&&((*m)->flag==0))
            {
                cout<<"�����:"<<(*m)->mAirlineName<<endl;
                cout<<"��˾:"<<(*m)->mCompany<<endl;
                cout<<"��ʼ����:"<<(*m)->mDepartureCity<<endl;
                cout<<"��ɻ���:"<<(*m)->mDepartureAirport<<endl;
                cout<<"�������:"<<(*m)->mArrivalCity<<endl;
                cout<<"�������:"<<(*m)->mArrivalAirport<<endl;
                cout<<"���ʱ��:"<<(*m)->mDepartureTime<<endl;
                cout<<"����ʱ��:"<<(*m)->mArrivalTime<<endl;
                cout<<"����:"<<(*m)->mAirplaneModel<<endl;
                cout<<"�۸�:"<<(*m)->mPrice<<endl;
                cout<<"����ۿ�:"<<(*m)->mIntDiscount<<endl;
                cout<<"����:"<<(*m)->mCapacity<<endl;
                cout<<"��ǰ����:"<<(*m)->mCurrentNumber<<endl;
                (*m)->flag==1;
            }
        }
    }
}

//��ʱ������
void AirlineGraph::SortByTime(string name1,string name2)
{
    vector<Airline*> Count;
    vector<Airline*>::iterator iter=Count.begin();
    vector<Airline*>::iterator temp;
    for(int i=0; i<mAirportNumber; i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            airline->transformtime=timetransform(airline->mDepartureTime);
            if(airline->mDepartureCity==name1&&airline->mArrivalCity==name2)
            {
                Count.push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    for(int i=0; i<1440; i++)
    {
        for(vector<Airline*>::iterator m = Count.begin(); m != Count.end(); m++ )    //�õ������ķ�ʽ������������ֵ
        {
            if((*m)->transformtime==i&&((*m)->flag==0))
            {
                cout<<"�����:"<<(*m)->mAirlineName<<endl;
                cout<<"��˾:"<<(*m)->mCompany<<endl;
                cout<<"��ʼ����:"<<(*m)->mDepartureCity<<endl;
                cout<<"��ɻ���:"<<(*m)->mDepartureAirport<<endl;
                cout<<"�������:"<<(*m)->mArrivalCity<<endl;
                cout<<"�������:"<<(*m)->mArrivalAirport<<endl;
                cout<<"���ʱ��:"<<(*m)->mDepartureTime<<endl;
                cout<<"����ʱ��:"<<(*m)->mArrivalTime<<endl;
                cout<<"����:"<<(*m)->mAirplaneModel<<endl;
                cout<<"�۸�:"<<(*m)->mPrice<<endl;
                cout<<"����ۿ�:"<<(*m)->mIntDiscount<<endl;
                cout<<"����:"<<(*m)->mCapacity<<endl;
                cout<<"��ǰ����:"<<(*m)->mCurrentNumber<<endl;
                (*m)->flag==1;
            }
        }
    }
}
void AirlineGraph::Search(string city1,string city2)
{
    vector<Airline*> Count;
    vector<Airline*>::iterator iter=Count.begin();
    vector<Airline*>::iterator temp;
    for(int i=0; i<mAirportNumber; i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mDepartureCity==city1&&airline->mArrivalCity==city2)
            {
                Count.push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    for(int i=0; i<3030; i++)
    {
        for(vector<Airline*>::iterator m = Count.begin(); m != Count.end(); m++ )    //�õ������ķ�ʽ������������ֵ
        {
                cout<<"�����:"<<(*m)->mAirlineName<<endl;
                cout<<"��˾:"<<(*m)->mCompany<<endl;
                cout<<"��ʼ����:"<<(*m)->mDepartureCity<<endl;
                cout<<"��ɻ���:"<<(*m)->mDepartureAirport<<endl;
                cout<<"�������:"<<(*m)->mArrivalCity<<endl;
                cout<<"�������:"<<(*m)->mArrivalAirport<<endl;
                cout<<"���ʱ��:"<<(*m)->mDepartureTime<<endl;
                cout<<"����ʱ��:"<<(*m)->mArrivalTime<<endl;
                cout<<"����:"<<(*m)->mAirplaneModel<<endl;
                cout<<"�۸�:"<<(*m)->mPrice<<endl;
                cout<<"����ۿ�:"<<(*m)->mIntDiscount<<endl;
                cout<<"����:"<<(*m)->mCapacity<<endl;
                cout<<"��ǰ����:"<<(*m)->mCurrentNumber<<endl;
                (*m)->flag==1;
            }
        }
}

void AirlineGraph::Book(Airline* airline)
{
    airline->mCurrentNumber=airline->mCurrentNumber+1;
    WriteAirlineJson();
}

void AirlineGraph::Unsubscribe(BookOrder* bookOrder)
{
    vector<Airline*>* vec=FindAirlineByName(bookOrder->mAirlineName);
    for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
    {
        if((*it)->mDepartureAirport==bookOrder->mDepartureAirport&&(*it)->mArrivalAirport==bookOrder->mArrivalAirport)
        {
            (*it)->mCurrentNumber=(*it)->mCurrentNumber-1;
            WriteAirlineJson();
            break;
        }
    }
    cout<<"==========================================="<<endl;
    cout<<endl;
    cout<<"================ ��Ʊ�ɹ� ================="<<endl;
    cout<<endl;
    cout<<setw(12)<<"����:"<<bookOrder->mName<<endl;
    cout<<setw(12)<<"֤����:"<<bookOrder->mIdNumber<<endl;
    cout<<setw(12)<<"�����:"<<bookOrder->mAirlineName<<endl;
    cout<<setw(12)<<"���չ�˾:"<<bookOrder->mCompany<<endl;
    cout<<setw(12)<<"������:"<<bookOrder->mDepartureCity<<endl;
    cout<<setw(12)<<"Ŀ�ĵ�:"<<bookOrder->mArrivalCity<<endl;
    cout<<setw(12)<<"����۸�:"<<bookOrder->mPrice<<endl;
    cout<<endl;
    cout<<"==========================================="<<endl;
}

//���۸�����
void AirlineGraph::SortByPrice(string name1,string name2)
{
    vector<Airline*> Count;
    vector<Airline*>::iterator iter=Count.begin();
    vector<Airline*>::iterator temp;
    for(int i=0; i<mAirportNumber; i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mDepartureCity==name1&&airline->mArrivalCity==name2)
            {
                Count.push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    for(int i=0; i<3030; i++)
    {
        for(vector<Airline*>::iterator m = Count.begin(); m != Count.end(); m++ )    //�õ������ķ�ʽ������������ֵ
        {
            if((*m)->transformtime==i&&((*m)->flag==0))
            {
                cout<<"�����:"<<(*m)->mAirlineName<<endl;
                cout<<"��˾:"<<(*m)->mCompany<<endl;
                cout<<"��ʼ����:"<<(*m)->mDepartureCity<<endl;
                cout<<"��ɻ���:"<<(*m)->mDepartureAirport<<endl;
                cout<<"�������:"<<(*m)->mArrivalCity<<endl;
                cout<<"�������:"<<(*m)->mArrivalAirport<<endl;
                cout<<"���ʱ��:"<<(*m)->mDepartureTime<<endl;
                cout<<"����ʱ��:"<<(*m)->mArrivalTime<<endl;
                cout<<"����:"<<(*m)->mAirplaneModel<<endl;
                cout<<"�۸�:"<<(*m)->mPrice<<endl;
                cout<<"����ۿ�:"<<(*m)->mIntDiscount<<endl;
                cout<<"����:"<<(*m)->mCapacity<<endl;
                cout<<"��ǰ����:"<<(*m)->mCurrentNumber<<endl;
                (*m)->flag==1;
            }
        }
    }
}
void AirlineGraph::Properline(string city1,string city2)
{
    //Search(city1,city2);
    Airport* airport=FindAirportByCity(city1);
    if(airport!=NULL)
    {
        Airline* airline = airport->mAdjAirline;
        while(airline!=NULL)
        {
            while(airline->mArrivalCity==city2)
            {
                /* cout<<"ֱ�﷽����"<<endl;
                 cout<<setw(10)<<airline->mAirlineName;
                 cout<<setw(25)<<airline->mCompany;
                 cout<<setw(10)<<airline->mDepartureCity;
                 cout<<setw(20)<<airline->mDepartureAirport;
                 cout<<setw(10)<<airline->mArrivalCity;
                 cout<<setw(20)<<airline->mArrivalAirport;
                 cout<<setw(10)<<airline->mDepartureTime;
                 cout<<setw(10)<<airline->mArrivalTime;
                 cout<<setw(8)<<airline->mAirplaneModel;
                 cout<<setw(8)<<airline->mPrice;
                 cout<<setw(8)<<airline->mIntDiscount/1000.0;
                 cout<<setw(9)<<airline->mPrice*(1-airline->mIntDiscount/1000.0);
                 cout<<setw(8)<<airline->mCapacity;
                 cout<<setw(8)<<airline->mCurrentNumber;
                 cout<<setw(8)<<airline->mCapacity-airline->mCurrentNumber;
                 cout<<endl;*/
                airline=airline->mNextAirline;
            }
            string transfercity = airline->mArrivalCity;          //��ת����
            Airport* transfer = FindAirportByCity(transfercity);     //
            cout<<transfer;
            if(transfer!=NULL)
            {
                Airline* airlines = transfer->mAdjAirline;
                while(airlines!=NULL)
                {
                    if(airlines->mArrivalCity==city2&&((timetransform(airline->mArrivalTime))<(timetransform(airlines->mDepartureTime))))
                    {
                        cout<<"��ת����"<<endl;
                        cout<<setw(10)<<airline->mAirlineName;
                        cout<<setw(25)<<airline->mCompany;
                        cout<<setw(10)<<airline->mDepartureCity;
                        cout<<setw(20)<<airline->mDepartureAirport;
                        cout<<setw(10)<<airline->mArrivalCity;
                        cout<<setw(20)<<airline->mArrivalAirport;
                        cout<<setw(10)<<airline->mDepartureTime;
                        cout<<setw(10)<<airline->mArrivalTime;
                        cout<<setw(8)<<airline->mAirplaneModel;
                        cout<<setw(8)<<airline->mPrice;
                        cout<<setw(8)<<airline->mIntDiscount/1000.0;
                        cout<<setw(9)<<airline->mPrice*(1-airline->mIntDiscount/1000.0);
                        cout<<setw(8)<<airline->mCapacity;
                        cout<<setw(8)<<airline->mCurrentNumber;
                        cout<<setw(8)<<airline->mCapacity-airline->mCurrentNumber;
                        cout<<endl;
                        cout<<setw(10)<<airlines->mAirlineName;
                        cout<<setw(25)<<airlines->mCompany;
                        cout<<setw(10)<<airlines->mDepartureCity;
                        cout<<setw(20)<<airlines->mDepartureAirport;
                        cout<<setw(10)<<airlines->mArrivalCity;
                        cout<<setw(20)<<airlines->mArrivalAirport;
                        cout<<setw(10)<<airlines->mDepartureTime;
                        cout<<setw(10)<<airlines->mArrivalTime;
                        cout<<setw(8)<<airlines->mAirplaneModel;
                        cout<<setw(8)<<airlines->mPrice;
                        cout<<setw(8)<<airlines->mIntDiscount/1000.0;
                        cout<<setw(9)<<airlines->mPrice*(1-airline->mIntDiscount/1000.0);
                        cout<<setw(8)<<airlines->mCapacity;
                        cout<<setw(8)<<airlines->mCurrentNumber;
                        cout<<setw(8)<<airlines->mCapacity-airline->mCurrentNumber;
                        cout<<endl;
                    }
                    airlines = airlines->mNextAirline;
                }

            }
            airline=airline->mNextAirline;
        }
    }
}
