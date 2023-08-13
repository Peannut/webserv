<?php
// Check if a cookie named "visited" is set
if (isset($_COOKIE['visited'])) {
    // If the cookie is set, it means the user has visited before
    echo "<h1>Welcome back to the website!</h1>";
} else {
    // If the cookie is not set, it means the user is visiting for the first time
    
    // Set a cookie named "visited" with a value of "true"
    setcookie('visited', 'true', time() + 3600); // Expires in 1 hour
    
    // Display the welcome message
    echo "<h1>Welcome to the website!</h1>";
}
?>
