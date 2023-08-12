#!/usr/bin/env python

import cgi
import cgitb

cgitb.enable()

def main():
    form = cgi.FieldStorage()
    name = form.getvalue("name", "")
    age = form.getvalue("age", "")
    height = form.getvalue("height", "")
    weight = form.getvalue("weight", "")
    skin_color = form.getvalue("skin_color", "")

    print("<html>")
    print("<head><title>Personal Profile</title></head>")
    print("<body>")
    print("<h1>Personal Profile</h1>")

    # Display the form
    print("<form method='post'>")
    print("Name: <input type='text' name='name' value='%s'><br>" % name)
    print("Age: <input type='text' name='age' value='%s'><br>" % age)
    print("Height: <input type='text' name='height' value='%s'><br>" % height)
    print("Weight: <input type='text' name='weight' value='%s'><br>" % weight)

    # Dropdown list for skin color
    skin_colors = ["", "Fair", "Medium", "Dark"]
    print("Skin Color: <select name='skin_color'>")
    for color in skin_colors:
        selected = "selected" if color == skin_color else ""
        print("<option value='%s' %s>%s</option>" % (color, selected, color))
    print("</select><br>")

    print("<input type='submit' value='Submit'>")
    print("</form>")

    # Display the result
    if name and age and height and weight and skin_color:
        print("<h2>Result:</h2>")
        print("<table border='1'>")
        print("<tr><th>Name</th><th>Age</th><th>Height</th><th>Weight</th><th>Skin Color</th></tr>")
        print("<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>" % (name, age, height, weight, skin_color))
        print("</table>")

    print("</body>")
    print("</html>")

if __name__ == "__main__":
    main()
