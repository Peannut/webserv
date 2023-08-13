#!/usr/bin/python

import cgi, cgitb

# Create instance of FieldStorage 
form = cgi.FieldStorage() 

# Get data from fields
first_name = form.getvalue('f')
last_name  = form.getvalue('l')

# Print the response header
print ("Content-type:text/html\r\n\r\n")
print ("<html>")
print ("<head>")
print ("<title>Hello - Second CGI Program</title>")
print ("</head>")
print ("<body>")

# Check if first_name and last_name are provided in the query string
if first_name and last_name:
    print ("<h2>Hello %s %s</h2>" % (first_name, last_name))
else:
    print ("<h2>Welcome, guest!</h2>")

# Print the HTML form
print ('''<form action="" method="get">
    <label for="f">First Name:</label>
    <input type="text" id="f" name="f" required><br><br>
    
    <label for="l">Last Name:</label>
    <input type="text" id="l" name="l" required><br><br>
    
    <input type="submit" value="Submit">
</form>''')

print ("</body>")
print ("</html>")
