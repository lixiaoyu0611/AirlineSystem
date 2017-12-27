#include "System.h"

System::System()
{
    cout.setf(ios::left);
    ShowWelcome();
    mAirlineGraph=new AirlineGraph();
    cout<<endl<<"�����������ݼ�����ϡ���"<<endl;
    mBookOrderVector=NULL;
    LoadBookOrder();
    cout<<"�������ݼ�����ϡ���"<<endl;
    MenuDaemon();
}

System::~System()
{
    //dtor
}

void System::ShowWelcome()
{
    cout<<"��ӭʹ�û�ƱԤ��ϵͳ��"<<endl;
    time_t timep;
    time (&timep);
    char timestr[64];
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S",localtime(&timep));
    cout<<"��¼ʱ�䣺"<<timestr<<endl;
}

void System::LoadBookOrder()
{
    ifstream infile;
    string s;
    infile.open("data/Book.json");
    ostringstream tmp;
    tmp<<infile.rdbuf();
    infile.close();
    s=tmp.str();
    Array BookArray;
    BookArray.parse(s);  //����json
    if(mBookOrderVector!=NULL)
    {
        delete mBookOrderVector;
    }
    mBookOrderVector=new vector<BookOrder*>();
    for(int i=0;i<BookArray.size();i++)  //���溽�ߵ�vector
    {
        BookOrder* bookOrder=new BookOrder();
        bookOrder->mName=BookArray.get<Object>(i).get<String>("����");
        bookOrder->mIdNumber=BookArray.get<Object>(i).get<String>("֤����");
        bookOrder->mAirlineName=BookArray.get<Object>(i).get<String>("�����");
        bookOrder->mCompany=BookArray.get<Object>(i).get<String>("��˾");
        bookOrder->mDepartureAirport=BookArray.get<Object>(i).get<String>("��ɻ���");
        bookOrder->mArrivalAirport=BookArray.get<Object>(i).get<String>("�������");
        bookOrder->mDepartureTime=BookArray.get<Object>(i).get<String>("���ʱ��");
        bookOrder->mArrivalTime=BookArray.get<Object>(i).get<String>("����ʱ��");
        bookOrder->mAirplaneModel=BookArray.get<Object>(i).get<String>("����");
        bookOrder->mDepartureCity=BookArray.get<Object>(i).get<String>("��ʼ����");
        bookOrder->mArrivalCity=BookArray.get<Object>(i).get<String>("�������");
        bookOrder->mPrice=BookArray.get<Object>(i).get<Number>("����۸�");
        mBookOrderVector->push_back(bookOrder);
    }
}

void System::InsertAirlineInfo()
{
    Airline* airline=new Airline();
    cout<<endl;
    cout<<"�����뺽�չ�˾��"<<endl;
    cin>>airline->mCompany;
    cout<<"�����뺽��ţ�"<<endl;
    cin>>airline->mAirlineName;
    cout<<"���������ʱ�䣺"<<endl;
    cin>>airline->mDepartureTime;
    cout<<"�����뵽��ʱ�䣺"<<endl;
    cin>>airline->mArrivalTime;
    cout<<"��������ɻ�����"<<endl;
    cin>>airline->mDepartureAirport;
    airline->mDepartureCity=mAirlineGraph->GetAirportLocation(airline->mDepartureAirport);
    cout<<"�����뵽�������"<<endl;
    cin>>airline->mArrivalAirport;
    airline->mArrivalCity=mAirlineGraph->GetAirportLocation(airline->mArrivalAirport);
    cout<<"��������ͣ�"<<endl;
    cin>>airline->mAirplaneModel;
    cout<<"������������"<<endl;
    cin>>airline->mCapacity;
    cout<<"�����뵱ǰ�˿�������"<<endl;
    cin>>airline->mCurrentNumber;
    if(airline->mCapacity<airline->mCurrentNumber)
    {
        cout<<"�Ƿ����룡����С�ڵ�ǰ�˿�������"<<endl;
        return;
    }
    cout<<"������Ʊ�ۣ�"<<endl;
    cin>>airline->mPrice;
    cout<<"�������ۿۣ�1000%����"<<endl;
    cin>>airline->mIntDiscount;
    mAirlineGraph->InsertAirline(airline);
    cout<<endl<<"����"<<airline->mAirlineName<<"¼��ɹ���"<<endl;
}

