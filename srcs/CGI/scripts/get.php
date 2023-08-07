<?php
    echo "Status: 200 OK\r\n\r\n";
    if ($_SERVER["REQUEST_METHOD"] == "GET")
        echo "this is Get Method ur so Coool :)\n";
    else
        echo "You didn't request a Get method :(\n";
?>