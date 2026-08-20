import time
import threading
from http.server import HTTPServer, BaseHTTPRequestHandler
from collections import deque

class FixedWindowRateLimiter:
    def __init__(self, max_window: float, max_requests: int):
        self.max_window = max_window
        self.max_requests = max_requests
        self.last_call_time = None
        self.call_within_period = 0
        self.lock = threading.Lock()

    def __call__(self, *args, **kwds):
        now = time.time()

        with self.lock:
            if not self.last_call_time or now - self.last_call_time > self.max_window:
                #reset fixed window
                self.last_call_time = now
                self.call_within_period = 1
                return True

            elif self.call_within_period <= self.max_requests:
                self.call_within_period += 1
                return True

            else:
                return False


class SlidingWindowRateLimiter:
    def __init__(self, max_window: float, max_requests: int):
        self.max_window = max_window
        self.max_requests = max_requests
        self.sliding_window = deque()
        self.lock = threading.Lock()

    def __call__(self, *args, **kwds):
        now = time.time()

        with self.lock:
            while self.sliding_window and now - self.sliding_window[0] > self.max_window:
                self.sliding_window.popleft()

            if len(self.sliding_window) > self.max_requests:
                return False
            else:
                self.sliding_window.append(now)
                return True


class TokenBucketRateLimiter:
    def __init__(self, token_rate: float, max_tokens: int):
        self.max_tokens = max_tokens
        self.token_ps = token_rate #tokens per seconds
        self.tokens = max_tokens
        self.last_request = None
        self.lock = threading.Lock()

    def __call__(self, *args, **kwds):
        now = time.time()

        with self.lock:
            time_elapsed = now - self.last_request if self.last_request else 0
            self.tokens = max(0, min(self.max_tokens, int(self.tokens + time_elapsed * self.token_ps)) - 1) # -1 the consumed token

            if self.tokens:
                self.last_request = now #refresh the last call timestamp
                return True
            else:
                return False


class LeakyBucketRateLimiter:
    """
    In this implementation i've decided to implement a synchronous wait on incoming API , to serve the incoming requests at a fixed rate.
    Normally this wait will happen inside a coroutine.
    """
    def __init__(self, requests_ps: float):
        self.requests_ps = requests_ps #requests per second
        self.last_request = None
        self.lock = threading.Lock()

    def __call__(self, *args, **kwds):
        now = time.time()
        time_elapsed = now - self.last_request if self.last_request else 60

        with self.lock:
            if time_elapsed * self.requests_ps >= 1:
                self.last_request = now

            else:
                time_wait = 1 / self.requests_ps - time_elapsed
                time.sleep(time_wait)
                now = time.time()
                self.last_request = now

            return True

        
class RateLimiter:
    def __init__(self, algorithm):
        self.algorithm = algorithm

    def allow_request(self):
        return self.algorithm()


class RateLimiterFactory:
    def create_rate_limiter(algorithm: str):
        match algorithm:
            case "fixed":
                return FixedWindowRateLimiter(60, 10)
            case "variable":
                return SlidingWindowRateLimiter(60, 10)
            case "token":
                return TokenBucketRateLimiter(0.16, 10)
            case "leaky":
                return LeakyBucketRateLimiter(0.16)
            case _:
                raise ValueError("Algorithm selected does not exists")


class ServerHandler(BaseHTTPRequestHandler):
    rate_limiter = RateLimiterFactory.create_rate_limiter("leaky")

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def do_GET(self):
        if self.path == "/":
            if self.rate_limiter():
                self.send_response(200)
                self.send_header("Content-Type", "text/plain")
                self.end_headers()  
                self.wfile.write(b"200 OK - Request Allowed") 
            else:
                self.send_response(429)
                self.send_header("Content-Type", "text/plain")
                self.end_headers()  
                self.wfile.write(b"429 Too Many Requests")

if __name__ == "__main__":
    server = HTTPServer(("localhost", 8080), ServerHandler)
    print("Server running on http://localhost:8080")
    server.serve_forever()