void System::RemoveAirline()
{
    cout<<endl<<"�����뺽��ţ�"<<endl;
    string name;
    cin>>name;
    vector<Airline*>* vec=mAirlineGraph->FindAirlineByName(name);
    if(vec->size()==0)
    {
        cout<<endl<<"�޼�¼��"<<endl;
        return;
    }else if(vec->size()==1)
    {
        mAirlineGraph->RemoveAirline((*vec)[0]);
        cout<<endl<<"����"<<name<<"��ɾ����"<<endl;
    }else
    {
        cout<<endl<<"==========================================="<<endl;
        cout<<"����"<<vec->size()<<"�����:"<<endl;
        for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
        {
            cout<<"��"<<it-vec->begin()+1<<"��"<<endl;
            Airline* airline=(*it);
            cout<<endl;
            cout<<setw(12)<<"�����:"<<airline->mAirlineName<<endl;
            cout<<setw(12)<<"���չ�˾:"<<airline->mCompany<<endl;
            cout<<setw(12)<<"������:"<<airline->mDepartureCity<<endl;
            cout<<setw(12)<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
            cout<<setw(12)<<"Ŀ�ĵ�:"<<airline->mArrivalCity<<endl;
            cout<<setw(12)<<"��½����:"<<airline->mArrivalAirport<<endl;
            cout<<setw(12)<<"���ʱ��:"<<airline->mDepartureTime<<endl;
            cout<<setw(12)<<"�ִ�ʱ��:"<<airline->mArrivalTime<<endl;
            cout<<setw(12)<<"����:"<<airline->mAirplaneModel<<endl;
            cout<<setw(12)<<"Ʊ��:"<<airline->mPrice<<endl;
            cout<<setw(12)<<"�ۿ�:"<<airline->mIntDiscount/1000.0<<endl;
            cout<<setw(12)<<"�ۺ�Ʊ��:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
            cout<<setw(12)<<"�ؿ���:"<<airline->mCapacity<<endl;
            cout<<setw(12)<<"����:"<<airline->mCurrentNumber<<endl;
            cout<<setw(12)<<"��Ʊ:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
            cout<<endl;
            cout<<"==========================================="<<endl;
        }

        cout<<"������ɾ���������������֣�"<<endl;
        int i;
        cin>>i;
        while(i>vec->size()||i<=0)
        {
            cout<<endl<<"���벻�Ϸ������������룡"<<endl;
            cin>>i;
        }
        mAirlineGraph->RemoveAirline((*vec)[i-1]);
        cout<<endl<<"����"<<name<<"��ɾ����"<<endl;
    }
}

void System::ShowAllAirlineToUser()
{
    mAirlineGraph->ShowAllAirlineToUser();
}

void System::ShowAirlineByAirport(int no)
{
    mAirlineGraph->ShowAirlineByAirport(no);
    cout<<endl<<"========================================================================================================================================================================"<<endl;
}

void System::ShowAirlineByCity(string city)
{
    cout<<city;
    mAirlineGraph->ShowAirlineByCity(city);
}

void System::SearchAirlineByName(string name)
{
    vector<Airline*>* vec=mAirlineGraph->FindAirlineByName(name);
    if(vec->size()==0)
    {
        cout<<endl<<"�޼�¼��"<<endl;
    }
    else
    {
        cout<<endl<<"==========================================="<<endl;
        cout<<"����"<<vec->size()<<"�����:"<<endl;
        for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
        {
            Airline* airline=(*it);
            cout<<endl;
            cout<<setw(12)<<"�����:"<<airline->mAirlineName<<endl;
            cout<<setw(12)<<"���չ�˾:"<<airline->mCompany<<endl;
            cout<<setw(12)<<"������:"<<airline->mDepartureCity<<endl;
            cout<<setw(12)<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
            cout<<setw(12)<<"Ŀ�ĵ�:"<<airline->mArrivalCity<<endl;
            cout<<setw(12)<<"��½����:"<<airline->mArrivalAirport<<endl;
            cout<<setw(12)<<"���ʱ��:"<<airline->mDepartureTime<<endl;
            cout<<setw(12)<<"�ִ�ʱ��:"<<airline->mArrivalTime<<endl;
            cout<<setw(12)<<"����:"<<airline->mAirplaneModel<<endl;
            cout<<setw(12)<<"Ʊ��:"<<airline->mPrice<<endl;
            cout<<setw(12)<<"�ۿ�:"<<airline->mIntDiscount/1000.0<<endl;
            cout<<setw(12)<<"�ۺ�Ʊ��:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
            cout<<setw(12)<<"�ؿ���:"<<airline->mCapacity<<endl;
            cout<<setw(12)<<"����:"<<airline->mCurrentNumber<<endl;
            cout<<setw(12)<<"��Ʊ:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
            cout<<endl;
            cout<<"==========================================="<<endl;
        }
    }
}

