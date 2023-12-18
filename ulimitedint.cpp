
#include "ulimitedint.h"

UnlimitedInt::UnlimitedInt(){
    size=1;
    sign=1;
    capacity=1;
    unlimited_int=new int[1];
    unlimited_int[0]=0;
}

UnlimitedInt::UnlimitedInt(string s){
    size=s.length();
    sign=1;
    capacity=size;
    if(s[0]=='-'){
        sign=-1;
        size--;
        capacity=size;
        s=s.substr(1,s.length()-1);
    }
    unlimited_int = new int[size];
    int idx = s.length() - 1;
    while (idx >= 0)
    {
        unlimited_int[idx] = s[idx] - 48;
        idx--;
    }
}

UnlimitedInt::UnlimitedInt(int i){
    sign = 1;
    if (i < 0){
        sign = -1;
        i = i * -1;
    }
    size = 0;
    int k = i;
    if (k == 0){
        unlimited_int = new int[1];
        unlimited_int[0] = 0;
        capacity = 1;
        size = 1;
        return;
    }
    while (k > 0){
        k = k / 10;
        size++;
    }
    k = size-1;
    unlimited_int = new int[size];
    while (i > 0){
        unlimited_int[k] = i % 10;
        i = i / 10;
        k--;
    }
    capacity = size;
}

UnlimitedInt::UnlimitedInt(int* ulimited_int,int cap, int sgn, int sz){
    capacity=cap;
    size=sz;
    sign=sgn;
    unlimited_int=new int[size];
    for(int i=0;i<size;i++){
        unlimited_int[i]=ulimited_int[i];
    }
}

UnlimitedInt::~UnlimitedInt(){
    delete[] unlimited_int;
}

int UnlimitedInt::get_size(){
    return size;
}

int* UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}

string UnlimitedInt::to_string(){
    string s = "";
    if (sign == -1)
    {
        s = s + "-";
    }
    for (int i = 0; i < size; i++)
    {
        s += std::to_string(unlimited_int[i]);
    }
    return s;
}

