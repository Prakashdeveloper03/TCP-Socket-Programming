import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("localhost", 3880))
num1 = float(input("Enter first number: "))
num2 = float(input("Enter second number: "))
s.sendall(f"{num1},{num2}".encode())
result = s.recv(1024).decode()
parts = result.split(",")
print(f"Addition: {parts[0]}")
print(f"Subtraction: {parts[1]}")
print(f"Multiplication: {parts[2]}")
print(f"Division: {parts[3]}")
s.close()
