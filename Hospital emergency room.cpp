#include <iostream>
#include <list>
#include <fstream>
#include <string>

using namespace std;
class Patient{
    string name,condition;
    int age,priority;
    void setPriority(string _condition){
        if (_condition == "critical") {
            priority = 3;
        }
        else if(_condition == "urgent") {
            priority = 2;
        }
        else if(_condition == "normal") {
            priority = 1;
        }
    }
public:
    Patient():age(-1),priority(-1){}
    Patient(string name,string condition,int age)
            :name(name),age(age),condition(condition){
        setPriority(condition);
    }
    void print(){
        cout<<"name:"<<name<<", age:"<<age<<", condition:"<<condition<<", priority:"<<priority<<endl;
    }
    string getName(){
        return name;
    }
    int getPriority(){
        return priority;
    }
    void setCondition(string _condition){
        condition=_condition;
        setPriority(_condition);
    }
};
class PriorityQueue{
private:
    list<Patient> patients;
public:
    void addPatient(Patient patient){
        if (patients.empty()) {
            patients.push_back(patient);
        }
        else if(patient.getPriority()==3){
            list<Patient>::iterator i = patients.begin();
            while (i->getPriority() == 3){
                i++;
            }
            patients.insert(i,patient);
        }
        else if(patient.getPriority()==2){
            list<Patient>::iterator i = patients.begin();
            while (i->getPriority() == 3 || i->getPriority() == 2){
                i++;
            }
            patients.insert(i,patient);
        }
        else if(patient.getPriority()==1){
            patients.push_back(patient);
        }
    }
    void processPatient(){
        patients.pop_front();
    }
    void updatePatient(Patient patient, string newCondition){
        list<Patient>::iterator i = patients.begin();
        while(i->getName()!=patient.getName()){
            i++;
        }
        i->setCondition(newCondition);
        Patient temp = *i;
        patients.erase(i);
        PriorityQueue::addPatient(temp);
    }
    string frontName(){
        return patients.begin()->getName();
    }
    int queue_size(){
        return patients.size();
    }
    void display_queue(){
        cout<<"patients data:\n";
        for (list<Patient>::iterator i = patients.begin(); i != patients.end(); ++i) {
            i->print();
        }
    }
    Patient findPatient(const string name){
        for (list<Patient>::iterator i = patients.begin(); i != patients.end(); ++i) {
            if (name == i->getName()){
                return *i;
            }
        }
        return Patient();
    }
    bool isFound(const string& name){
        if (findPatient(name).getName()==name)
            return true;
        else
            return false;
    }
};

int main() {
    PriorityQueue queue;
    int choice;
    bool flag = true;
    while(flag){
        cout<<"1-add patient to the queue\n"
            <<"2-process/remove patient from the queue\n"
            <<"3-update patient in the queue\n"
            <<"4-get the first patient in the queue\n"
            <<"5-how many patients in the queue\n"
            <<"6-display patients in the queue\n"
            <<"7-end program\n";
        cin>>choice;
        switch (choice) {
            case 1:{
                string name,condition;
                int age;
                cout<<"enter patient name:";cin>>name;
                cout<<"\nenter patient condition,critical-urgent-normal:";cin>>condition;
                cout<<"\nenter patient age:";cin>>age;
                queue.addPatient(Patient(name,condition,age));
                cout<<"patient "<<name << " added to the queue.\n";
            }break;
            case 2: {
                if (queue.queue_size()==0) {
                    cout<<"there are no patients in the queue!\n";
                }
                else{
                    Patient firstPatient=queue.findPatient(queue.frontName());
                    cout<<"processing patient:"<<firstPatient.getName()<<" (Priority: "<<firstPatient.getPriority()<<")\n";
                    queue.processPatient();
                }
            }break;
            case 3:{
                string name,condition;
                cout<<"enter name of patient you want to update his/her condition:";
                cin>>name;
                if (queue.isFound(name)) {
                    cout<<"enter the new condition:";
                    cin>>condition;
                    queue.updatePatient(queue.findPatient(name),condition);
                    cout<<"condition/priority updated successfully!";
                }
                else
                    cout<<"please enter available name in the queue!\n";
            }break;
            case 4:cout<<"Front patient name: "<<queue.frontName()<<endl;break;
            case 5:cout<<"number of patients in the queue: "<<queue.queue_size()<<endl;break;
            case 6:queue.display_queue();break;
            case 7:flag=false;break;
        }
    }
    return 0;
}
