#include <iostream>
using namespace std;


int main(void){

    string usr = "b";
    double valprod = 0;
    double valvend = 0;

    cout << "Ajuda> ";
    cin >> usr;
    if (usr == "h"){

        cout << "Calc> Digite o valor do produto: ";
        cin >> valprod;
        cout << "Calc> Digite o valor da venda: ";
        cin >> valvend;
        double vallucro = valvend - valprod;

        cout << vallucro << '\n'; }

    return 0;



}