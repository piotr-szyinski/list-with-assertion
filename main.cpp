#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>

//#define NDEBUG
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

        void listPushFront(lista &L, double v)
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

        void listPushBack(lista &L, double v)
        {
          el* p;

          p = new el;
          p->data = v;
          p->next = NULL;
          p->prev = L.tail;
          L.tail  = p;
          L.size++;
          if(p->prev) p->prev->next = p;
          else L.head = p;
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

        void listPopFront(lista &L){
            if(L.size) listErase(L,L.head);
        }

        void listPopBack(lista &L){
            if(L.size) listErase(L,L.tail);
        }

        void listPartition(el *head, el *tail){

            el *p, *i, *j;

            p = head->next;
            i = p->next;

            if(i != tail){
                do{
                    j = i;
                    i = i->next;
                    if(j->data > p->data){
                        j->prev->next = j->next;
                        j->next->prev = j->prev;
                        j->next = p;
                        j->prev = p->prev;
                        p->prev = j;
                        j->prev->next = j;
                    }
                }while(i != tail);
            }

            if(head->next != p ) listPartition(head,p);
            if(p->next != tail) listPartition(p,tail);
        }

        void listSort(lista &L){

            if(L.size > 1)
            {
                listPushFront(L,0);
                listPushBack(L,0);
                listPartition(L.head,L.tail);
                listPopFront(L);
                listPopBack(L);
            }
        }

        bool isEmpty(lista &L){
            if(L.size == 0){
                return true;
            }
            else{
                return false;
            }
        }

        el* getHead(lista &L){
            return L.head;
        }

        el* getTail(lista &L){
            return L.tail;
        }

        double getSize(lista &L){
            return L.size;
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
        cin >> downRange; // sprawdzanie poprawności wpisywanego zakresu
        assert(downRange >= 0);
        cout << "Zakres gorny: ";
        cin >> upRange;
        assert(upRange > downRange); // sprawdzanie poprawności wpisywanego zakresu

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

    r.getRanges(); // pobranie zakresu od uzytkownika
    c.init(l);  // inicjalizacja listy
    assert(c.getHead(l)==NULL&&c.getTail(l)==NULL&&c.getSize(l)==0); // sprawdzenie czy lista poprawnie zainicjowana

    double value;
    char what;
    string str;
    filebuf* fb = new filebuf();
    fb->open("plik.txt", ios::in);
    assert(fb->is_open());  // assert sprawdzajacy czy plik jest otwarty
    istream plik(fb);
    while (!plik.eof()) {
        ignoreWhiteMarks(plik);
        what = plik.peek(); //podgldamy co jest w strumieniu
        assert(isdigit(what)); // assert sprawdzajacy czy pobrana wartość jest liczbą
        plik>> value;   // pobranie liczby z pliku
        if(value >= r.getDownRange() && value <= r.getUpRange()){ // warunek wpisujacy poprawne liczby do listy
            assert(value >= r.getDownRange() && value <= r.getUpRange()); // sprawdzenie czy warunek dziala
            c.listPushFront(l,value); // dodanie wartosci do listy
        }
    }
    assert(c.isEmpty(l)==0); // assert czy pomyślnie dodano elementy do listy
    c.listSort(l);  // posortowanie listy
    c.printLeftToRight(l); // wypisanie listy od lewa to prawa
    c.printRightToLeft(l); // wypisanie listy od prawa do lewa
    c.listRemove(l);    // usuniecie listy
    c.printRightToLeft(l); // pokazanie czy usunelo liste
    cout << "Czy lista poprawnie usunieta: " << boolalpha << c.isEmpty(l) << endl;
    assert(c.isEmpty(l)==1); // assert czy lista poprawnie usunięta
    fb->close();

    return 0;
}
