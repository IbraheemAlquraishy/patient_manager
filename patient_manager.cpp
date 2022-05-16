#include <iostream>
#include <fstream>


//this program is written by ibraheem alquraishy

using namespace std;


fstream file;//a file to save patients data
struct date{
    int YYYY;
    int MM;
    int DD;
};
struct patient{
    string name;
    int age;
    string illness;
    date d;    
};
patient patients[100];
int count=0;//the count of patients exist in the file

string toLower(string);
void sort(int);
int binary_search(string);
void read_input();
void write_file();
void read_file();
void output_file();
void cnt();
void stats();


int main(){
    char ch;
    
    file.open("patient");
    if(!file){//checks if file exist if not make one 
        file.close();
        file.open("patient",ios::out);
        file.close();
    }
    else{
        file.close();
    }
    while(true){
    cout<<"This program is made by ibraheem qasim /information /morning\n";
    cout<<"\t[1]read the list of patient.\n\t[2]add new patients.\n\t[3]search.\n\t[4]count the number of patients.\n\t[5]statics.\n\t[e]exit.\nselect:";
    cin>>ch;
    if(ch=='1'){
        file.open("patient",ios::in);
        read_file();
        sort(count);
        output_file();
        file.close();
    }else if(ch=='2'){
        file.open("patient",ios::out);
        read_input();
        sort(count);
        write_file();
        file.close();
    }else if(ch=='3'){
        string search;
        cout<<"enter the name you want to find:";
        cin>>search;
        read_file();
        sort(count);
        int i=binary_search(toLower(search));
        i!=-1?cout<<patients[i].name<<"\t"<<patients[i].age<<"\t"<<patients[i].illness<<
        "\t"<<patients[i].d.YYYY<<"/"<<patients[i].d.MM<<"/"<<patients[i].d.DD<<"\n":cout<<"not found.\n";
    }else if(ch=='4'){
        file.open("patient",ios::in);
        read_file();
        cout<<count<<endl;
        file.close();
    }else if(ch=='5'){
        file.open("patient",ios::in);
        read_file();
        stats();
        file.close();
    }
     else if(ch=='e'){
        break;
    }
    
    }
    
}

//function to to lower chars and strings to avoid logic erros when searching etc.
string toLower(string s){
    for(int i=0;i<s.length();i++){
        if(s[i]>='A'&&s[i]<='Z'){
            s[i]+=32;
        }
    }
    return s;
}

//function to refresh the count var this is importent to avoid some bugs
void cnt(){
    count=0;
    for(int i=0;patients[i].name!="";i++){
        count++;
    }
}

//function to sort patient array to output it to the file and to the binary search function
void sort(int n){
    patient temp;
    for(int i=0;i<n-1;i++){
        for(int j=i;j<n;j++){
            if(patients[i].name>patients[j].name){
                temp=patients[i];
                patients[i]=patients[j];
                patients[j]=temp;
            }
        }
    }
}

//function to search for a patient in an array using his name
int binary_search(string s){
    string arr[100];
    int low=0;
    int high=count;
    int i=(low+high)/2;
    int rounds=0;
    for(int i=0;i<count;i++){
        arr[i]=patients[i].name;
    }
    while(rounds<5){
        if(arr[i]!=s){
            if(arr[i]>s){
                high=i-1;
            }
            else{
                low=i+1;
            }
        }
        else{
            return i;
        }
        i=(low+high)/2;
        rounds++;
    }
    return -1;
}

//function to read user input data to output it to the file
void read_input(){
    string temp;
    for(int i=0;i<50;i++){
        cout<<"enter the name of the patient(e to exit adding):";
        cin>>temp;
        if(toLower(temp)=="e"){
            break;
        }else{
            patients[i].name=toLower(temp);
            cout<<"enter his age:";
            cin>>patients[i].age;
            cout<<"enter his illness:";
            cin>>temp;
            patients[i].illness=toLower(temp);
            cout<<"enter which year:";
            cin>>patients[i].d.YYYY;
            cout<<"enter which month:";
            cin>>patients[i].d.MM;
            cout<<"enter which day of the month:";
            cin>>patients[i].d.DD;
            
        }
    }
    cnt();
}

