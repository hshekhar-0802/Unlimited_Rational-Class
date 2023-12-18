
#include "ulimitedrational.h"

UnlimitedRational::UnlimitedRational(){
    p=new UnlimitedInt(0);
    q=new UnlimitedInt(0);
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    p=new UnlimitedInt(num->get_array(),num->get_capacity(),num->get_sign(),num->get_size());
    q=new UnlimitedInt(den->get_array(),den->get_capacity(),den->get_sign(),den->get_size());
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
}

string UnlimitedRational::get_q_str(){
    return q->to_string();
}

string UnlimitedRational::get_frac_str(){
    string res=p->to_string()+"/"+q->to_string();
    return res;
}

int compareI(UnlimitedInt* i1, UnlimitedInt* i2){
    int max=i1->get_size();
    if(max<i2->get_size()){
        max=i2->get_size();
    }
    int max2=max;
    int* arr1=new int[max];
    int* arr2=new int[max];
    for(int i=0;i<max;i++){
        arr1[i]=0;
        arr2[i]=0;
    }
    if(max==i1->get_size()){
        int* arr=i1->get_array();
        for(int i=0;i<max;i++){
            arr1[i]=arr[i];
        }
        int* ptr=i2->get_array();
        int size=i2->get_size();
        while(size>=1){
            arr2[max-1]=ptr[size-1];
            max--;
            size--;
        }
    }
    else{
        int* arr=i2->get_array();
        for(int i=0;i<max;i++){
            arr2[i]=arr[i];
        }
        int* ptr=i1->get_array();
        int size=i1->get_size();
        while(size>=1){
            arr1[max-1]=ptr[size-1];
            size--;
            max--;
        }
    }
    int i=0;
    for( ;i<max2;i++){
        if(arr1[i]>arr2[i]){
            delete[] arr1;
            delete[] arr2;
            return 1;
        }
        else if(arr1[i]<arr2[i]){
            delete[] arr1;
            delete[] arr2;
            return 2;
        }
    }
    if(i==max2){
        delete[] arr1;
        delete[] arr2;
        return 0;
    }
    return 0;
}

bool equalZero(UnlimitedInt* i1){
    int* arr=i1->get_array();
    for(int i=0;i<i1->get_size();i++){
        if(arr[i]!=0){
            return false;
        }
    }
    return true;
}

bool isZerobyZero(UnlimitedRational* r){
    if(equalZero(r->get_q())){
        return true;
    }
    return false;
}

bool strequalZero(string s){
    if(s[0]=='-'){
        s=s.substr(1,s.length()-1);
    }
    for(int i=0;i<s.length();i++){
        if(s[i]!='0'){
            return false;
        }
    }
    return true;
}

string modulo(string s1,string s2){
    UnlimitedInt* i1=new UnlimitedInt(s1);
    UnlimitedInt* i2=new UnlimitedInt(s2);
    UnlimitedInt* i3=UnlimitedInt::mod(i1,i2);
    string s=i3->to_string();
    delete i1;
    delete i2;
    delete i3;
    return s;
}

