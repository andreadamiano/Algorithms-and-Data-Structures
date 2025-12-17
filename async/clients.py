import socket
from concurrent.futures import ProcessPoolExecutor
import os

UDP_IP = "127.0.0.1"
UDP_PORT = 41234
MESSAGE = b"Hello, World!"


def client():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Send message
    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
    print(f"Sent: {MESSAGE} from {os.getpid()}")

    # Wait for response
    data, addr = sock.recvfrom(1024)  # Buffer size 1024
    print(f"Received: {data} from {addr}")

    sock.close()



with ProcessPoolExecutor(max_workers=1000) as executor:
    futures = [executor.submit(client) for _ in range(100000)]
    for f in futures:
        f.result()
