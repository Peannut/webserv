#!/usr/bin/python3

# Import modules for CGI handling
import cgi, cgitb
import http.cookies

# Create instance of FieldStorage
form = cgi.FieldStorage()

# Get data from fields
first_name = form.getvalue('f')
last_name = form.getvalue('l')

# Create a new cookie
cookie = http.cookies.SimpleCookie()
cookie['first_name'] = first_name
cookie['last_name'] = last_name

print ("Content-type:text/html\r\n")
print (cookie.output())
print ("<html>")
print ("<head>")
print ("<title>Hello - Second CGI Program</title>")
print ("</head>")
print ("<body>")
print ("<h2>Hello %s %s</h2>" % (first_name, last_name))
print ("</body>")
print ("</html>")
