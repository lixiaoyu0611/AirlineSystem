#include "AirlineGraph.h"

AirlineGraph::AirlineGraph()
{
    LoadAirport();
    LoadAirline();
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
    infile.open("data/Airport.json");
    ostringstream tmp;
    tmp<<infile.rdbuf();
    s=tmp.str();
    AirportArray.parse(s);  //����json
    mAirportNumber=AirportArray.size();
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
    infile.open("data/Airline.json");
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

        Airport* dAirport=GetAirportByName(airline->mDepartureAirport);
        Airport* aAirport=GetAirportByName(airline->mArrivalAirport);
        if(dAirport!=NULL&&aAirport!=NULL)   //�жϻ����Ƿ����
        {
            airline->mAirportNo=aAirport->No;
            InsertAirlineGraph(dAirport,airline);    //���뵽ͼ
        }
    }
    infile.close();
    //cout<<AirlineArray.json();
}
//ͨ������Ų�ѯ����
Airport* AirlineGraph::GetAirportByName(string name)
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

//���뺽�� ����ʱ����
void AirlineGraph::InsertAirlineGraph(Airport* airport,Airline* airline)
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
        cout<<"======================================================================================================================";
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        cout<<endl<<"��"<<airport->mLocation<<" - "<<airport->mAirportName<<"��"<<"\t"<<endl<<endl;
        while(airline!=NULL)
        {
            cout<<airline->mAirlineName<<"\t";
            airline=airline->mNextAirline;
        }
    }
    cout<<endl<<"======================================================================================================================"<<endl;
}
//����json
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
            airline=airline->mNextAirline;
        }
    }
    return jsonArray;
}

void AirlineGraph::WriteAirlineJson()
{
    ofstream outfile;
    outfile.open("data/Airline.json");
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
    Airport* dAirport=GetAirportByName(airline->mDepartureAirport);
    Airport* aAirport=GetAirportByName(airline->mArrivalAirport);

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
        WriteAirlineJson(); //д�������º��������ļ�
    }
}

string AirlineGraph::GetAirportLocation(string airportName)
{
    return GetAirportByName(airportName)->mLocation;
}

//���뺽��Ż�ȡ���п��ܵĺ���
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
    vector<Airline*> vec;
    Airport* airport=mAirportHeadArray[no];
    Airline* airline=airport->mAdjAirline;
    while(airline!=NULL)
    {
        vec.push_back(airline);
        airline=airline->mNextAirline;
    }
    for(int i=1;i<vec.size();i++)  //��������
    {
        Airline* airline=vec[i];
        int j;
        for(j=i-1;j>=0&&(airline->GetAirlineDepartureTimeStamp())<vec[j]->GetAirlineDepartureTimeStamp();j--)
        {
            vec[j+1]=vec[j];
        }
        vec[j+1]=airline;
    }
    cout.setf(ios::left);
    cout<<endl;
    cout<<"========================================================================================================================================================================"<<endl;
    /*Airport* airport=mAirportHeadArray[no];
    Airline* airline=airport->mAdjAirline;*/
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

    for(vector<Airline*>::iterator it=vec.begin();it!=vec.end();it++)
    {
        Airline* airline=*it;
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
    }
}

vector<int>* AirlineGraph::GetAirportIdByLocation(string loc)
{
    vector<int>* vec=new vector<int>();
    for(int i=0;i<mAirportNumber;i++)
    {
        if(mAirportHeadArray[i]->mLocation==loc)
        {
            vec->push_back(i);
        }
    }
    return vec;
}

