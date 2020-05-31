#ifndef node_hpp
#define node_hpp

#include "Components.hpp"
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <utility>
#include <cctype>
#include <Eigen/Dense>

using namespace std;

class Nodes
{
private:
    map<pair<string, string>, vector<Component>> Branch;
    vector<vector<double>> Conductances;
    vector<double> Currents;
    vector<double> Voltages;
    map<string, int> Labels;
    //number of nodes in the circuit
    unsigned int Size;
    
public:
    Nodes()
    {
        Size = 0;
    }
    
    /*
        Modify all get_ methods to const types.
    */
    
    int get_Size()
    {
        return Size;
    }
    
    void Resize()
    {
        Currents.resize(Size);
        Conductances.resize(Size);
        for(int i = 0; i < Conductances.size(); i++)
            Conductances[i].resize(Size);
    }
    
    int node_number(string &s)
    {
        if(s[0] == 'n' || s[0] == 'N')
        {
            s.erase(s.begin());
            if(stoi(s) > Size)
            {
                Size = stoi(s);
                Resize();
            }
            return stoi(s);
        }
        else
        {
            //check label
            //if new, add new label with number Size+1
            if(Labels[s])
                return Labels[s];
            else
            {
                Size++;
                Labels[s] = Size;
                Resize();
                return Size;
            }
            
        }
    }
    
    double get_conductance(int &i, int &j)
    {
        return Conductances[i][j];
    }
    
    double get_current(int &i)
    {
        return Currents[i];
    }
    
    double get_voltage(int &i)
    {
        return Voltages[i];
    }
    
    void add_voltage(int &i, double &value)
    {
        Voltages[i] = value;
    }
    
    void add_branch(const pair<string, string> &p, const Component &c)
    {
        Branch[p].push_back(c);
        
        int node1 = node_number(p.first);
        int node2 = node_number(p.second);
        
        //dynamicly calculate Currents and Conductances
        /*
         Current sources only, for now
        */
        if(c.get_type() == 'I')
        {
            if(node1)
                Currents[node1-1] += c.get_I();
            if(node2)
                Currents[node2-1] -= c.get_I();
        }
        else
        {
            //compute impedance
            /*
             Resistors only, for now
            */
            if(node1 && node2)
                Conductances[node1-1][node2-1] += c.compute_conductance();
            
            if(node1)
                Conductances[node1-1][node1-1] += c.compute_conductance();
            if(node2)
                Conductances[node2-1][node2-1] += c.compute_conductance();
        }
    }
    
    void print_voltages()
    {
        for(int i = 0; i < Size; i++)
            cout << Voltages[i] << endl;
    }
}

#endif
