#include<iostream>
#include "mylib.h"

using namespace std;
int isTrue= 1;

int main(){
    int a,b;
    
    while(isTrue){
        cout<<"\n\nchoose one of the options:\n 1) Addition \n 2) Subtraction \n 3) Multiplication \n 4) Division\n 5) Exit!\n\n";
        int choice;
        cin>>choice;

         

        switch (choice)
        {
        case 1:
            cout<<"Enter the two numbers a and b: "<<endl;
            cin>>a>>b; 
            cout<<a<<"+"<<b<<"="<<add(a,b)<<"\n";
            break;
        
        case 2:
            cout<<"Enter the two numbers a and b: "<<endl;
            cin>>a>>b;
            cout<<a<<"-"<<b<<"="<<difference(a,b)<<"\n";
            break;

        case 3:
            cout<<"Enter the two numbers a and b: "<<endl;
            cin>>a>>b;
            cout<<a<<"*"<<b<<"="<<product(a,b)<<"\n";
            break;

        case 4:
            cout<<"Enter the two numbers a and b: "<<endl;
            cin>>a>>b;
            cout<<a<<"/"<<b<<"="<<divide(float(a),b)<<"\n";
            break;

        case 5:
            isTrue = 0;
            break;

        default:
            cout<<"Please enter a valid option!\n";
            break;
        }

    }

    return 0;
}