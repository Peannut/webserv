#!/usr/bin/php-cgi
<?php
// HTML content
$html_content = "<html><head><title>Hello, World!</title></head><body><h1>Hello, World!</h1></body></html>";

// Calculate the content length
$content_length = strlen($html_content);



// Send the content
echo ("Status: 200 OK\r\n");
echo ("Host: localhost\r\n");
echo ("Content-Type: text/html\r\n");
echo ("Content-Length: $content_length\r\n\r\n");

echo $html_content;
?>
