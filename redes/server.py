import threading
import socket
from datetime import datetime

clients = []
usernames = {}  

def handle_client(client, addr):
    # Autenticação simples
    try:
        senha_recebida = client.recv(2048).decode('utf-8')
        if senha_recebida != "senha_secreta":
            client.send("Senha incorreta. Conexão recusada.".encode('utf-8'))
            client.close()
            return
        client.send("Bem-vindo ao chat!".encode('utf-8'))
    except:
        remove_client(client)
        return

    while True:
        try:
            msg = client.recv(2048).decode('utf-8')

            if msg.startswith('@sair'):
                print(f"{addr} saiu do chat.")
                remove_client(client)
                break

            elif msg.startswith('@privado:'):
                mensagem_privada = msg[9:].strip()
                if ' ' in mensagem_privada:
                    destinatario, mensagem = mensagem_privada.split(' ', 1)
                    enviar_privado(mensagem, client, destinatario)
                else:
                    print(f"Mensagem privada mal formatada: {msg}")
            else:
                broadcast(f"[{datetime.now().strftime('%Y-%m-%d %H:%M:%S')}] {msg}", client)

        except:
            remove_client(client)
            break

def enviar_privado(msg, sender, destinatario):
    destinatario_client = None
    for client in clients:
        try:
            # Encontra o cliente pelo nome
            if client.getpeername()[0] == destinatario:
                destinatario_client = client
                break
        except:
            continue

    if destinatario_client:
        try:
            destinatario_client.send(f"[Privado] {msg}".encode('utf-8'))
        except:
            remove_client(destinatario_client)


def enviar_privado(msg, sender, destinatario):
    destinatario_client = usernames.get(destinatario)

    if destinatario_client:
        try:
            destinatario_client.send(f"[Privado] {msg}".encode('utf-8'))
        except:
            remove_client(destinatario_client)

def broadcast(msg, sender):
    for client in clients:
        if client != sender:
            try:
                client.send(msg.encode('utf-8'))
            except:
                remove_client(client)

def enviar_privado(msg, sender, destinatario):
    destinatario_client = None
    for client in clients:
        if client.getpeername()[0] == destinatario:
            destinatario_client = client
            break

    if destinatario_client:
        try:
            destinatario_client.send(f"[Privado] {msg}".encode('utf-8'))
        except:
            remove_client(destinatario_client)

def remove_client(client):
    if client in clients:
        clients.remove(client)
        client.close()

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        server.bind(("localhost", 5000))
        server.listen()
        print("Servidor de bate-papo iniciado na porta 5000")
    except:
        return print('\nNão foi possível iniciar o servidor!\n')

    while True:
        client, addr = server.accept()
        clients.append(client)
        print(f"Cliente {addr} conectado.")

        thread = threading.Thread(target=handle_client, args=(client, addr))
        thread.start()

main()
