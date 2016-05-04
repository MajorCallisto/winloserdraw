<?php
header('Content-type: application/json');

include 'config.php';

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$obscureRating = "";
if ($_GET["obscureRating"] != ""){
	$obscureRating = "AND obscure = ".$_GET["obscureRating"]." ";
}

if ($_GET["isObscure"] != ""){
	$sql = "UPDATE dictionary SET obscure=".$_GET["isObscure"]." WHERE idDictionary=".$_GET["idDictionary"];
	if ($conn->query($sql) === TRUE) {
//		echo "Record updated successfully";
	} else {
//		echo "Error: " . $sql . "<br>" . $conn->error;
	}
}
$sql = "SELECT word, idDictionary FROM dictionary WHERE partOfSpeech = \"A\" ".$obscureRating."ORDER BY RAND() LIMIT 1;";
$res = $conn->query($sql)->fetch_assoc();
$adjective = $res["word"];
$adjectiveId = $res["idDictionary"];

$sql = "SELECT word, idDictionary FROM dictionary WHERE partOfSpeech = \"N\" ".$obscureRating."ORDER BY RAND() LIMIT 1;";
$res = $conn->query($sql)->fetch_assoc();
$noun = $res["word"];
$nounId = $res["idDictionary"];
$conn->close();

echo "{\"noun\":\"$noun\", \"nounId\":$nounId, \"adjective\":\"$adjective\", \"adjectiveId\": $adjectiveId}";

?>