//function to write user input data to the file
void write_file(){
    for(int i=0;i<count;i++){
        file<<patients[i].name<<"\t"<<patients[i].age<<"\t"<<patients[i].illness<<
        "\t"<<patients[i].d.YYYY<<"\t"<<patients[i].d.MM<<"\t"<<patients[i].d.DD<<"\n";
        
    }   
}

//function to output the content of the file
void output_file(){
    for(int i=0;i<count;i++){
        cout<<patients[i].name<<"\t"<<patients[i].age<<"\t"<<patients[i].illness<<
        "\t"<<patients[i].d.YYYY<<"/"<<patients[i].d.MM<<"/"<<patients[i].d.DD<<"\n";
        
    }  
}

//function reads content of the file
void read_file(){
    string line;
    string word="";
    int order=0;
    int k=0;
    while(getline(file,line,'\n')){
        for(int i=0;i<=line.length();i++){
            if(line[i]=='\t'||i==line.length()){
                
                switch(order){
                    case 0:patients[k].name=word;break;
                    case 1:patients[k].age=stoi(word,nullptr);break;
                    case 2:patients[k].illness=word;break;
                    case 3:patients[k].d.YYYY=stoi(word,nullptr);break;
                    case 4:patients[k].d.MM=stoi(word,nullptr);break;
                    case 5:patients[k].d.DD=stoi(word,nullptr);break;
                    default:cout<<"error\n";break;
                }
                word="";
                order++;
            }else{
                word+=line[i];
            }
        }
        k++;
        order=0;
        word="";
    }
    cnt();
}

//function to ask user about what kind of stats he want and output it to him
void stats(){
    char s;
    
    
    while(true){
        cout<<"statics page\n\t[1]statics by years.\n\t[2]statics by months.\n\t[3]statics by age.\n\t[4]statics by illness.\n\t[e]exit from statics.\nselect:";
        cin>>s;
        if(s=='1'){
            int years[100];
            int sum=0;
            for(int i=0;i<=count;i++){
                years[i]=patients[i].d.YYYY;
            }
            int year;
            for(int i=0;i<count;i++){
                if(years[i]!=0){
                year=years[i];
                sum=1;

                for(int j=i+1;j<=count;j++){
                    if(years[j]==year){
                        sum++;
                        years[j]=0;
                    }else if(years[j]==0){
                        continue;
                    }
                }
                cout<<year<<":"<<sum<<"\t\t";
                }
            }
            cout<<endl;
        }else if(s=='2'){
            int months[100];
            int sum;
            for(int i=0;i<=count;i++){
                months[i]=patients[i].d.MM;
            }
            int month;
            for(int i=0;i<count;i++){
                if(months[i]!=0){
                month=months[i];
                sum=1;

                for(int j=i+1;j<=count;j++){
                    if(months[j]==month){
                        sum++;
                        months[j]=0;
                    }else if(months[j]==0){
                        continue;
                    }
                }
                cout<<month<<":"<<sum<<"\t\t";
                }
            }
            cout<<endl;
        }else if(s=='3'){
            int ages[100];
            int sum=0;
            for(int i=0;i<=count;i++){
                ages[i]=patients[i].age;
            }
            int age;
            for(int i=0;i<count;i++){
                if(ages[i]!=0){
                age=ages[i];
                sum=1;

                for(int j=i+1;j<=count;j++){
                    if(ages[j]==age){
                        sum++;
                        ages[j]=0;
                    }else if(ages[j]==0){
                        continue;
                    }
                }
                cout<<age<<":"<<sum<<"\t\t";
                }
            }
            cout<<endl;
        }else if(s=='4'){
            string ils[100];
            int sum;
            for(int i=0;i<=count;i++){
                ils[i]=patients[i].illness;
            }
            string il;
            for(int i=0;i<count;i++){
                if(ils[i]!=""){
                    il=ils[i];
                    sum=1;
                    for(int j=i+1;j<=count;j++){
                        if(ils[j]==il){
                            sum++;
                            ils[j]="";
                        }else if(ils[j]==""){
                            continue;
                        }
                    }
                    cout<<il<<":"<<sum<<"\t\t";
                }
            }
            cout<<endl;
        }else if(s=='e'){
           break;
        }
    }
}