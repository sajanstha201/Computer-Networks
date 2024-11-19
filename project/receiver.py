import socket
import hashlib
import pickle
import time
# Constants (Use the actual IP of the receiver)
RECEIVER_IP = '127.0.0.1'  # Receiver's IP (this laptop)
RECEIVER_PORT = 8082  # Port the receiver listens on

# Function to compute checksum
def compute_checksum(data):
    return hashlib.md5(data.encode()).hexdigest()

# Integrity check function to validate received packets
def check_packet_integrity(received_packet):
    source_ip, destination_ip, port, delay_time, checksum, message = received_packet
    print('time delay is ',time.time()-delay_time)
    # Validate checksum
    computed_checksum = compute_checksum(message)

    if checksum != computed_checksum:
        print("Checksum mismatch! Possible attack detected.")
        return False

    print("Packet is valid.")
    return True

# Receiver Class
class Receiver:
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((RECEIVER_IP, RECEIVER_PORT))

    def receive_message(self):
        while True:
            data, addr = self.sock.recvfrom(1024)
            received_packet = pickle.loads(data)
            print(f"Received packet from {addr}: {received_packet}")

            if check_packet_integrity(received_packet):
                print("Message received:", received_packet[-1])
            else:
                print("Received an invalid packet. Data was tampered with!")

def main():
    receiver = Receiver()
    receiver.receive_message()

if __name__ == "__main__":
    main()