vector<Airline*>* AirlineGraph::GetAirlineByDACity(string departure,string arrival)
{
    vector<Airline*>* vec=new vector<Airline*>();
    vector<int>* dAirportVec=new vector<int>();
    dAirportVec=GetAirportIdByLocation(departure);
    for(vector<int>::iterator dit=dAirportVec->begin();dit!=dAirportVec->end();dit++)
    {
        Airline* airline=mAirportHeadArray[*dit]->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mArrivalCity==arrival)
            {
                vec->push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    return vec;
}

void AirlineGraph::ShowDACityAirlineByDiscountPrice(string departure,string arrival)
{
    vector<Airline*>* vec=GetAirlineByDACity(departure,arrival);

    for(int i=1;i<vec->size();i++)  //��������
    {
        Airline* airline=(*vec)[i];
        int j;
        for(j=i-1;j>=0&&(airline->GetPriceAfterDiscount())<(*vec)[j]->GetPriceAfterDiscount();j--)
        {
            (*vec)[j+1]=(*vec)[j];
        }
        (*vec)[j+1]=airline;
    }

    cout.setf(ios::left);

    cout<<endl<<"========================================================================================================================================================================"<<endl;
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
    for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
    {
        Airline* airline=*it;
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
    }
    cout<<endl<<"========================================================================================================================================================================"<<endl;
}

void AirlineGraph::ShowDACityAirlineByDepartureTime(string departure,string arrival)
{
    vector<Airline*>* vec=GetAirlineByDACity(departure,arrival);

    for(int i=1;i<vec->size();i++)
    {
        Airline* airline=(*vec)[i];
        int j;
        for(j=i-1;j>=0&&(airline->GetAirlineDepartureTimeStamp())<(*vec)[j]->GetAirlineDepartureTimeStamp();j--)
        {
            (*vec)[j+1]=(*vec)[j];
        }
        (*vec)[j+1]=airline;
    }

    cout.setf(ios::left);

    cout<<endl<<"========================================================================================================================================================================"<<endl;
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
    for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
    {
        Airline* airline=*it;
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
    }
    cout<<endl<<"========================================================================================================================================================================"<<endl;
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

void AirlineGraph::Book(Airline* airline)
{
    airline->mCurrentNumber=airline->mCurrentNumber+1;  //�Ѷ�����+1
    WriteAirlineJson(); //д�������±�������
}

void AirlineGraph::Unsubscribe(BookOrder* bookOrder)
{
    vector<Airline*>* vec=FindAirlineByName(bookOrder->mAirlineName);
    for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
    {
        if((*it)->mDepartureAirport==bookOrder->mDepartureAirport&&(*it)->mArrivalAirport==bookOrder->mArrivalAirport)
        {
            (*it)->mCurrentNumber=(*it)->mCurrentNumber-1;  //�Ѷ�����-1
            WriteAirlineJson(); //д�������±�������
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

vector<Route*>* AirlineGraph::GetAdvisableRouteWithBFS(string departure,string arrival,int departureTime,int arrivalTime)
{
    int InD[mAirportNumber]={0};
    int visit[mAirportNumber]={0};
    for(int i=0;i<mAirportNumber;i++)
    {
        Airline* airline=mAirportHeadArray[i]->mAdjAirline;
        while(airline!=NULL)
        {
            InD[GetAirportByName(airline->mArrivalAirport)->No]+=1; //ͳ�ƻ������
            airline=airline->mNextAirline;
        }
    }
    vector<int>* dAirportId=GetAirportIdByLocation(departure);
    vector<int>* aAirportId=GetAirportIdByLocation(arrival);
    vector<Route>* mainVec=new vector<Route>();
    vector<Route*>* retVec=new vector<Route*>();

    for(int i=0;i<dAirportId->size();i++)
    {
        for(int j=0;j<aAirportId->size();j++)
        {
            BFS((*dAirportId)[i],(*aAirportId)[j],InD,visit,mainVec);
            for(int k=0;k<mAirportNumber;k++)
            {
                visit[k]=0;
            }
        }
    }

    for(vector<Route>::iterator it=mainVec->begin();it!=mainVec->end();it++)
    {
        if((*it).mAirlineVec[(*it).mAirlineVec.size()-1]->GetAirlineDepartureTimeStamp()<arrivalTime
           &&(*it).mAirlineVec[(*it).mAirlineVec.size()-1]->GetAirlineArrivalTimeStamp()<arrivalTime
           &&(*it).mAirlineVec[0]->GetAirlineDepartureTimeStamp()>departureTime
           &&(*it).mAirlineVec[0]->GetAirlineArrivalTimeStamp()>departureTime)  //��ʱ������������������Ҳ����ָ�ҹ�����
        {
            (*it).SumToatalCost();
            retVec->push_back(&(*it)); //ɸѡ���������Ľ����ֱ��eraseɾ������� std::bad_alloc��ԭ��δ֪
        }else
        {
            //mainVec->erase(it);
        }
    }
    for(int i=1;i<retVec->size();i++)  //��������
    {
        Route* r=(*retVec)[i];
        int j;
        for(j=i-1;j>=0&&(r->mTotalCost)<(*retVec)[j]->mTotalCost;j--)
        {
            (*retVec)[j+1]=(*retVec)[j];
        }
        (*retVec)[j+1]=r;
    }

    return retVec;
}

void AirlineGraph::BFS(int f,int a,int* InD,int* visit,vector<Route>* mainVec)
{
    int k=1;   //����k
    queue<Route> q;
    Route r;
    r.mPrevNo=f;
    q.push(r);
    while(!q.empty())
    {
        Route r0=q.front();
        q.pop();
        Airline* airline=mAirportHeadArray[r0.mPrevNo]->mAdjAirline;
        while(airline!=NULL)
        {
            if(!r0.CheckPass(airline->mArrivalAirport))
            {
                if(((r0.mAirlineVec.size()>0&&r0.mAirlineVec[r0.mAirlineVec.size()-1]->GetAirlineArrivalTimeStamp()<airline->GetAirlineDepartureTimeStamp())
                        ||r0.mAirlineVec.size()==0) //������ʼ�����ߣ�����Ҫ�ж�ǰ�󺽰�ʱ���Ƿ�ϵ���
                   &&airline->GetAirlineDepartureTimeStamp()<airline->GetAirlineArrivalTimeStamp()) //����ҹ
                {
                    int no=GetAirportByName(airline->mArrivalAirport)->No;
                    if(visit[no]<k*InD[no])    //��ȵ�k��������һ��������ȵ�10��������BFS���̶ܳȣ���������ʱ�������
                    {
                        Route rNew=r0;
                        rNew.mAirlineVec.push_back(airline);
                        rNew.mPrevNo=no;
                        visit[no]+=1;
                        if(no!=a)
                        {
                            q.push(rNew);
                        }
                        else
                        {
                            mainVec->push_back(rNew);
                        }
                    }
                }
            }
            airline=airline->mNextAirline;
        }
    }
}

void AirlineGraph::DFS(int v,int a,int* InD,int* visit,vector< vector<Airline*> >* mainVec,vector<Airline*> routeVec)
{
    if(v!=a)    //δ����Ŀ�ĵ�
    {
        visit[v]+=1;
        Airline* airline=mAirportHeadArray[v]->mAdjAirline;
        while(airline!=NULL)
        {
            int no=airline->mAirportNo;
            bool tag=0;
            for(int i=0;i<routeVec.size();i++)
            {
                if(routeVec[i]->mArrivalAirport==airline->mArrivalAirport)
                {
                    tag=1;
                    break;
                }
            }
            if(routeVec.size()==0)
            {
                if(visit[no]<InD[no]&&!tag)   //�ȽϷ��ʴ���������Ƿ�С�����
                {
                    vector<Airline*> newRoute;
                    for(vector<Airline*>::iterator it=routeVec.begin(); it!=routeVec.end(); it++)
                    {
                        newRoute.push_back(*it);
                    }
                    newRoute.push_back(airline);
                    DFS(no,a,InD,visit,mainVec,newRoute);
                }
            }
            else if(routeVec[routeVec.size()-1]->GetAirlineArrivalTimeStamp()<airline->GetAirlineDepartureTimeStamp()/*&&airline->GetAirlineDepartureTimeStamp()<airline->GetAirlineArrivalTimeStamp()*/)
            {
                if(visit[no]<InD[no]&&!tag)   //�ȽϷ��ʴ���������Ƿ�С�����
                {
                    vector<Airline*> newRoute;
                    for(vector<Airline*>::iterator it=routeVec.begin(); it!=routeVec.end(); it++)
                    {
                        newRoute.push_back(*it);
                    }
                    newRoute.push_back(airline);
                    DFS(no,a,InD,visit,mainVec,newRoute);
                }
            }
            airline=airline->mNextAirline;
        }
    }else   //����Ŀ�ĵأ���ֹDFS
    {
        visit[v]+=1;
        mainVec->push_back(routeVec);   //��·�������� mainVec
    }
}

Airline* AirlineGraph::GetMinCostAirline(int f,int t)
{
    //cout<<"f\t"<<f<<"\tt\t"<<t<<"\t";
    Airline* airline=mAirportHeadArray[f]->mAdjAirline;
    Airline* ret=NULL;
    int cost=INT_MAX;

    while(airline!=NULL)
    {
        if(airline->mAirportNo==t&&airline->GetPriceAfterDiscount()<cost)
        {
            cost=airline->GetPriceAfterDiscount();
            ret=airline;
        }
        airline=airline->mNextAirline;
    }
    return ret;
}

Route** AirlineGraph::Dijkstra(int v)
{
    int TotalCost[mAirportNumber];
    int path[mAirportNumber];
    bool visit[mAirportNumber];

    for(int i=0; i<mAirportNumber; i++)
    {
        TotalCost[i]=INT_MAX;
        path[i]=-1;
        visit[i]=0;
    }

    TotalCost[v]=0;
    visit[v]=1;

    Airline* airline=mAirportHeadArray[v]->mAdjAirline;
    int u=v;

    for(int i=0; i<mAirportNumber-1; i++)
    {
        while(airline!=NULL)    //���³��ȡ�·����Ϣ
        {
            int k=airline->mAirportNo;
            if(visit[k]!=1&&TotalCost[k]+airline->GetPriceAfterDiscount()<TotalCost[k])
            {
                TotalCost[k]=TotalCost[k]+airline->GetPriceAfterDiscount();
                path[k]=u;
            }
            airline=airline->mNextAirline;
        }
        int tmpMin=INT_MAX;
        for(int j=0; j<mAirportNumber; j++) //������һ�����ʽ��
        {
            if(TotalCost[j]<tmpMin&&visit[j]==0)
            {
                tmpMin=TotalCost[j];
                u=j;
            }
        }
        visit[u]=1;
        airline=mAirportHeadArray[u]->mAdjAirline;
    }

    Route** routeArray=new Route*[mAirportNumber];

    /*for(int i=0;i<mAirportNumber;i++)
        cout<<"i\t"<<i<<"\t"<<path[i]<<endl;*/
    for(int i=0;i<mAirportNumber;i++)
    {
        if(path[i]!=-1) //��v�����û�пɼ�·��
        {
            stack<int> s;
            int j=i;
            while(j!=v)   //����·����ѹջ
            {
                s.push(j);
                j=path[j];
            }
            int prev=v;
            Route* r=new Route();
            while(!s.empty())   //��ջ������·��
            {
                int f=s.top();
                Airline* airline=GetMinCostAirline(prev,f);
                r->mAirlineVec.push_back(airline);
                s.pop();
                prev=f;
            }
            routeArray[i]=r;
        }else
        {
            routeArray[i]=NULL;
        }
    }
    return routeArray;
}
