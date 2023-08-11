<!DOCTYPE html>
<html>
<head>
    <title>GET Form Example</title>
</head>
<body>

<h2>GET Form Example</h2>

<form method="get">
    <label for="name">Name:</label>
    <input type="text" id="name" name="name">
    <br>
    <label for="age">Age:</label>
    <input type="number" id="age" name="age">
    <br>
    <input type="submit" value="Submit">
</form>

<?php
// Check if QUERY_STRING is set and not empty
if (isset($_SERVER['QUERY_STRING']) && !empty($_SERVER['QUERY_STRING'])) {
    // Parse the query string into an array
    parse_str($_SERVER['QUERY_STRING'], $queryParams);

    // Extract name and age values
    $name = $queryParams['name'] ?? '';
    $age = $queryParams['age'] ?? '';

    // Display the inputs
    if (!empty($name) && !empty($age)) {
        echo '<p style="color: green;">The age of ' . htmlspecialchars($name) .  ' is: ' . htmlspecialchars($age) . '</p>';
    }
}
?>

</body>
</html>
