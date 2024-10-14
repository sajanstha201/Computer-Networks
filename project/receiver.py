import socket
import hashlib

# Function to calculate checksum (hash) of the message
def calculate_checksum(message):
    return hashlib.sha256(message.encode()).hexdigest()

# Function for NIDS to detect tampering
def nids_detect(message, received_checksum):
    calculated_checksum = calculate_checksum(message)
    if calculated_checksum == received_checksum:
        print("NIDS: No tampering detected.")
    else:
        print("NIDS: Tampering detected! Message was altered.")

# Client B details
client_b_ip = '127.0.0.1'
client_b_port = 54321

# Create UDP socket for Client B
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((client_b_ip, client_b_port))

# Receive message from Attacker (which was originally from Client A)
data, addr = sock.recvfrom(1024)
received_data = data.decode()

# Extract message and checksum
message, received_checksum = received_data.split('|')
print(f"Client B: Received message -> {message}")

# Run NIDS to check if the message has been tampered with
nids_detect(message, received_checksum)

# Close the socket
sock.close()
