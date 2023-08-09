<!DOCTYPE html>
<html>
<head>
    <title> WEEE </title>
</head>
<body>
    <?php
    // Retrieve the PATH_INFO value
    $pathInfo = isset($_SERVER['PATH_INFO']) ? $_SERVER['PATH_INFO'] : '';

    // Trim the leading slash if present
    $pathInfo = ltrim($pathInfo, '/');

    // If PATH_INFO is empty, display a default message
    if (empty($pathInfo)) {
        echo '<h1>No additional information provided.</h1>';
    } else {
        // Display the extracted information from PATH_INFO
        echo '<h1>Additional information: ' . htmlspecialchars($pathInfo) . '</h1>';
    }
    ?>
</body>
</html>
