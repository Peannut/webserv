<?php
// Check if the cookie is set and display its value
if (isset($_COOKIE["test_cookie"])) {
    $cookieValue = $_COOKIE["test_cookie"];
    $contentLength = strlen($cookieValue);
    echo "HTTP/1.1 200 OK\r\n";
    echo "Content-length: $contentLength\r\n";
    echo "\r\n"; // Empty line to separate headers from the body
    echo $cookieValue;
} else {
    // Set a cookie with a name "test_cookie" and a value "Hello, Cookie!"
    setcookie("test_cookie", "Hello, Cookie!", time() + 3600); // Cookie will expire in 1 hour (3600 seconds)

    echo "HTTP/1.1 200 OK\r\n";
    echo "Content-length: 14\r\n"; // Length of "Cookie not set."
    echo "\r\n"; // Empty line to separate headers from the body
    echo "Cookie not set.";
}
?>
