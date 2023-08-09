#!/usr/bin/php-cgi
<?php
// Function to set a custom cookie value
function setCustomCookie($name, $value) {
    // Set the cookie with a custom value and an expiration time of 1 hour
    setcookie($name, $value, time() + 3600);
}

// Function to get the cookie value
function getCookieValue($name) {
    return isset($_COOKIE[$name]) ? $_COOKIE[$name] : null;
}

function getCookieName($name) {
	return isset($_COOKIE[$name]) ? $name : null;
}
// Set a custom cookie value
setCustomCookie('id', 'id1337');

$cookie_name = getCookieName('user');
// Get the cookie value
$cookie_value = getCookieValue('user');

// HTML content with cookie value
$html_content = "<html><head><title>Hello, World!</title></head><body><h1>Hello, World!</h1><p>Cookie Value: $cookie_value</p></body></html>";

// Calculate the content length
$content_length = strlen($html_content);

// Send the content
echo "Status: 200 OK\r\n";
echo "Content-Type: text/html\r\n";
echo "Set-Cookie: &cookie_name=cookie_value\r\n";
echo "\r\n";

echo $html_content;
?>
