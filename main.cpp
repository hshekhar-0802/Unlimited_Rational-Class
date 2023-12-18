#include "ulimitedrational.h"
using namespace std;
#include <iostream>

// int main(){
//     UnlimitedInt* a=new UnlimitedInt(1);
//     for(int i=1;i<20000;i++){
//         UnlimitedInt* b=new UnlimitedInt(i);
//         UnlimitedInt* c=UnlimitedInt::mul(a,b);
//         delete b;
//         b=nullptr;
//         delete a;
//         a=nullptr;
//         a=c;
//     }
//     cout<<a->to_string()<<endl;
//     delete a;
// }

int main(){
    UnlimitedInt *n1=new UnlimitedInt("-12");
    UnlimitedInt *n2=new UnlimitedInt("24");
    UnlimitedInt *d1=new UnlimitedInt("36");
    UnlimitedInt *d2=new UnlimitedInt("48");
    UnlimitedRational *r1=new UnlimitedRational(n1,d1);
    UnlimitedRational *r2=new UnlimitedRational(n2,d2);
    UnlimitedRational *ans=r1->div(r1,r2);
    cout<<ans->get_frac_str()<<endl;
    delete n1;
    delete n2;
    delete d1;
    delete d2;
    delete r1;
    delete r2;
    delete ans;
    return 0;
}