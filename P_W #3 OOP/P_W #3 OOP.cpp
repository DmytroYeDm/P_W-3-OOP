#include <iostream>
using namespace std;
class Circuit_Elem {
protected:
    bool is_conn;  
public:
    Circuit_Elem* next = nullptr;
    Circuit_Elem() {
        this->is_conn = true;
    }
    virtual void Print() = 0;
    virtual bool Check() {
        return is_conn;
    }
    void Connect() {
        this->is_conn = true;
    }
    void Disconnect() {
        this->is_conn = false;
    }
};

class Contactor :public Circuit_Elem {
private:
    bool closed;
public:
    Contactor() :Circuit_Elem() {       
        this->closed = true;
    }
    Contactor(int a) :Circuit_Elem() {
        if (a == 0) {
            this->closed = false;
        }
        else {
            this->closed = true;
        }
    }
    Contactor(Contactor* c) {
        this->is_conn = c->is_conn;
        this->closed = c->closed;
    }
    void Close() {
        this->closed = true;
    }
    void Open() {
        this->closed = false;
    }
    void Print() override {
        cout << this->is_conn << endl;
        cout << this->closed << endl;
    }
    bool Check() override{
        if (Circuit_Elem::Check() == true && this->closed == true) {
            return true;
        }
        else {
            return false;
        }         
    }
};

class Resistance_Elem :public Circuit_Elem {
private:
    int resist;
public:
    Resistance_Elem() :Circuit_Elem() {
        this->resist = 1;
    }
    Resistance_Elem(int r) :Circuit_Elem() {
        if (r <= 0) {
            abort();
        }
        this->resist = r;
    }
    Resistance_Elem(Resistance_Elem* r) {
        this->is_conn = r->is_conn;
        this->resist = r->resist;
    }
    void Print() override {
        cout << this->is_conn << endl;
        cout << this->resist << endl;
    }
    bool Check() override {
        if (Circuit_Elem::Check() == true) {
            return true;
        }
        else {
            return false;
        }
    }
};

class Wires :public Circuit_Elem {
private:
    int length;
public:
    Wires() :Circuit_Elem() {
       this->length = 1;
    }  
    Wires(int l) :Circuit_Elem() {
        if (l <= 0) {
            abort();
        }
        this->length = l;
    }
    Wires(Wires* w) {
        this->is_conn = w->is_conn;
        this->length = w->length;
    }
    void Print() override {
        cout << this->is_conn << endl;
        cout << this->length << endl;
    }
    bool Check() override {
        if (Circuit_Elem::Check() == true) {
            return true;
        }
        else {
            return false;
        }
    }
};

class Current_Sourse :public Circuit_Elem {
private:
    int power;
    int resist;
    bool activated;
public:
    Current_Sourse() :Circuit_Elem() {
        this->power = 1;
        this->resist = 1;
        this->activated = true;
    }
    Current_Sourse(int p, int r) :Circuit_Elem() {
        if (p <=0 || r <= 0) {
            abort();
        }
        this->power = p;
        this->resist = r;
        this->activated = true;
    }
    Current_Sourse(Current_Sourse* s) {
        this->is_conn = s->is_conn;
        this->power = s->power;
        this->resist = s->resist;
        this->activated = s->activated;
    }
    void Activate() {
        this->activated = true;
    }
    void Deactivate() {
        this->activated = false;
    }
    void Print() {
        cout << this->is_conn << endl;
        cout << this->power << endl;
        cout << this->resist << endl;
        cout << this->activated << endl;
    }
    bool Check() override {
        if (Circuit_Elem::Check() == true && this->activated == true) {
            return true;
        }
        else {
            return false;
        }
    }
};

class Electric_Circuit {
private:
    Circuit_Elem* first;
public:
    Electric_Circuit() {
        first = nullptr;
    }
    void Add(Circuit_Elem* e) {
        e->next = first;
        first = e;
    }
    void Print() {
        Circuit_Elem* temp = first;
        while (temp != nullptr) {
            temp->Print();
            temp = temp->next;
        }    
    }
    bool Check_Circuit() {
        Circuit_Elem* temp = first;
        while (temp != nullptr) {
            if (temp->Check() != true) {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }
};

int main()
{
    Contactor c1, c2(0), c3(c2);
    c1.Print();
    c2.Print();
    c2.Close();
    c2.Disconnect();
    c2.Print();
    c3.Disconnect();
    cout << c1.Check() << ' '<< c2.Check() << ' ' << c3.Check() << endl; 
    Resistance_Elem r1, r2(3), r3(r2);
    r1.Print();
    r2.Print();
    r3.Disconnect();
    cout << r1.Check() << ' ' << r2.Check() << ' ' << r3.Check() << endl;
    Wires w1, w2(6), w3(w2);
    w1.Print();
    w2.Print();
    w3.Disconnect();
    cout << w1.Check() << ' ' << w2.Check() << ' ' << w3.Check() << endl;
    Current_Sourse s1, s2(14, 2), s3(s2);
    s1.Print();
    s2.Print();
    s3.Deactivate();
    s3.Print();
    Electric_Circuit e; 
    e.Add(&c1);
    e.Add(&r2);
    e.Add(&w3);
    e.Add(&s2);
    e.Print();
    cout << e.Check_Circuit() << endl;
    w3.Connect();
    cout << e.Check_Circuit() << endl;
    s2.Deactivate();
    cout << e.Check_Circuit() << endl;
}


