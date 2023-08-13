#!/usr/bin/python

import cgi

# Create instance of FieldStorage 
form = cgi.FieldStorage() 

# Get data from fields
first_name = form.getvalue('f')
last_name  = form.getvalue('l')

# Print the response header
print ("Content-type:text/html\r\n\r\n")
print ("<html>")
print ("<head>")
print ("<title>POST Form Example</title>")
print ("</head>")
print ("<body>")
print ("<form action=\"\" method=\"post\">")
print ("<label for=\"f\">First Name:</label>")
print ("<input type=\"text\" id=\"f\" name=\"f\" required><br><br>")
print ("<label for=\"l\">Last Name:</label>")
print ("<input type=\"text\" id=\"l\" name=\"l\" required><br><br>")
print ("<input type=\"submit\" value=\"Submit\">")
print ("</form>")

# Check if first_name and last_name are provided in the POST data
if first_name and last_name:
    print ("<h2>Hello %s %s</h2>" % (first_name, last_name))
else:
    print ("<h2>Welcome, guest!</h2>")

print ("</body>")
print ("</html>")