void System::Book()
{
    string name;
    cout<<endl<<"�����뺽��ţ�"<<endl;
    cin>>name;

    vector<Airline*>* vec=mAirlineGraph->FindAirlineByName(name);
    if(vec->size()==0)
    {
        cout<<endl<<"�޼�¼��"<<endl;
        return;
    }
    else if(vec->size()==1)
    {
        Airline* airline=(*vec)[0];

        cout<<"==========================================="<<endl;
        cout<<endl;
        cout<<setw(12)<<"�����:"<<airline->mAirlineName<<endl;
        cout<<setw(12)<<"���չ�˾:"<<airline->mCompany<<endl;
        cout<<setw(12)<<"������:"<<airline->mDepartureCity<<endl;
        cout<<setw(12)<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
        cout<<setw(12)<<"Ŀ�ĵ�:"<<airline->mArrivalCity<<endl;
        cout<<setw(12)<<"��½����:"<<airline->mArrivalAirport<<endl;
        cout<<setw(12)<<"���ʱ��:"<<airline->mDepartureTime<<endl;
        cout<<setw(12)<<"�ִ�ʱ��:"<<airline->mArrivalTime<<endl;
        cout<<setw(12)<<"����:"<<airline->mAirplaneModel<<endl;
        cout<<setw(12)<<"Ʊ��:"<<airline->mPrice<<endl;
        cout<<setw(12)<<"�ۿ�:"<<airline->mIntDiscount/1000.0<<endl;
        cout<<setw(12)<<"�ۺ�Ʊ��:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
        cout<<setw(12)<<"�ؿ���:"<<airline->mCapacity<<endl;
        cout<<setw(12)<<"����:"<<airline->mCurrentNumber<<endl;
        cout<<setw(12)<<"��Ʊ:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
        cout<<endl;
        cout<<"==========================================="<<endl;


        if(airline->mCapacity==airline->mCurrentNumber)
        {
            cout<<endl<<"���ۿգ�"<<endl;
            return;
        }
        Object jsonObj;
        string s1,s2;
        cout<<endl<<"������������"<<endl;
        cin>>s1;
        jsonObj<<"����"<<s1;
        cout<<endl<<"������֤���ţ�"<<endl;
        cin>>s2;
        jsonObj<<"֤����"<<s2;

        jsonObj<<"��˾"<<airline->mCompany;
        jsonObj<<"�����"<<airline->mAirlineName;
        jsonObj<<"��ʼ����"<<airline->mDepartureCity;
        jsonObj<<"��ɻ���"<<airline->mDepartureAirport;
        jsonObj<<"�������"<<airline->mArrivalCity;
        jsonObj<<"�������"<<airline->mArrivalAirport;
        jsonObj<<"���ʱ��"<<airline->mDepartureTime;
        jsonObj<<"����ʱ��"<<airline->mArrivalTime;
        jsonObj<<"����"<<airline->mAirplaneModel;
        jsonObj<<"����۸�"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0));

        cout<<"==========================================="<<endl;
        cout<<endl;
        cout<<"================ Ԥ���ɹ� ================="<<endl;
        cout<<endl;
        cout<<setw(12)<<"����:"<<s1<<endl;
        cout<<setw(12)<<"֤����:"<<s2<<endl;
        cout<<setw(12)<<"�����:"<<airline->mAirlineName<<endl;
        cout<<setw(12)<<"���չ�˾:"<<airline->mCompany<<endl;
        cout<<setw(12)<<"������:"<<airline->mDepartureCity<<endl;
        cout<<setw(12)<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
        cout<<setw(12)<<"Ŀ�ĵ�:"<<airline->mArrivalCity<<endl;
        cout<<setw(12)<<"��½����:"<<airline->mArrivalAirport<<endl;
        cout<<setw(12)<<"���ʱ��:"<<airline->mDepartureTime<<endl;
        cout<<setw(12)<<"�ִ�ʱ��:"<<airline->mArrivalTime<<endl;
        cout<<setw(12)<<"����:"<<airline->mAirplaneModel<<endl;
        cout<<setw(12)<<"����۸�:"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0))<<endl;
        cout<<endl;
        cout<<"==========================================="<<endl;

        Array bookArray=GenerateBookJson();
        bookArray<<jsonObj;
        //cout<<bookArray.json();

        ofstream outfile;
        outfile.open("data/Book.json");

        outfile<<bookArray.json();
        outfile.close();

        mAirlineGraph->Book(airline);

        LoadBookOrder();
    }
    else if(vec->size()>1)
    {
        cout<<"����"<<vec->size()<<"�����:"<<endl;
        cout<<"==========================================="<<endl;
        for(int i=0;i<vec->size();i++)
        {
            Airline* airline=(*vec)[i];
            cout<<"��"<<i+1<<"��"<<endl;
            cout<<endl;
            cout<<setw(12)<<"�����:"<<airline->mAirlineName<<endl;
            cout<<setw(12)<<"���չ�˾:"<<airline->mCompany<<endl;
            cout<<setw(12)<<"������:"<<airline->mDepartureCity<<endl;
            cout<<setw(12)<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
            cout<<setw(12)<<"Ŀ�ĵ�:"<<airline->mArrivalCity<<endl;
            cout<<setw(12)<<"��½����:"<<airline->mArrivalAirport<<endl;
            cout<<setw(12)<<"���ʱ��:"<<airline->mDepartureTime<<endl;
            cout<<setw(12)<<"�ִ�ʱ��:"<<airline->mArrivalTime<<endl;
            cout<<setw(12)<<"����:"<<airline->mAirplaneModel<<endl;
            cout<<setw(12)<<"Ʊ��:"<<airline->mPrice<<endl;
            cout<<setw(12)<<"�ۿ�:"<<airline->mIntDiscount/1000.0<<endl;
            cout<<setw(12)<<"�ۺ�Ʊ��:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
            cout<<setw(12)<<"�ؿ���:"<<airline->mCapacity<<endl;
            cout<<setw(12)<<"����:"<<airline->mCurrentNumber<<endl;
            cout<<setw(12)<<"��Ʊ:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
            cout<<endl;
            cout<<"==========================================="<<endl;
        }

        cout<<"������Ԥ���������������֣�"<<endl;
        int i;
        cin>>i;
        while(i>vec->size()||i<=0)
        {
            cout<<endl<<"���벻�Ϸ������������룡"<<endl;
            cin>>i;
        }
        Airline* airline=(*vec)[i-1];

        if(airline->mCapacity==airline->mCurrentNumber)
        {
            cout<<endl<<"���ۿգ�"<<endl;
            return;
        }
        Object jsonObj;
        string s1,s2;
        cout<<endl<<"������������"<<endl;
        cin>>s1;
        jsonObj<<"����"<<s1;
        cout<<endl<<"������֤���ţ�"<<endl;
        cin>>s2;
        jsonObj<<"֤����"<<s2;

        jsonObj<<"��˾"<<airline->mCompany;
        jsonObj<<"�����"<<airline->mAirlineName;
        jsonObj<<"��ʼ����"<<airline->mDepartureCity;
        jsonObj<<"��ɻ���"<<airline->mDepartureAirport;
        jsonObj<<"�������"<<airline->mArrivalCity;
        jsonObj<<"�������"<<airline->mArrivalAirport;
        jsonObj<<"���ʱ��"<<airline->mDepartureTime;
        jsonObj<<"����ʱ��"<<airline->mArrivalTime;
        jsonObj<<"����"<<airline->mAirplaneModel;
        jsonObj<<"����۸�"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0));

        cout<<"==========================================="<<endl;
        cout<<endl;
        cout<<"================ Ԥ���ɹ� ================="<<endl;
        cout<<endl;
        cout<<setw(12)<<"����:"<<s1<<endl;
        cout<<setw(12)<<"֤����:"<<s2<<endl;
        cout<<setw(12)<<"�����:"<<airline->mAirlineName<<endl;
        cout<<setw(12)<<"���չ�˾:"<<airline->mCompany<<endl;
        cout<<setw(12)<<"������:"<<airline->mDepartureCity<<endl;
        cout<<setw(12)<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
        cout<<setw(12)<<"Ŀ�ĵ�:"<<airline->mArrivalCity<<endl;
        cout<<setw(12)<<"��½����:"<<airline->mArrivalAirport<<endl;
        cout<<setw(12)<<"���ʱ��:"<<airline->mDepartureTime<<endl;
        cout<<setw(12)<<"�ִ�ʱ��:"<<airline->mArrivalTime<<endl;
        cout<<setw(12)<<"����:"<<airline->mAirplaneModel<<endl;
        cout<<setw(12)<<"����۸�:"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0))<<endl;
        cout<<endl;
        cout<<"==========================================="<<endl;

        Array bookArray=GenerateBookJson();
        bookArray<<jsonObj;
        //cout<<bookArray.json();

        ofstream outfile;
        outfile.open("data/Book.json");

        outfile<<bookArray.json();
        outfile.close();

        mAirlineGraph->Book(airline);

        LoadBookOrder();
    }
}

