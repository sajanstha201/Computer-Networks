import socket
import hashlib

# Function to calculate checksum (hash) of the message
def calculate_checksum(message):
    return hashlib.sha256(message.encode()).hexdigest()

# Client A details
client_a_ip = '127.0.0.1'
client_a_port = 12345
attacker_ip = '127.0.0.1'  # Attacker IP (sending through Attacker)
attacker_port = 40000

# Create UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Message to send
message = "Hello Client B, this is Client A."
checksum = calculate_checksum(message)  # Calculate checksum (hash) for integrity check
data_to_send = f"{message}|{checksum}"  # Append checksum to message

# Send message with checksum to Attacker
sock.sendto(data_to_send.encode(), (attacker_ip, attacker_port))
print(f"Client A: Sent message and checksum -> {data_to_send}")

# Close the socket
sock.close()
