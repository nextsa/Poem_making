#include <QCoreApplication>
#include <fstream>
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

using namespace std;

void takeString(vector<string>& fpoem, vector<string>& spoem, ifstream &fin1, ofstream &fout, mutex& m_in, mutex& m_out)
{
    m_in.lock();
    char poemStr1[100];
    while (!fin1.eof())
    {
        fin1.getline(poemStr1, 100);
        fpoem.push_back(poemStr1);
    }
    m_in.unlock();

    m_out.lock();
    for(int i = 0;i < signed(fpoem.size());i++)
    {
        fout << fpoem[i] << endl << spoem[i] << endl;
    }
    m_out.unlock();
}

/*
void takeString(ifstream& fin1, ifstream& fin2, ofstream& fout, mutex& m_p1, mutex& m_p2, mutex& m_out)
{
    setlocale(LC_ALL, "Russian");

    m_p1.lock();
    char poemStr1[100];
    fin1.getline(poemStr1, 100);
    m_p1.unlock();

    m_p2.lock();
    char poemStr2[100];
    fin2.getline(poemStr2, 100);
    m_p2.unlock();



    m_out.lock();
    fout << poemStr1 << endl << poemStr2 << endl;
    m_out.unlock();


}
*/

/*
string threadReading(ifstream &fin1)
{

    char poemStr1[100];
    fin1.getline(poemStr1, 100);
    return poemStr1;
}
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    mutex m_in;
    mutex m_out;

    ofstream fout("bc.txt");
    ifstream fin1("f1.txt");
    ifstream fin2("f2.txt");
    vector<string> fpoem;
    vector<string> spoem;

    thread push_thread(takeString, ref(fpoem), ref(spoem), ref(fin1), ref(fout), ref(m_in), ref(m_out));
    push_thread.detach();
    char poemStr2[100];
    while (!fin2.eof())
    {
        fin2.getline(poemStr2, 100);
        spoem.push_back(poemStr2);
    }


 /*
    char poemStr2[100];
    fin2.getline(poemStr2, 100);
    fout << poemStr2 << endl;
    thread push_thread(takeString, ref(fin1), ref(fout), ref(m_in), ref(m_out));
 //   thread push_thread2(takeString, ref(fin2), ref(fout), ref(m_in), ref(m_out));






    mutex m_p1;
    mutex m_p2;
    mutex m_out;
    ifstream fin1("f1.txt");
    ifstream fin2("f2.txt");

    thread push_thread(takeString, ref(fin1), ref(fin2), ref(fout), ref(m_p1), ref(m_p2), ref(m_out));

    char poemStr2[100];
    fin2.getline(poemStr2, 100);
    fout << poemStr2 << endl;
    thread push_thread(takeString, ref(fin1), ref(fout), ref(m_in), ref(m_out));
 //   thread push_thread2(takeString, ref(fin2), ref(fout), ref(m_in), ref(m_out));

*/

    /*
    int i = 0;

    while(i < 7)
    {
        fin2.getline(poemStr2, 100);
        fout << poemStr2 << endl;
        i++;
    }
*/
 //   thread thr(threadReading, fin1);
 //   thr.join();



/*
//    setlocale(LC_ALL, "rus");
//    ifstream fin1("f1.txt");
    ifstream fin2("f2.txt");
    ofstream fout("out.txt");

    char poemStr1[100];
    char poemStr2[100];

    int i = 0;
    while(!fin1.eof() && !fin2.eof())
    {
//        fin1.getline(poemStr1, 100);
        fin2.getline(poemStr2, 100);
        fout << poemStr1 << endl << poemStr2 << endl;
        i += 2;
        if (i%4 == 0)
        {
            fout << endl;
        }
    }
    fin1.close();
    fin2.close();
    fout.close();
*/
    return a.exec();
}
