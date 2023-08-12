<?php
// Reset the cookie by setting its expiration time to the past
setcookie('user', '', time() - 3600);

// Redirect back to the main page
header('Location: b.php');
?>
