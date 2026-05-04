#include "tlistacom.h"
#include <iostream>

using namespace std;

int main(void)
{
  const TListaCom l;

  if (l.EsVacia()==true){
    cout<<"SI"<<endl;
  }else{
    cout<<"NO"<<endl;
  }

  if (l.Longitud()==0){
    cout<<"SI"<<endl;
  }else{
    cout<<"NO"<<endl;
  }

  return 0;
}
