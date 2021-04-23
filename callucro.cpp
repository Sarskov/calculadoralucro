#include <iostream>
using namespace std;

//int soma(double asmd1, double asmd2)
//{
 //   cout << "Mult> Valor 1:";
   // cin >> asmd1;
   // cout << "Mult> Valor 2:";
   // cin >> asmd2;
  //  double resul = asmd1 * asmd2;
  //  cout << resul << '\n';
  //  cout << "" << '\n';

  //  return 0;
  //  }
//



int main(void){
   
    string usr = "1";
    double valprod = 0;
    double valvend = 0;
    double asmd1,asmd2;


    cout << "" << '\n';
    cout << "1 Entra na calculadora de lucro " << '\n';
    cout << "sm Entra no modo de soma " << '\n';
    cout << "sb Entra no modo de subtracao" << '\n';
    cout << "mt Entra no modo de multiplicacao" << '\n';
    cout << "dv Entra no modo de divisao" << '\n';
    cout << "sair Fecha o programa" << '\n';
    cout << "" << '\n';

    while(usr != "sair"){
        cout << "" << '\n';
        cout << "Ajuda> ";
        cin >> usr;
        if (usr == "1"){

            cout << "Calc> Digite o valor do produto: ";
            cin >> valprod;
            cout << "Calc> Digite o valor da venda: ";
            cin >> valvend;
            double vallucro = valvend - valprod;
            if (vallucro < 0){
                cout << "Voce esta perdendo dinheiro, nao faça isso " << '\n';
                cout << "O valor do prejuizo é de R$";
                cout << vallucro;
                cout << "" << '\n';
            }
            if (vallucro > 0){
                cout << "O valor do lucro é de R$";
                cout << vallucro << '\n'; 
                cout << "" << '\n';
            
            }

        }

        if (usr == "sm"){
            cout << "Som> Valor 1: ";
            cin >> asmd1;
            cout << "Som> Valor 2: ";
            cin >> asmd2;
            double resul = asmd1 + asmd2;
            cout << resul << '\n'; 
            cout << "" << '\n'; 
        }

        if (usr == "sb"){
            cout << "Sub> Valor 1: ";
            cin >> asmd1;
            cout << "Sub> Valor 2: ";
            cin >> asmd2;
            double resul = asmd1 - asmd2;
            cout << resul << '\n';
            cout << "" << '\n';

        }

        if (usr == "mt"){
            cout << "Mult> Valor 1:";
            cin >> asmd1;
            cout << "Mult> Valor 2:";
            cin >> asmd2;
            double resul = asmd1 * asmd2;
            cout << resul << '\n';
            cout << "" << '\n';

        }

        if (usr == "dv"){
            cout << "Div> Valor 1:";
            cin >> asmd1;
            cout << "Div> Valor 2:";
            cin >> asmd2;
            double resul = asmd1 / asmd2;
            cout << resul << '\n';
            cout << "" << '\n';

        }

        //if (usr =="fn"){
         //   soma(asmd1, asmd2);
       // }



    }

    return 0;

}




