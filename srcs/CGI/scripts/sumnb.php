<!DOCTYPE html>
<html>
<head>
    <title>Addition Form</title>
</head>
<body>
    <form action="sum.php" method="GET">
        <label for="num1">Number 1:</label>
        <input type="number" name="num1" id="num1" required><br><br>

        <label for="num2">Number 2:</label>
        <input type="number" name="num2" id="num2" required><br><br>

        <input type="submit" value="Calculate">
    </form>

    <?php
    if (isset($_SERVER['QUERY_STRING']) && !empty($_SERVER['QUERY_STRING'])) {
        // Retrieve the submitted numbers
        parse_str($_SERVER['QUERY_STRING'], $queryParams);
        
        $num1 = $queryParams['num1'] ?? '';
        $num2 = $queryParams['num2'] ?? '';

        // Calculate the sum
        $sum = $num1 + $num2;

        // Display the result
        echo '<p style="color: green;">The sum of ' . $num1 . ' and ' . $num2 . ' is: ' . $sum . '</p>';
    }
    ?>
</body>
</html>