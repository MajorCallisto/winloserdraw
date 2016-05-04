<?php
include 'config.php';

if (!function_exists('mysqli_init') && !extension_loaded('mysqli')) {
    echo 'We don\'t have mysqli!!!';
} else {
    echo 'Connected!';
}

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}


/*
$file = fopen("selectedDictionary.json","r");
$cnt = 0;
$start = false;
$lastword = "vivandi";
while(! feof($file))
{
	$cnt = $cnt+1;
	$str = 	fgets($file);
	
	list($word, $pos) = explode("×", $str);
	
	if ($word == $lastword){
		$start = true;
		continue;
	}
	if ($start == false){
		continue;	
	}
	
	$pos = trim($pos);
	if (strcmp($pos, "N") ==0 || strcmp($pos, "A") ==0){
		$sql = "INSERT INTO dictionary (idDictionary, word, partOfSpeech) VALUES (null, \"$word\", \"$pos\")";
		if ($conn->query($sql) === TRUE) {
			//echo "New record created successfully";
		} else {
			echo "Error: " . $sql . "<br>" . $conn->error;
		}
		
		if ($cnt % 5000 == 0){
			echo "<br>".$cnt;
			flush();
			
			$conn->close();
			// Create connection
			$conn = new mysqli($servername, $username, $password, $dbname);
		}
	}
*/	
}
fclose($file);

$conn->close();

?> 