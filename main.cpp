#include <iostream>
#include <stdio.h>
#include <list>
using namespace std;
void scan(list<char> *t){
    char ch=0;
    while(ch!='\n'){
        ch=getchar();
        (*t).push_back(ch-48);
    }
    (*t).pop_back();
}
void print(list<char> t){
    list<char>::iterator itr;
    for(itr=t.begin();itr!=t.end();++itr)
        cout<<(char)(*itr+48);
}
void refresh(list<char> *t){
    list<char>::reverse_iterator itr;
    char ch=0;
    for(itr=(*t).rbegin();itr!=(*t).rend();itr++){
        *itr=*itr+ch;
        ch=*itr/10;
        *itr=*itr%10;
    }
    if(ch)
        (*t).push_front(ch);
}
void plus_(list<char> *source,list <char>*target){
    while((*source).size()>(*target).size())
        (*target).push_front(0);
    list<char>::reverse_iterator itr;
    list<char>::reverse_iterator itr2;
    for(itr=(*source).rbegin(),itr2=(*target).rbegin();itr!=(*source).rend()&&itr2!=(*target).rend();itr++,itr2++){
        *itr2=*itr2+*itr;
    }
    refresh(target);
}
void remove_zero_from_start(list<char>*t){
    list<char>::iterator itr=(*t).begin();
    while(itr!=(*t).end()&&(*t).size()>1){
        if(*itr==0){
            (*t).pop_front();
            itr=(*t).begin();
            continue;
        }else
            break;
        itr++;
    }
}
void refresh2(list<char> *t){
    list<char>::iterator itr;
    list<char>::iterator itr2;
    itr=(*t).begin();
    itr2=(*t).begin();
    if((*t).size()<2)
        return;
    for(itr2++;itr!=(*t).end()&&itr2!=(*t).end();itr++,itr2++){
        *itr=*itr-1;
        *itr2=*itr2+10;
    }
    refresh(t);
    remove_zero_from_start(t);
}
void minus_(list<char> *m,list<char> *m2){
    list<char>::reverse_iterator itr;
    list<char>::reverse_iterator itr2;
    itr=(*m).rbegin();
    itr2=(*m2).rbegin();
    while(itr!=(*m).rend()&&itr2!=(*m2).rend()){
        *itr=*itr-*itr2;
        itr++;
        itr2++;
    }
    refresh2(m);
}
void decrease_by_one(list<char> *m){
    list<char>::reverse_iterator itr;
    itr=(*m).rbegin();
    *itr=*itr-1;
    refresh2(m);
}
void increase_by_one(list<char> *m){
    list<char>::reverse_iterator itr;
    if( (*m).size()==0)
        (*m).push_back(0);
    itr=(*m).rbegin();
    *itr=*itr+1;
    refresh(m);
}
void multiply_(list<char> *m,list<char>*m2,list<char> *result){
    while(1){
        if((*m2).size()==1&&(*m2).back()==0 )
            break;
        plus_(m,result);
        decrease_by_one(m2);
    }
}
int compare_(list<char> *m,list<char> *m2){
    remove_zero_from_start(m);
    remove_zero_from_start(m2);
    if( (*m).size()>(*m2).size())
        return 1;
    if( (*m).size()<(*m2).size())
        return -1;
    list<char>::iterator itr;
    list<char>::iterator itr2;
    for(itr=(*m).begin(),itr2=(*m2).begin();itr!=(*m).end()&&itr2!=(*m2).end();itr++,itr2++){
        if(*itr>*itr2)
            return 1;
        if(*itr2>*itr)
            return -1;
    }
    return 0;
}
void division_(list<char>*m,list<char>*m2,list<char>*res){
    list<char>temp;
    while(compare_(m,&temp)!=-1){
        plus_(m2,&temp);
        increase_by_one(res);
    }
    decrease_by_one(res);
}
void clean_buff(){
    while(getchar()!='\n');
}
void division2(list<char> *m,list<char> *m2,list<char>*res){
    list<char>temp;
    list<char>::iterator i;
    for(i=(*m).begin();i!=(*m).end();){
        temp.push_back( *i);
        i++;
        while(i!=(*m).end()&&compare_(&temp,m2)==-1){
            (*res).push_back(0);
            temp.push_back(*i);
            i++;
        }
        int n=0;
        while(compare_(&temp,m2)!=-1){
            minus_(&temp,m2);
            n++;
        }
        if(n){
           (*res).push_back(n);
        }else
            (*res).push_back(0);
    }
    remove_zero_from_start(res);
}
void multiply2(list<char>*m,list<char>*m2,list<char>*res){
    list<char>::reverse_iterator itr;
    list<char>::reverse_iterator itr2;
    list<char>::reverse_iterator itr3;
    for(int i=0;i<(*m).size();i++)
        (*res).push_back(0);
    for(int i=0;i<(*m2).size();i++)
        (*res).push_back(0);
    int i=0;
    for(itr=(*m).rbegin();itr!=(*m).rend();itr++,i++){
        itr3=(*res).rbegin();
        for(int k=0;k<i;k++)
            itr3++;
        for(itr2=(*m2).rbegin();itr2!=(*m2).rend();itr2++,itr3++){
            *itr3+=(*itr)*(*itr2);
        }
        refresh(res);
    }
    remove_zero_from_start(res);
}
void run(){
    list<char> L1;
    list<char> L2;
    list<char> L3;
    char ch=0;
    printf("Arithmetic operations in big numbers in C++\n");
    while(1){
        cout<<"Enter arithmetic operator + - * /\nExit enter @\n";
        scanf("%c",&ch);
        clean_buff();
        if(ch=='@')
            break;
        cout<<"Enter first number\n";
        scan(&L1);
        cout<<"Enter second number\n";
        scan(&L2);
        switch(ch){
            case '+':
                plus_(&L1,&L3);
                plus_(&L2,&L3);
                break;
            case '-':
                plus_(&L1,&L3);
                minus_(&L3,&L2);
                break;
            case '*':
                multiply2(&L1,&L2,&L3);
                break;
            case '/':
                division2(&L1,&L2,&L3);
                break;
        }
        cout<<"\nResult = ";
        print(L3);
        cout<<endl<<endl;
        L1.clear();
        L2.clear();
        L3.clear();
    }
}
int main() {
    run();
    puts("\nExit enter\n");
    getchar();
    return 0;
}





















