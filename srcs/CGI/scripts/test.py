#!/usr/bin/env python3
import os
import http.cookies

# Read the HTTP request headers
headers = os.environ.get('HTTP_COOKIE', '')

# Parse the cookies from the headers
cookie = http.cookies.SimpleCookie(headers)

# Check if the "test_cookie" is present
if 'test_cookie' in cookie:
    cookie_value = cookie['test_cookie'].value
    print('Status: 200 OK')
    print('Content-type: text/html')
    print('\r\n')
    print('<h1>Cookie Found!</h1>')
    print('<p>Value of test_cookie: {}</p>'.format(cookie_value))
else:
    print('Status: 404 Not Found\r\n')
    print('Content-type: text/html\r\n')
    print('\r\n')
    print('<h1>Cookie Not Found!</h1>')