int compare(UnlimitedInt* i1, UnlimitedInt* i2){
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

UnlimitedInt* adder(UnlimitedInt* i1, UnlimitedInt* i2){
    int sign=i1->get_sign();
    int size=i1->get_size();
    if(size<i2->get_size()){
        size=i2->get_size();
    }
    size++;
    int capacity=size;
    int* answer=new int[size];
    for(int i=0;i<size;i++){
        answer[i]=0;
    }
    int* arr1=i1->get_array();
    int* arr2=i2->get_array();
    int idx=size-1, idx2=i2->get_size()-1, idx1=i1->get_size()-1;
    int sum=0,carry=0;
    for(int i=size-1;i>=0;i--){
        int a1=0,a2=0;
        if(idx1>=0){
            a1=arr1[idx1];
        }
        if(idx2>=0){
            a2=arr2[idx2];
        }
        sum=a1+a2+carry;
        carry=sum/10;
        answer[idx]=sum%10;
        idx--;
        idx1--;
        idx2--;
    }
    int k=0;
    while(answer[k]==0 && k<size){
        k++;
    }
    int* trimmed=new int[size-k];
    for(int i=0;i<size-k;i++){
        trimmed[i]=answer[i+k];
    }
    delete[] answer;
    UnlimitedInt* result=new UnlimitedInt(trimmed,size-k,sign,size-k);
    delete[] trimmed;
    return result;
}

UnlimitedInt* subtractor(UnlimitedInt* i1, UnlimitedInt* i2){
    int big=compare(i1,i2);
    if(big==0){
        UnlimitedInt* answer=new UnlimitedInt(0);
        return answer;
    }
    else if(big==1){
        int sign=i1->get_sign();
        int size=i1->get_size();
        int* answer=new int[size];
        for(int i=0;i<size;i++){
            answer[i]=0;
        }
        int* arr1=i1->get_array();
        int* arr2=i2->get_array();
        int diff=0,borrow=0,idx=size-1,idx1=size-1,idx2=i2->get_size()-1;
        for(int i=size-1;i>=0;i--){
            int a1=0,a2=0;
            if(idx1>=0){
                a1=arr1[idx1];
            }
            if(idx2>=0){
                a2=arr2[idx2];
            }
            diff=a1-a2-borrow;
            if(diff<0){
                diff+=10;
                borrow=1;
            }
            else{
                borrow=0;
            }
            answer[idx]=diff;
            idx--;
            idx1--;
            idx2--;
        }
        int k=0;
        while(answer[k]==0 && k<size){
            k++;
        }
        int* trimmed=new int[size-k];
        for(int i=0;i<size-k;i++){
            trimmed[i]=answer[i+k];
        }
        delete[] answer;
        UnlimitedInt* result=new UnlimitedInt(trimmed,size-k,sign,size-k);
        delete[] trimmed;
        return result;
    }
    else{
        UnlimitedInt* ans=subtractor(i2,i1);
        int sign = ans->get_sign() * -1;
        UnlimitedInt *res = new UnlimitedInt(ans->get_array(), ans->get_capacity(), sign, ans->get_size());
        delete ans;
        return res;
    }
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    int sign = i1->get_sign() * i2->get_sign();
    int size=i1->get_size()+i2->get_size();
    int* answer=new int[size];
    for(int i=0;i<size;i++){
        answer[i]=0;
    }
    int* arr1=i1->get_array();
    int* arr2=i2->get_array();int idx = size - 1;
    int pro = 0, carry_pro = 0, carry_sum = 0;
    int idx1 = i1->get_size() - 1;
    int idx2 = i2->get_size() - 1;
    while (idx1 >= 0)
    {
        idx = size - 1;
        while (carry_sum > 0 || carry_pro > 0 || idx2 >= 0)
        {
            int a1 = 0, a2 = 0;
            if (idx1 >= 0)
            {
                a1 = arr1[idx1];
            }
            if (idx2 >= 0)
            {
                a2 = arr2[idx2];
            }
            pro = (a1 * a2) + carry_pro;
            carry_pro = pro / 10;
            answer[idx] += pro % 10 + carry_sum;
            carry_sum = answer[idx] / 10;
            answer[idx] = answer[idx] % 10;
            idx--;
            idx2--;
        }
        size--;
        idx = size - 1;
        idx1--;
        idx2 = i2->get_size() - 1;
    }
    size = i1->get_size() + i2->get_size();
    int k = 0;
    while (answer[k] == 0 && k < size)
    {
        k++;
    }
    if (k == size)
    {
        UnlimitedInt *res = new UnlimitedInt();
        delete[] answer;
        return res;
    }
    int *trimmed =new int[size-k];
    for(int i=0;i<size-k;i++){
        trimmed[i]=answer[i+k];
    }
    UnlimitedInt *res = new UnlimitedInt(trimmed, size - k, sign, size - k);
    delete[] answer;
    delete[] trimmed;
    return res;
}

string sum(string s1, string s2){
    UnlimitedInt* i1=new UnlimitedInt(s1);
    UnlimitedInt* i2=new UnlimitedInt(s2);
    UnlimitedInt* i3=i1->add(i1,i2);
    delete i1;
    delete i2;
    string s=i3->to_string();
    delete i3;
    return s;
}

string difference(string s1, string s2){
    UnlimitedInt* i1=new UnlimitedInt(s1);
    UnlimitedInt* i2= new UnlimitedInt(s2);
    UnlimitedInt* i3=i1->sub(i1,i2);
    string s=i3->to_string();
    delete i1;
    delete i2;
    delete i3;
    return s;
}

int strcompare(string s1, string s2){
    UnlimitedInt* i1=new UnlimitedInt(s1);
    UnlimitedInt* i2=new UnlimitedInt(s2);
    int i=compare(i1,i2);
    delete i1;
    delete i2;
    return i;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    if(compare(i1,i2)==2 && i1->get_sign()*i2->get_sign()==1){
        UnlimitedInt* result=new UnlimitedInt(0);
        return result;
    }
    else if(compare(i1,i2)==2 && i1->get_sign()*i2->get_sign()==-1){
        UnlimitedInt* result=new UnlimitedInt(-1);
        return result;
    }
    string s1=i1->to_string();
    string s2=i2->to_string();
    if(s1[0]=='-'){
        s1=s1.substr(1,s1.length()-1);
    }
    if(s2[0]=='-'){
        s2=s2.substr(1,s2.length()-1);
    }
    string answer="";
    int val=0;
    string dividend=s1.substr(0,s2.length()),divisor=s2;
    int ptr=s2.length();
    while(ptr<=s1.length()){
        val=0;
        while(strcompare(dividend,divisor)==1 || strcompare(dividend,divisor)==0){
            divisor=sum(divisor,s2);
            val++;
        }
        answer+=std::to_string(val);
        divisor=difference(divisor,s2);
        dividend=difference(dividend,divisor);
        if(ptr<s1.length()){
            dividend+=s1[ptr];
        }
        divisor=s2;
        ptr++;
    }
    int k=0;
    while(k<answer.length() && answer[k]=='0'){
        k++;
    }
    answer=answer.substr(k,answer.length()-k);
    if(i1->get_sign()*i2->get_sign()==1){
        UnlimitedInt* res=new UnlimitedInt(answer);
        return res;
    }
    else if(dividend=="0"){
        answer="-"+answer;
        UnlimitedInt* res= new UnlimitedInt(answer);
        return res;
    }
    else{
        answer="-"+answer;
        answer=difference(answer,"1");
        UnlimitedInt* res= new UnlimitedInt(answer);
        return res;
    }
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* a=div(i1,i2);
    UnlimitedInt* b=mul(i2,a);
    UnlimitedInt* c=sub(i1,b);
    delete b;
    delete a;
    return c;
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    if(i1->get_sign()*i2->get_sign()==1){
        UnlimitedInt* ans=subtractor(i1,i2);
        return ans;
    }
    else if(i1->get_sign()*i2->get_sign()==-1){
        UnlimitedInt* ans=adder(i1,i2);
        return ans;
    }
    return i1;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    if(i1->get_sign()*i2->get_sign()==1){
        UnlimitedInt* ans=adder(i1,i2);
        return ans;
    }
    else if(i1->get_sign()*i2->get_sign()==-1){
        if(compare(i1,i2)==1){
            UnlimitedInt* ans=subtractor(i1,i2);
            return ans;
        }
        else{
            UnlimitedInt* ans=subtractor(i1,i2);
            int sign=ans->get_sign();
            UnlimitedInt* result=new UnlimitedInt(ans->get_array(),ans->get_capacity(),sign*-1,ans->get_size());
            delete ans;
            return result;
        }
    }
    return i1;
}

