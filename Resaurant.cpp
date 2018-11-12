#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include <sstream> 
#include "Action.h"
#include <fstream>
using namespace std;

class Restaurant{		
public:
	Restaurant():
    this->open=false, this->currentId=0
    { }
    Restaurant(const string &configFilePath):
    this->open=false , this->currentId=0
    {
         int count=0,id=0,d_price,current,capacity;
         string line,word,d_name,d_type;
         ifstream myfile;
         myfile.open (configFilePath);
         if (myfile.is_open())
          {
            while ( getline (myfile,line) )
            {
                if(line[0]!='#' && line!="")// empty or comment lines ignored
                {
                    switch (count){ //switch for what is meant to be read
                    case 0: //read number of tables
                         this->numoftables=stringstream(line); //entire line can be read
                         count++; break;
                    case 1: // read tables capacity 
                        current=0;
                        while(line[current]!= \0)//reading line word by word
                            tables.push_back(new table(stringstream(wordreader(line,*current)))//current is advanced in function
                        count++; break;
                    default: //read menu
                        current=0;
                        d_name=wordreader(line,&current);//current is advanced in function
                        d_type=wordreader(line,&current);
                        d_price=stringstream(wordreader(line,&current));
                        menu.push_back(new Dish(id,d_name,d_type,d_price));
                        id++; 
                       }
                }
            }
            myfile.close();
         }
         else cout << "Unable to open file";
    }
    void start(){
        int current,tableId,destinationId,customerId;
        string line,command,strat,name,;
        customer* temp;
        cout<<"Restaurant is now open";
        vector<Customer*> customerlist;
        BaseAction base;
        this->open=true;
        while(this->open)
        {
            getline (cin, line);
            command=wordreader(line,&current);
            switch(command):
            case (open):
                tableId=stringstream(wordreader(line,&current));
                while(line[current]!= \0)//reading line word by word
                {
                    name=wordreader(line,&current);
                    strat=wordreader(line,&current);
                    temp=createCustomer(currentId,name,strat)
                    customerlist.push_back(temp);
                    currentId++;
                }       
                base=new openTable(tableId,customerlist,); break;
            case (order):
                tableId=stringstream(wordreader(line,&current));
                base=new Order(tableId);break;
            case(move):
                tableId=stringstream(wordreader(line,&current));
                destinationId=stringstream(wordreader(line,&current));
                customerId=stringstream(wordreader(line,&current));
                base=new MoveCustomer(tableId,destinationId,customerId);  break;
            case(close):
                tableId=stringstream(wordreader(line,&current));
                base=new Close(tableId);  break;
            case(closeall):
                base=new CloseAll(); break;
            case(menu):
                base=new PrintMenu(); break;
            case(status):
                tableId=stringstream(wordreader(line,&current));
                base=new PrintTableStatus(); break;
            case(log):
                base=new PrintActionsLog(); break;
            case(backup):
                base=new BackupRestaurant(); break;
            case(restore):
                base=new RestoreRestaurant(); break;
            case default: cout<<"illegal command";
            base.act(*this);
        }
    }
    int getNumOfTables() const{
        return this->numoftables;
    }
    Table* getTable(int ind)
        return this->tables[ind];
	const vector<BaseAction*>& getActionsLog() const
    {
        return this->actionsLog;
    } // Return a reference to the history of actions
    vector<Dish>& getMenu(){
        return this->menu;
    }

private:
    bool open;
    int numoftables;
    int currentId;
    vector<Table*> tables;
    vector<Dish> menu;
    vector<BaseAction*> actionsLog;
    string wordreader(string line, int* pcurrent)// function reads the next word in the line,current is advanced in function
            {
                string word="";
                boolean flag=true;
                    while(line[*pcurrent]!= '\0' && flag)//reading line word by word
                    {
                        if(line[*pcurrent]==' ' || line[*pcurrent]==',')
                            if(word!="")// not empty word
                                flag=false;
                        else
                            word+=line[*pcurrent];
                        j++;
                    }      
                return word;                
            }
    customer* createCustomer(id,name,strat){

            switch (strat):
            case (veg):
                return  new VegetarianCustomer(name, id);
            case(spc):
                return  new SpicyCustomer(name, id);
            case(alc):
                return  new AlchoholicCustomer(name, id);
            case(chp):
                return  new CheapCustomer(name, id);
            case default:
                return null;




    }
};