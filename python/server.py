import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', 3880))
s.listen()
print("Waiting for client connection...")
conn, addr = s.accept()
print(f"Client connected successfully: {addr}")
while True:
    data = conn.recv(1024).decode()
    if not data:
        break
    num1, num2 = map(float, data.split(","))
    addition = num1 + num2
    subtraction = num1 - num2
    multiplication = num1 * num2
    division = num1 / num2
    print("Send the results back to the client...\n")
    conn.sendall(f"{addition},{subtraction},{multiplication},{division}".encode())
conn.close()
s.close()
