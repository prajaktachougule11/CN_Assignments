import socket
# Server configuration
SERVER_IP = "127.0.0.1"
SERVER_PORT = 5000
# Create UDP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
print("===================================")
print("       UDP CLIENT STARTED")
print("===================================")
# Take input from user
message = input("Enter an uppercase string: ")
# Send message to server
client_socket.sendto(
    message.encode(),
    (SERVER_IP, SERVER_PORT)
)
print()
print("Message sent successfully to server.")
# Receive response from server
data, server_address = client_socket.recvfrom(1024)
# Convert bytes to string
result = data.decode()
print(f"Server Address : {server_address}")
print(f"Original       : {message}")
print(f"Lowercase      : {result}")
# Close socket
client_socket.close()
print()
print("Client socket closed.")