int System::GetBookOrderNum()
{
    return mBookOrderVector->size();
}

Array System::GenerateBookJson()
{
    Array jsonArray;
    for(int i=0; i<GetBookOrderNum(); i++)
    {
        BookOrder* bookOrder=(*mBookOrderVector)[i];
        Object jsonObj;
        jsonObj<<"����"<<bookOrder->mName;
        jsonObj<<"֤����"<<bookOrder->mIdNumber;
        jsonObj<<"�����"<<bookOrder->mAirlineName;
        jsonObj<<"��˾"<<bookOrder->mCompany;
        jsonObj<<"��ɻ���"<<bookOrder->mDepartureAirport;
        jsonObj<<"�������"<<bookOrder->mArrivalAirport;
        jsonObj<<"���ʱ��"<<bookOrder->mDepartureTime;
        jsonObj<<"����ʱ��"<<bookOrder->mArrivalTime;
        jsonObj<<"��ʼ����"<<bookOrder->mDepartureCity;
        jsonObj<<"�������"<<bookOrder->mArrivalCity;
        jsonObj<<"����"<<bookOrder->mAirplaneModel;
        jsonObj<<"����۸�"<<bookOrder->mPrice;

        jsonArray<<jsonObj;
    }
    return jsonArray;
}

void System::ShowBookList()
{
    cout<<endl;
    for(int i=0;i<mBookOrderVector->size();i++)
    {
        BookOrder* bookOrder=(*mBookOrderVector)[i];
        cout<<"==========================================="<<endl;
        cout<<"��"<<i+1<<"��"<<endl;
        cout<<endl;
        cout<<setw(12)<<"����:"<<bookOrder->mName<<endl;
        cout<<setw(12)<<"֤����:"<<bookOrder->mIdNumber<<endl;
        cout<<setw(12)<<"�����:"<<bookOrder->mAirlineName<<endl;
        cout<<setw(12)<<"���չ�˾:"<<bookOrder->mCompany<<endl;
        cout<<setw(12)<<"������:"<<bookOrder->mDepartureCity<<endl;
        cout<<setw(12)<<"��ɻ���:"<<bookOrder->mDepartureAirport<<endl;
        cout<<setw(12)<<"Ŀ�ĵ�:"<<bookOrder->mArrivalCity<<endl;
        cout<<setw(12)<<"��½����:"<<bookOrder->mArrivalAirport<<endl;
        cout<<setw(12)<<"���ʱ��:"<<bookOrder->mDepartureTime<<endl;
        cout<<setw(12)<<"�ִ�ʱ��:"<<bookOrder->mArrivalTime<<endl;
        cout<<setw(12)<<"����:"<<bookOrder->mAirplaneModel<<endl;
        cout<<setw(12)<<"����۸�:"<<bookOrder->mPrice<<endl;
        cout<<endl;
        cout<<"==========================================="<<endl;
    }
}

