<!DOCTYPE html>
<html>
<head>
    <title>File Upload</title>
</head>
<body>
    <form action="" method="POST" enctype="multipart/form-data">
        <label for="file">Select a file:</label>
        <input type="file" name="file" id="file"><br><br>
        <input type="submit" value="Upload">
    </form>

    <?php
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $uploadedFile = $_FILES['file'];
        $targetDir = '/Users/zoukaddo/Desktop/webserv/srcs/CGI/output/';  // Set your desired target directory
        $targetFile = $targetDir . basename($uploadedFile['name']);

        if (move_uploaded_file($uploadedFile['tmp_name'], $targetFile)) {
            echo "File uploaded successfully.";
        } else {
            echo "Error uploading file.";
        }
    }
    ?>
</body>
</html>
