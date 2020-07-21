#include <bits/stdc++.h>
using namespace std;
void marye (int valor, int item, float desconto, string nome) {
    int pagamento = 0;
    ofstream myfile; // file do tipo output
        myfile.open ("fidelidade.txt", ios::out);
    cout << ". Forma de pagamento:" << endl;
    cout << " (1) Dinheiro - 5% desconto;" << endl;
    cout << " (2) Cartão. " << endl;
    cin >> pagamento;
    if (pagamento == 1){ // se pagamento for no dinheiro o desconto é maior.
        desconto = desconto+ 0.05;
        }
    valor = valor - valor*desconto;
    cout << "Você recebe " << desconto*100 << "%, e sua conta e R$ " << valor << "." << endl;
    cout << "Obrigada, " << nome << ", volte sempre!!";
    myfile << nome << "gastou R$" << valor << endl; // cout pro buffer do arquivo, fica guardando pra escrever de uma vez so
    //myfile << "ola" << endl;
    myfile.close(); // fechar. buffer = caixa que vai guardando pra usar. flush no buffer ele usa.
 }
int main(){

    int cardapio;
    int mais_alguma_coisa = 1;
    int valor = 0;
    int primeira_vez = 1;
    int item = 0;
    int quantidade = 0;
    float desconto;
    string nome;


    cout << "Oi, Bem vindo!" << endl;
    while (mais_alguma_coisa == 1){
        if (primeira_vez == 1){
        cout << "Qual seu nome?" << endl;
        cin >> nome;
        }
        if (primeira_vez == 1 and nome == "catita"){
            cout << "Voce e um cliente VIP, coma o que quiser:" << endl;
        } else if (primeira_vez == 1 and nome != "catita"){
            cout << "Estamos com promocao! Consumindo 3 itens voce ganha 10% de desconto!" << endl;
        }
        cout << "Escolha um item do cardápio:" << endl;
        cout << " (1) Cafézito R$ 10,00;" << endl;
        cout << " (2) Carolina R$ 20,00;" << endl;
        cout << " (3) Coxinha R$ 20,00." << endl;
        if (primeira_vez == 1){
            cout << " (4) Errei, hoje nao quero nada." << endl;
        } else {
            cout << " (4) Era so aquilo mesmo, obrigadx" << endl;
        }

        cin >> cardapio;
        cout << "Quantos voce quer desse item?" << endl;
        cin >> quantidade;

        if (cardapio == 1){
            valor = valor + 10*quantidade; // preço*quantidade de itens
            item = item + quantidade; // quantidade de itens
        } else if (cardapio == 2 or cardapio == 3) {
            valor = valor + 20*quantidade;
            item = item + quantidade;
        } else if (primeira_vez == 1 and cardapio == 4) {
            cout << "QUE PENA! VOLTE SEMPRE! =D" << endl;
            return 0;
        }
        primeira_vez = 2;
      	if (cardapio != 4) {
            cout << "Mais alguma coisa:" << endl;
            cout << "(1) sim" << endl;
            cout << "(2) nao." << endl;
            cin >> mais_alguma_coisa;
        } else {
            mais_alguma_coisa = 2;
        }
    }
    if (nome != "catita" and nome != "geladinho" and item >= 3){
        desconto = 0.10;
        marye (valor, item, desconto, nome);
    }
    else if (nome != "catita" and nome != "geladinho" and item < 3){
        desconto = 0;
        marye (valor, item, desconto, nome);
    }
    else if (nome == "catita") {
        desconto = 1;
        cout << "Obrigada por ter vindo. Ate mais" << endl;
    }
    else if (nome == "geladinho"){
        desconto = 0.50;
        marye (valor, item, desconto, nome);
    }

    return 0;
}
