#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <assert.h>

using namespace std;

struct el
{
  double data;
  el* next;
  el* prev;
};

struct lista
{
    int size;
    el* head;
    el* tail;

};

class List{

    public:
        void init(lista &L)
        {
          L.head  = L.tail  = NULL;
          L.size = 0;
        }

        void printRightToLeft(lista &L)
        {
          el* p;

          cout << "Rozmiar listy " << L.size << " elementy ( od prawej do lewej )" << endl;
          cout << "[" ;
          p = L.head;
          while(p)
          {
            cout << " " << p->data;
            p = p->next;
          }
          cout << " ]\n\n";
        }

        void printLeftToRight(lista &L)
        {
          el* p;

          cout << "Rozmiar listy " << L.size << " elementy ( od lewej do prawej)" << endl;
          cout << "[" ;
          p = L.tail;
          while(p)
          {
            cout << " " << p->data;
            p = p->prev;
          }
          cout << " ]\n\n";
        }

        void push(lista &L, double v)
        {
          el* p;

          p = new el;
          p->data = v;
          p->prev = NULL;
          p->next = L.head;
          L.head  = p;
          L.size++;
          if(p->next) p->next->prev = p;
          else L.tail = p;
        }

        void listErase(lista &L, el* e)
        {
          L.size--;
          if(e->prev) e->prev->next = e->next;
          else        L.head = e->next;
          if(e->next) e->next->prev = e->prev;
          else        L.tail = e->prev;
          delete e;
        }

        void listRemove(lista &L)
        {
            while(L.size){
                listErase(L,L.head);
            }
        }

        void listSort(el * & h){

        }

        virtual ~List(){}
};

int ignoreWhiteMarks(istream& in) {
    int howMany = 0;
    while (in.peek() == 10 || in.peek() == 32)
        in.ignore();
    return howMany;
}

class Range{

    double downRange;
    double upRange;

public:
    void getRanges(){

        cout << "Podaj zakres liczb do wczytania:" << endl << "Zakres dolny: ";
        cin >> downRange;
        cout << "Zakres gorny: ";
        cin >> upRange;

        system("cls");
    }

    double getDownRange(){
        return downRange;
    }

    double getUpRange(){
        return upRange;
    }

    virtual ~Range(){}
};

int main()
{
    List c;
    lista l;
    Range r;

    r.getRanges();
    c.init(l);

    double value;
    char what;
    string str;
    filebuf* fb = new filebuf();
    assert(fb->open("plik.txt", ios::in));
    istream plik(fb);
    while (!plik.eof()) {
        ignoreWhiteMarks(plik);
        what = plik.peek(); //podgl¹damy co jest w strumieniu
        assert(isdigit(what));
        /*if (isdigit(what)) {*/
            plik>> value;
            if(value >= r.getDownRange() && value <= r.getUpRange()){
                assert(value >= r.getDownRange() && value <= r.getUpRange());
                c.push(l,value);
            }
        /*} else {
            plik>> str;
            cout <<"Nie liczba: " <<str <<";" <<endl;
        }*/
    }

    c.printLeftToRight(l);
    c.printRightToLeft(l);
    c.listRemove(l);
    c.printRightToLeft(l);
    fb->close();

    return 0;
}
