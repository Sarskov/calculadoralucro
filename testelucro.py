'''print('Bem vindo')
print('')
print('Digite 1 caso queira fazer um calculo. ')
print('')
print('sair')
print('')
print('Fecha o programa. ')'''

def Manual():
    print('')
    print('1 Calcula o lucro.')
    print('2 Fecha o programa.')
    print('')

print('')
print('Ola Italo')
print('')

while True:

    usr = input('Ajuda> ')
    print('')

    if usr == '-h':
        Manual()

    if usr == '1':
        try:
            valorproduto = float(input('Calc> Digite o valor do produto: '))

            valorvenda = float(input('Calc> Digite o valor da venda: '))

            valorlucro = valorvenda - valorproduto

        

            if valorlucro < 0:
                print('Você esta perdendo dinheiro, não fassa isso. ')

            print(f'O valor do lucro é R${valorlucro}')

        except(ValueError):
            print('')
            print('Não use virgulas. Apenas ponto')
            print('')

    if usr == '2':
        break
