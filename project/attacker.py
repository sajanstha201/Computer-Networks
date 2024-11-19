import socket
import pickle
import hashlib

# Constants (Use the actual IPs of sender and receiver)
SENDER_IP = '127.0.0.1'  # Sender's IP
RECEIVER_IP = '127.0.0.1'  # Receiver's IP
ATTACKER_IP = '127.0.0.1'  # Attacker's IP
ATTACKER_PORT = 8081  # Port for attacker to listen
RECEIVER_PORT = 8082  # Port on the receiver to which the attacker will forward

# Function to compute checksum
def compute_checksum(data):
    return hashlib.md5(data.encode()).hexdigest()

# Attacker class
class Attacker:
    def __init__(self):
        # Set up socket to intercept packets sent to the receiver
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((ATTACKER_IP, ATTACKER_PORT))  # Bind to the attacker's port

        # Set up socket for forwarding modified packets to the receiver
        self.forward_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Intercept, modify, and forward the packet
    def intercept_and_modify(self):
        print(f"Listening on {ATTACKER_IP}:{ATTACKER_PORT} to intercept packets...")

        while True:
            # Receive packet from sender
            data, addr = self.sock.recvfrom(1024)
            packet = pickle.loads(data)
            print(f"Intercepted packet from {addr}: {packet}")

            # Extract information from the packet
            source_ip, destination_ip, port, delay_time, checksum, message = packet

            # Log original message
            print(f"Original message intercepted: {message}")

            # Get user input to modify the message
            user_input = input("Enter the modification for the message (leave empty for no modification): ")
            modified_message = message + f" {user_input}" if user_input else message  # Modify the message if input is provided

            print(f"Modified message: {modified_message}")

            # Compute new checksum for the modified message
            new_checksum = compute_checksum(modified_message)

            # Construct new packet with the modified message
            modified_packet = (source_ip, RECEIVER_IP, port, delay_time, new_checksum, modified_message)

            # Forward the modified packet to the receiver
            self.forward_sock.sendto(pickle.dumps(modified_packet), (RECEIVER_IP, RECEIVER_PORT))
            print(f"Modified packet forwarded to {RECEIVER_IP}:{RECEIVER_PORT}")

# Main function
def main():
    attacker = Attacker()
    attacker.intercept_and_modify()

if __name__ == "__main__":
    main()
