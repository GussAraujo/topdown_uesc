import threading
import socket
from datetime import datetime

clients = []
usernames = {}

def handle_client(client, addr):
    try:
        senha_recebida = client.recv(2048).decode('utf-8')
        if senha_recebida != "a":
            client.send("Senha incorreta. Conexão recusada.".encode('utf-8'))
            client.close()
            return
        client.send("Bem-vindo ao chat!".encode('utf-8'))
    except:
        remove_client(client)
        return

    username = client.recv(2048).decode('utf-8')
    usernames[client] = username
    clients.append(client)

    broadcast(f"{username} entrou no chat.", client)

    while True:
        try:
            msg = client.recv(2048).decode('utf-8')

            if msg.startswith('@sair'):
                print(f"{username} saiu do chat.")
                broadcast(f"{username} saiu do chat.", client)
                remove_client(client)
                break

            elif msg.startswith('@privado:'):
                mensagem_privada = msg[9:].strip()
                if ' ' in mensagem_privada:
                    destinatario, mensagem = mensagem_privada.split(' ', 1)
                    enviar_privado(f"[Privado de {username}] {mensagem}", client, destinatario)
                else:
                    print(f"Mensagem privada mal formatada: {msg}")
            else:
                broadcast(msg, client)

        except:
            broadcast(f"{username} desconectou inesperadamente.", client)
            remove_client(client)
            break

def enviar_privado(msg, sender, destinatario):
    destinatario_client = None
    for client, name in usernames.items():
        if name == destinatario:
            destinatario_client = client
            break

    if destinatario_client:
        try:
            destinatario_client.send(msg.encode('utf-8'))
        except:
            remove_client(destinatario_client)
    else:
        sender.send(f"Usuário '{destinatario}' não encontrado.".encode('utf-8'))

def broadcast(msg, sender):
    for client in clients:
        if client != sender:
            try:
                client.send(msg.encode('utf-8'))
            except:
                remove_client(client)

def remove_client(client):
    if client in clients:
        clients.remove(client)
        username = usernames.get(client, "Desconhecido")
        del usernames[client]
        client.close()
        broadcast(f"{username} saiu do chat.", client)

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
        print(f"Cliente {addr} conectado.")

        thread = threading.Thread(target=handle_client, args=(client, addr))
        thread.start()

main()