void System::Unsubscribe()
{
    ShowBookList();
    cout<<endl<<"��1��ͨ��������Ʊ"<<endl<<"��2��ͨ��֤������Ʊ"<<endl<<"��3��ͨ�����������Ʊ"<<endl;
    int i;
    cin>>i;
    while(i>3||i<1)
    {
        cout<<endl<<"���벻�Ϸ������������룡"<<endl;
        cin>>i;
    }
    string s;
    switch(i)
    {
    case 1:
        cout<<endl<<"������������"<<endl;
        cin>>s;
        UnsubscribeByName(s);
        break;
    case 2:
        cout<<endl<<"������֤���ţ�"<<endl;
        cin>>s;
        UnsubscribeByIdNum(s);
        break;
    case 3:
        cout<<endl<<"������������ţ�"<<endl;
        cin>>i;
        while(i>GetBookOrderNum()||i<=0)
        {
            cout<<endl<<"���벻�Ϸ������������룡"<<endl;
            cin>>i;
        }
        UnsubscribeByNo(i);
        break;
    }

    Array bookArray=GenerateBookJson();
    //cout<<bookArray.json();

    ofstream outfile;
    outfile.open("data/Book.json");

    outfile<<bookArray.json();
    outfile.close();

    LoadBookOrder();
}

