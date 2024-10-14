import socket

# Attacker details
attacker_ip = '127.0.0.1'
attacker_port = 40000
client_b_ip = '127.0.0.1'
client_b_port = 54321

# Create UDP socket for Attacker
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((attacker_ip, attacker_port))

# Listen for message from Client A
print("Attacker: Waiting to intercept the message...")
data, addr = sock.recvfrom(1024)
received_data = data.decode()

# Modify the message
message, checksum = received_data.split('|')
modified_message = "Hacked message from Attacker!"

# Forward the modified message to Client B (with the original checksum)
modified_data = f"{modified_message}|{checksum}"
sock.sendto(modified_data.encode(), (client_b_ip, client_b_port))
print(f"Attacker: Modified and sent message to Client B -> {modified_data}")

# Close the socket
sock.close()