UnlimitedInt* gcd(UnlimitedInt* i1, UnlimitedInt* i2){
    string larger,smaller,rem;
    int big=compareI(i1,i2);
    if(big==0){
        return i1;
    }
    else if(big==1){
        larger=i1->to_string();
        smaller=i2->to_string();
    }
    else{
        larger=i2->to_string();
        smaller=i1->to_string();
    }
    while(!strequalZero(smaller)){
        rem=modulo(larger,smaller);
        larger=smaller;
        smaller=rem;
    }
    UnlimitedInt* res=new UnlimitedInt(larger);
    return res;
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    if(isZerobyZero(i1) || isZerobyZero(i2)){
        UnlimitedRational* res=new UnlimitedRational();
        return res;
    }
    UnlimitedInt *i1_p=i1->get_p();
    UnlimitedInt *i1_q=i1->get_q();
    UnlimitedInt *i2_p=i2->get_p();
    UnlimitedInt *i2_q=i2->get_q(); 
    UnlimitedInt* multiply_num=UnlimitedInt::mul(i1_p,i2_q);
    UnlimitedInt* multiply_den=UnlimitedInt::mul(i1_q,i2_p);
    UnlimitedInt *numerator=UnlimitedInt::add(multiply_num,multiply_den);
    UnlimitedInt *denominator=UnlimitedInt::mul(i1_q,i2_q);
    UnlimitedInt *pos_num=new UnlimitedInt(numerator->get_array(),numerator->get_capacity(),1,numerator->get_size());
    UnlimitedInt *pos_den=new UnlimitedInt(denominator->get_array(),denominator->get_capacity(),1,denominator->get_size());
    UnlimitedInt* hcf=gcd(pos_num,pos_den);
    UnlimitedInt* num1=UnlimitedInt::div(numerator,hcf);
    UnlimitedInt* den1=UnlimitedInt::div(denominator,hcf);
    UnlimitedRational *res=new UnlimitedRational(num1,den1);
    delete multiply_num;
    delete multiply_den;
    delete numerator;
    delete denominator;
    delete pos_num;
    delete pos_den;
    delete hcf;
    delete num1;
    delete den1;
    return res;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    if(isZerobyZero(i1) || isZerobyZero(i2)){
        UnlimitedRational* res=new UnlimitedRational();
        return res;
    }
    UnlimitedInt *i1_p=i1->get_p();
    UnlimitedInt *i1_q=i1->get_q();
    UnlimitedInt *i2_p=i2->get_p();
    UnlimitedInt *i2_q=i2->get_q();
    UnlimitedInt *multiply_num=UnlimitedInt::mul(i1_p,i2_q);
    UnlimitedInt *multiply_den=UnlimitedInt::mul(i1_q,i2_p);
    UnlimitedInt *numerator=UnlimitedInt::sub(multiply_num,multiply_den);
    UnlimitedInt *denominator=UnlimitedInt::mul(i1_q,i2_q);
    UnlimitedInt *pos_num=new UnlimitedInt(numerator->get_array(),numerator->get_capacity(),1,numerator->get_size());
    UnlimitedInt *pos_den=new UnlimitedInt(denominator->get_array(),denominator->get_capacity(),1,denominator->get_size());
    UnlimitedInt* hcf=gcd(pos_num,pos_den);
    UnlimitedInt* num1=UnlimitedInt::div(numerator,hcf);
    UnlimitedInt* den1=UnlimitedInt::div(denominator,hcf);
    UnlimitedRational *res=new UnlimitedRational(num1, den1);
    delete multiply_num;
    delete multiply_den;
    delete numerator;
    delete denominator;
    delete pos_num;
    delete pos_den;
    delete hcf;
    delete num1;
    delete den1;
    return res;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    if(isZerobyZero(i1) || isZerobyZero(i2)){
        UnlimitedRational* res=new UnlimitedRational();
        return res;
    }
    UnlimitedInt *i1_p=i1->get_p();
    UnlimitedInt *i1_q=i1->get_q();
    UnlimitedInt *i2_p=i2->get_p();
    UnlimitedInt *i2_q=i2->get_q(); 
    UnlimitedInt *numerator=UnlimitedInt::mul(i1_p,i2_p);
    UnlimitedInt *denominator=UnlimitedInt::mul(i1_q,i2_q);
    UnlimitedInt *pos_num=new UnlimitedInt(numerator->get_array(),numerator->get_capacity(),1,numerator->get_size());
    UnlimitedInt *pos_den=new UnlimitedInt(denominator->get_array(),denominator->get_capacity(),1,denominator->get_size());
    UnlimitedInt* hcf=gcd(pos_num,pos_den);
    UnlimitedInt* num1=UnlimitedInt::div(numerator,hcf);
    UnlimitedInt* den1=UnlimitedInt::div(denominator,hcf);
    UnlimitedRational *res=new UnlimitedRational(num1, den1);
    delete numerator;
    delete denominator;
    delete pos_num;
    delete pos_den;
    delete hcf;
    delete num1;
    delete den1;
    return res;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    if(isZerobyZero(i1) || isZerobyZero(i2) || equalZero(i2->get_p())){
        UnlimitedRational* res=new UnlimitedRational();
        return res;
    }
    UnlimitedInt *i1_p=i1->get_p();
    UnlimitedInt *i1_q=i1->get_q();
    UnlimitedInt *i2_p=i2->get_p();
    UnlimitedInt *i2_q=i2->get_q(); 
    UnlimitedInt *numerator=UnlimitedInt::mul(i1_p,i2_q);
    UnlimitedInt *denominator=UnlimitedInt::mul(i1_q,i2_p);
    UnlimitedInt *pos_num=new UnlimitedInt(numerator->get_array(),numerator->get_capacity(),1,numerator->get_size());
    UnlimitedInt *pos_den=new UnlimitedInt(denominator->get_array(),denominator->get_capacity(),1,denominator->get_size());
    UnlimitedInt* hcf=gcd(pos_num,pos_den);
    UnlimitedInt* num1=UnlimitedInt::div(numerator,hcf);
    UnlimitedInt* den1=UnlimitedInt::div(denominator,hcf);
    UnlimitedRational *res=new UnlimitedRational(num1,den1);
    delete numerator;
    delete denominator;
    delete pos_num;
    delete pos_den;
    delete hcf;
    delete num1;
    delete den1;
    return res;
}