void System::UnsubscribeByName(string name)
{
    vector<BookOrder*>::iterator it;
    for(it=mBookOrderVector->begin();it!=mBookOrderVector->end();it++)
    {
        if((*it)->mName==name)
        {
            mAirlineGraph->Unsubscribe(*it);    //��������ͼ��ȡ������������Ҳ�ǣ�����ɾ�����������ָ���һ��Ԫ��
            mBookOrderVector->erase(it);
            break;
        }
    }
    if(it==mBookOrderVector->end())
    {
        cout<<endl<<"�޼�¼��"<<endl;
    }
}

void System::UnsubscribeByIdNum(string Id)
{
    vector<BookOrder*>::iterator it;
    for(it=mBookOrderVector->begin();it!=mBookOrderVector->end();it++)
    {
        if((*it)->mIdNumber==Id)
        {
            mAirlineGraph->Unsubscribe(*it);
            mBookOrderVector->erase(it);
            break;
        }
    }
    if(it==mBookOrderVector->end())
    {
        cout<<endl<<"�޼�¼��"<<endl;
    }
}

void System::UnsubscribeByNo(int no)
{
    vector<BookOrder*>::iterator it=mBookOrderVector->begin();
    mAirlineGraph->Unsubscribe(*(it+no-1));
    mBookOrderVector->erase(it+no-1);
}

void System::ShowAdvisableRoute(string departureCity,string arrivalCity,string departureTime,string arrivalTime)
{
    TimeUtil timeUtil;
    int dTime=timeUtil.GetTimeStamp(departureTime);
    int aTime=timeUtil.GetTimeStamp(arrivalTime);
    vector<Route*>* vec=mAirlineGraph->GetAdvisableRouteWithBFS(departureCity,arrivalCity,dTime,aTime);
    if(vec->size()==0)
    {
        cout<<endl<<"��Ǹ���޿��к���"<<endl;
    }else
    {
        cout<<endl<<"========================================================================================================================================================================"<<endl;
        for(vector<Route*>::iterator it=vec->begin(); it!=vec->end(); it++)
        {
            cout<<endl;
            (*it)->ShowRoute();
        }
        cout<<endl<<endl<<"========================================================================================================================================================================"<<endl;
    }
}

void System::ShowBestAirlineNetwork(string departureCity)
{
    vector<int>* vec=mAirlineGraph->GetAirportIdByLocation(departureCity);
    if(vec->size()==0)
    {
        cout<<endl<<"��Ǹ���ó������޿��к���"<<endl;
    }
    for(int j=0; j<vec->size(); j++)
    {
        cout<<endl<<"========================================================================================================================================================================"<<endl;
        cout<<endl<<"�ӡ�"<<departureCity<<" - "<<mAirlineGraph->mAirportHeadArray[(*vec)[j]]->mAirportName<<"������"<<endl<<endl;
        Route** r=mAirlineGraph->Dijkstra((*vec)[j]);   //���� Dijkstra �㷨
        for(int i=0; i<mAirlineGraph->mAirportNumber; i++)
        {
            string outstr="��"+mAirlineGraph->mAirportHeadArray[i]->mLocation+" - "+mAirlineGraph->mAirportHeadArray[i]->mAirportName+"��";
            if(r[i]!=NULL)
            {
                cout<<setw(30)<<outstr;
                Route* route=r[i];
                route->SumToatalCost();
                route->ShowRoute();
                cout<<endl;
            }
            else
            {
                cout<<setw(30)<<outstr<<"NULL"<<endl;
            }
        }
    }
    cout<<endl<<"========================================================================================================================================================================"<<endl;

}

