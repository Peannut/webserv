#!/usr/bin/env python3

import sys
import os

# Read the content length from environment variables
content_length = int(os.environ.get('CONTENT_LENGTH', 0))

# Read the request body from stdin
request_body = sys.stdin.read(content_length)

# Output the response headers
print("Content-Type: text/plain")
print(f"Content-Length: {len(request_body)}")
print()

# Echo the request body back in the response
if request_body:
    print(request_body)
else:
    print("Request body is empty")
