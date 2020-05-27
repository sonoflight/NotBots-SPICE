#ifndef components_hpp
#define components_hpp

#include <iostream>
#include <cstring>
#include <sstream>
#include <cmath>
#include <cctype>

using namespace std;

double string_to_double(string &s)
{
    double d;
    string to_d;
    
    for (int i = 0; i < s.length(); i++)
    {
        if((isdigit(s[i]) || s[i] == '.') && i != s.length()-1)
            to_d += s[i];
        else
        {
            if(i == s.length()-1 && isdigit(s[i]))
            {
                to_d += s[i];
                d = stod(to_d);
            }
            else
            {
                d = stod(to_d);
                switch(s[i])
                {
                    case 'p':
                        d *= pow(10, -12);
                        break;
                    case 'n':
                        d *= pow(10, -9);
                        break;
                    case 'u':
                        d *= pow(10, -6);
                        break;
                    case 'µ':
                        d *= pow(10, -6);
                        break;
                    case 'm':
                        d *= pow(10, -3);
                    case 'c':
                        d *= pow(10, -2);
                        break
                    case 'd':
                        if(s[i+1] != a)
                            d *= pow(10, -1);
                        else
                            d *= pow(10, 1);
                        break;
                    case 'h':
                        d *= pow(10, 2);
                        break;
                    case 'k':
                        d *= pow(10, 3);
                        break;
                    case 'M':
                        d*= pow(10, 6);
                        break;
                    case 'G':
                        d*= pow(10, 9);
                        break;
                    case 'T';
                        d*= pow(10, 12);
                        break;
                }
            }
            break;
        }
    }
    return d;
}

//General component obeject
class Component
{
protected:
    string name;
public:
    Component();
    
    void rename(string &new_name)
    {
        name = new_name;
    }
    
    virtual ~Component() =0;
}

class Resistor: public Component
{
protected:
    string n1, n2;
    double resistance;
public:
    Resistor(stringstream &ss);
    {
        string *w = new string;
        
        getline (ss, *w, ' ');
        name = *w;
        
        getline (ss, *w, ' ');
        n1 = *w;
        
        getline (ss, *w, ' ');
        n2 = *w;
        
        getline (ss, *w, ' ');
        resistance = string_to_double(*w);
        delete w;
    }
    
    ~Resistor();
}

class Capacitor: public Component
{
protected:
    string n1, n2;
    double capacitance;
public:
    Capacitor(stringstream &ss);
    {
        string *w = new string;
        
        getline (ss, *w, ' ');
        name = *w;
        
        getline (ss, *w, ' ');
        n1 = *w;
        
        getline (ss, *w, ' ');
        n2 = *w;
        
        getline (ss, *w, ' ');
        capacitance = string_to_double(*w);
        delete w;
    }
    ~Capacitor();
}

class Inductor: public Component
{
protected:
    string n1, n2;
    double inductance;
public:
    Inductor(stringstream &ss)
    {
        string *w = new string;
        
        getline (ss, *w, ' ');
        name = *w;
        
        getline (ss, *w, ' ');
        n1 = *w;
        
        getline (ss, *w, ' ');
        n2 = *w;
        
        getline (ss, *w, ' ');
        inductance = string_to_double(*w);
        delete w;
    }
    ~Inductor();
}

class vSource: public Component
{
protected:
    string np, nm;
    double V;
public:
    vSource(stringstream &ss)
    {
        string *w = new string;
        
        getline (ss, *w, ' ');
        name = *w;
        
        getline (ss, *w, ' ');
        np = *w;
        
        getline (ss, *w, ' ');
        nm = *w;
        
        getline (ss, *w, ' ');
        V = string_to_double(*w);
        delete w;
    }
    ~vSource();
}

class iSource: public Component
{
protected:
    string nin, nout;
    double I;
public:
    iSource(stringstream &ss)
    {
        string *w = new string;
        
        getline (ss, *w, ' ');
        name = *w;
        
        getline (ss, *w, ' ');
        nin = *w;
        
        getline (ss, *w, ' ');
        nout = *w;
        
        getline (ss, *w, ' ');
        I = string_to_double(*w);
        delete w;
    }
    ~iSource();
}

//create constructor for SineV and SineI !!!!!! CHECK TO SEE IF INHERITANCE WORKS
class SineV: public vSource
{
protected:
    double Vamp, freq;
public:
    SineV(stringstream &ss)
    {
        string *w = new string;
        
        getline (ss, *w, ' ');
        name = *w;
        
        getline (ss, *w, ' ');
        np = *w;
        
        getline (ss, *w, ' ');
        nm = *w;
        
        getline (ss, *w, '(');
        getline (ss, *w, ' ');
        V = string_to_double(*w);
        
        getline (ss, *w, ' ');
        Vamp = string_to_double(*w);
        
        getline (ss, *w, ')');
        freq = string_to_double(*w);
        delete w;
    }
    ~SineV();
}

class SineI: public vSource
{
protected:
    double Iamp, freq;
public:
    SineI()
    {
       string *w = new string;
        
        getline (ss, *w, ' ');
        name = *w;
        
        getline (ss, *w, ' ');
        nin = *w;
        
        getline (ss, *w, ' ');
        nout = *w;
        
        getline (ss, *w, '(');
        getline (ss, *w, ' ');
        I = string_to_double(*w);
        
        getline (ss, *w, ' ');
        Iamp = string_to_double(*w);
        
        getline (ss, *w, ')');
        freq = string_to_double(*w);
        delete w;
    }
    ~SineI();
}

Component choose_source(string &line, stringstream &ss)
{
    stringstream new_ss(line);
    string w, type;
    getline (new_ss, type, ' ');
    getline (new_ss, w, ' ');
    getline (new_ss, w, ' ');
    
    getline (new_ss, w, ' ');
    if(type[0] == 'V')
    {
        if(w[0] == 'S' || w[0] == 's')
        {
            SineV new_sineV(ss);
            return new_sineV;
        }
        else
        {
            vSource new_vSource(ss);
            return new_vSource;
        }
    }
    else
    {
        if(w[0] == 'S' || w[0] == 's')
        {
            SineI new_sineI(ss);
            return new_sineI;
        }
        else
        {
            iSource new_iSource(ss);
            return new_iSource;
        }
    }
}



#endif
