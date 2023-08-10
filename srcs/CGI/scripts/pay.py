#!/usr/bin/env python3

print("HTTP/1.1 200 OK")
print("Content-Type: text/html")
print("\r\n")
print("<!DOCTYPE html>")
print("<html>")
print("<head>")
print("<title>GET Request Test</title>")
print("</head>")
print("<body>")
print("<h1>GET Request Test</h1>")
print("<form method=\"get\">")
print("<label for=\"param1\">Parameter 1:</label>")
print("<input type=\"text\" id=\"param1\" name=\"param1\"><br>")
print("<label for=\"param2\">Parameter 2:</label>")
print("<input type=\"text\" id=\"param2\" name=\"param2\"><br>")
print("<input type=\"submit\" value=\"Submit\">")
print("</form>")

import cgi

form = cgi.FieldStorage()
param1 = form.getvalue("param1")
param2 = form.getvalue("param2")

if param1 is not None and param2 is not None:
    print("<h2>Results:</h2>")
    print(f"<p>Param 1: {param1}</p>")
    print(f"<p>Param 2: {param2}</p>")
else:
    print("<p>Both parameters are required.</p>")

print("</body>")
print("</html>")
