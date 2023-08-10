#!/usr/bin/php-cgi
<?php
echo "Status: 200 OK\r\n";
echo "Content-Type: text/html\r\n";
echo "\r\n";
?>

<!DOCTYPE html>
<html>
<body>

<form method="post" action="">
  Name: <input type="text" name="fname">
  <input type="submit">
</form>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // collect value of input field
    $name = $_POST['fname'];
    if (empty($name)) {
        echo "Name is empty";
    } else {
        echo $name;
    }
}
?>

</body>
</html>