void System::RecommandBestRoute(string departureCity,string arrivalCity)
{

    vector<int>* dVec=mAirlineGraph->GetAirportIdByLocation(departureCity);
    vector<int>* aVec=mAirlineGraph->GetAirportIdByLocation(arrivalCity);
    if(dVec->size()==0||aVec->size()==0)
    {
        cout<<endl<<"��Ǹ���޿��к���"<<endl;
        return;
    }
    Route* routeArray[dVec->size()][aVec->size()];
    for(int i=0;i<dVec->size();i++)
    {
        for(int j=0;j<aVec->size();j++)
        {
            Route** r=mAirlineGraph->Dijkstra((*dVec)[i]);   //���� Dijkstra �㷨
            r[(*aVec)[j]]->SumToatalCost();
            routeArray[i][j]=r[(*aVec)[j]];
        }
    }
    Route* best=routeArray[0][0];
    for(int i=0;i<dVec->size();i++)
    {
        for(int j=0;j<aVec->size();j++)
        {
            if(routeArray[i][j]->mTotalCost<best->mTotalCost)
            best=routeArray[i][j];
        }
    }
    cout<<endl;
    best->ShowRoute();
    cout<<endl;
}

void System::MenuDaemon()
{
    ShowMenu(0);

    int operation=0;
    cin>>operation;

    while(operation)
    {
        int x;
        string s1,s2,s3,s4;
        switch(operation)
        {
        case 1:
            InsertAirlineInfo();
            break;
        case 2:
            RemoveAirline();
            break;
        case 3:
            ShowAllAirlineToUser();
            break;
        case 4:
            ShowMenu(3);
            cin>>s1;
            SearchAirlineByName(s1);
            break;
        case 5:
            ShowBookList();
            break;
        case 6:
            Book();
            break;
        case 7:
            Unsubscribe();
            break;
        case 8:
            ShowMenu(1);
            cin>>x;
            if(x==1)
            {
                ShowMenu(2);
                cin>>s1>>s2;
                mAirlineGraph->ShowDACityAirlineByDepartureTime(s1,s2);
            }else if(x==2)
            {
                ShowMenu(2);
                cin>>s1>>s2;
                mAirlineGraph->ShowDACityAirlineByDiscountPrice(s1,s2);
            }
            break;
        case 9:
            ShowMenu(4);
            cin>>s1>>s2>>s3>>s4;
            ShowAdvisableRoute(s1,s2,s3,s4);
            break;
        case 10:
            ShowMenu(5);
            cin>>s1;
            ShowBestAirlineNetwork(s1);
            break;
        case 11:
            ShowMenu(6);
            cin>>s1>>s2;
            RecommandBestRoute(s1,s2);
            break;
        }
        ShowMenu(0);
        cin>>operation;
    }
}

void System::ShowMenu(int i)
{
    switch(i)
    {
    case 0:
        cout<<endl
        <<"1) ¼�뺽��"<<endl
        <<"2) ɾ������"<<endl
        <<"3) ���ȫ�����ߣ����������ã�4000��������Ϣ���Դ󣡣�����"<<endl
        <<"4������Ų�ѯ����"<<endl
        <<"5���鿴�������"<<endl
        <<"6����Ʊ"<<endl
        <<"7����Ʊ"<<endl
        <<"8����ѯ�Ǽ亽��"<<endl
        <<"9��������·���"<<endl
        <<"10����������"<<endl
        <<"11���Ƽ�������·"<<endl
        <<endl
        <<"0���˳�"<<endl;
        break;
    case 1:
        cout<<endl
        <<"��ѡ������ʽ"<<endl
        <<"1������ʱ��"<<endl
        <<"2���ۺ�Ʊ��"<<endl
        <<"0���˳�"<<endl;
        break;
    case 2:
        cout<<endl
        <<"������������к͵�����У�"<<endl;
        break;
    case 3:
        cout<<endl
        <<"�����뺽��ţ�"<<endl;
        break;
    case 4:
        cout<<endl
        <<"������������С�������С�����ʱ��͵���ʱ�䣺"<<endl;
        break;
    case 5:
        cout<<endl
        <<"������������У�"<<endl;
        break;
    case 6:
        cout<<endl
        <<"������������к͵�����У�"<<endl;
        break;
    }
}
