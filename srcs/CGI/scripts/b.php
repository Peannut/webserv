<?php
// Set a cookie named "user" with the value "John" that expires in 1 hour
setcookie('user', 'John', time() + 3600);

// Now you can start outputting HTML content
?>
<!DOCTYPE html>
<html>
<head>
    <title>Cookie Test</title>
</head>
<body>
    <?php
    // Check if a cookie named "user" exists
    if(isset($_COOKIE['user'])) {
        $username = $_COOKIE['user'];
        echo "Welcome back, $username!";
    } else {
        echo "Welcome, guest!";
    }

    // Display a link to reset the cookie
    echo '<br><a href="c.php">Reset Cookie</a>';
    ?>
</body>
</html>
