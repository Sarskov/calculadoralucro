'''print('Bem vindo')
print('')
print('Digite 1 caso queira fazer um calculo. ')
print('')
print('sair')
print('')
print('Fecha o programa. ')


tabela cores


vermelho == '\033[1;31m'+
branco == '\033[1;97m'+


'''


def Subtraçao():
    sv1 = float(input('Sub> Valor 1: '))
    sv2 = float(input('Sub> Valor 2: '))
    sub = sv1 - sv2 
    print(f'{sub}')
    print('')


def Multiplicaçao():
    sv1 = float(input('Mult> Valor 1: '))
    sv2 = float(input('Mult> Valor 2: '))
    mult = sv1 * sv2
    print(f'{mult}')
    print('')


def Divisao():
    sv1 = float(input('Div> Valor 1: '))
    sv2 = float(input('Div> Valor 2: '))
    div = sv1 / sv2 
    print(f'{div}')
    print('')


def Manual():
    print('')
    print('1 Calcula o lucro.')
    print('2 Fecha o programa.')
    print('a Entra nomodo de soma')
    print('s Entra no modo se subtração')
    print('m Entra no modo de multiplicação')
    print('d Entra no modo de divisão')
    print('')


print('')
print('\033[1;34m'+'Ola Italo')
print('')
Manual()
print('')

while True:

    usr = input('\033[1;97m'+'Ajuda> ')
    print('')

    if usr == '-h':
        Manual()

    if usr == '1':
        print('\033[1;31m'+'Para calcular o lucro é simples, digite o valor que')
        print('\033[1;31m'+'foi pago no produto e o valor que ele sera vendido.')
        print('')
        try:
            valorproduto = float(input('\033[1;34m'+'Calc> Digite o valor do produto: '))

            valorvenda = float(input('\033[1;34m'+'Calc> Digite o valor da venda: '))

            valorlucro = valorvenda - valorproduto

        

            if valorlucro < 0:
                print('\033[1;97m'+'Você esta perdendo dinheiro, não faça isso. ')
                print('\033[1;31m'+ f'O valor do prejuizo é R${valorlucro}')
            if valorlucro > 0:
                print('\033[1;32m'+ f'O valor do lucro é R${valorlucro}')

        except(ValueError):
            print('')
            print('Não use virgulas. Apenas ponto')
            print('')
            

    if usr == '2':
        break
    if usr == 'sair':
        break


    if usr == 'a':
        sv1 = float(input('Soma> Valor 1: '))
        sv2 = float(input('Soma> Valor 2: '))
        soma = sv1 + sv2
        print(f'{soma}')

    if usr == 's':
        Subtraçao()

    if usr == 'm':
        Multiplicaçao()

    if usr == 'd':
        Divisao()



