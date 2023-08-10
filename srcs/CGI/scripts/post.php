#!/usr/bin/php
<?php
// Read raw POST data
$input = file_get_contents('php://input');
parse_str($input, $postData);

$hobby = isset($postData['hobby']) ? $postData['hobby'] : '';
$time = isset($postData['time']) ? $postData['time'] : '';

// Generate response headers
$responseHeaders = [
    "HTTP/1.1 200 OK",
    "Content-Type: text/html",
];

// Calculate content length based on the actual content
$content = '<!DOCTYPE html>
<html>
<head>
    <title>Hobby and Time</title>
</head>
<body>
    <form action="" method="POST">
        <label for="hobby">Hobby:</label>
        <input type="text" name="hobby" id="hobby" required><br><br>

        <label for="time">Time:</label>
        <input type="number" name="time" id="time" required><br><br>

        <input type="submit" value="Submit">
    </form>';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $content .= '<p style="color: green;">The time of ' . htmlspecialchars($hobby) .  ' is: ' . htmlspecialchars($time) . '</p>';
}

$content .= '</body>
</html>';

$contentLength = strlen($content);
$responseHeaders[] = "Content-Length: " . $contentLength;

// Output response headers
foreach ($responseHeaders as $header) {
    header($header);
}
echo "\r\n"; // Empty line after headers

// Output the content
echo $content;
?>
