import socket
import threading
from datetime import datetime

def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    while True:
        try:
            client.connect(('localhost', 5000))
            break
        except:
            print('\nTentando se conectar ao servidor...\n')

    senha = input("Digite a senha para entrar: ")
    client.send(senha.encode('utf-8'))
    resposta = client.recv(2048).decode('utf-8')
    
    if resposta == "Senha incorreta. Conexão recusada.":
        print(resposta)
        client.close()
        return

    print(resposta)
    username = input('Usuário> ')
    print('\nConectado! Digite @sair para sair do chat.\n')

    client.send(username.encode('utf-8'))

    thread1 = threading.Thread(target=receive_messages, args=(client,))
    thread2 = threading.Thread(target=send_messages, args=(client, username))

    thread1.start()
    thread2.start()

def receive_messages(client):
    while True:
        try:
            msg = client.recv(2048).decode('utf-8')
            if msg != '':            
                print(f"\n{msg}\n")
                print('Digite uma mensagem ou comando: ')
        except:
            print('Você foi desconectado do chat!\n')
            client.close()
            break


def send_messages(client, username):
    while True:
        try:
            msg = input('Digite uma mensagem ou comando: ')
            timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

            if msg:
                if msg.startswith('@sair'):
                    client.send('@sair'.encode('utf-8'))
                    print("Saindo do chat...")
                    client.close()
                    break

                elif msg.startswith('@privado:'):
                    mensagem_privada = msg[9:].strip()
                    if ' ' in mensagem_privada:
                        destinatario, mensagem = mensagem_privada.split(' ', 1)
                        client.send(f'@privado: {destinatario} {mensagem}'.encode('utf-8'))
                    else:
                        print("Erro: Mensagem privada não formatada corretamente.")
                else:
                    client.send(f'[{timestamp}] <{username}> {msg}'.encode('utf-8'))

        except:
            client.close()
            return

main()
