<?php
// Start a session
session_start();

// Check if the session variable "counter" is set
if (isset($_SESSION['counter'])) {
    // Increment the counter
    $_SESSION['counter']++;
} else {
    // If the counter is not set, set it to 1
    $_SESSION['counter'] = 1;
}

// Display the current counter value
echo "Session counter: " . $_SESSION['counter'];
?>
