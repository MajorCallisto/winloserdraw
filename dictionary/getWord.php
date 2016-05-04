<?php
header('Content-type: application/json');

include 'config.php';

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
$sql = "SELECT word FROM dictionary WHERE partOfSpeech = \"A\" ORDER BY RAND() LIMIT 1;";
$adjective = $conn->query($sql)->fetch_assoc()["word"];

$sql = "SELECT word FROM dictionary WHERE partOfSpeech = \"N\" ORDER BY RAND() LIMIT 1;";
$noun = $conn->query($sql)->fetch_assoc()["word"];
$conn->close();

echo "{'noun':$noun,'adjective':$adjetive}";
?>