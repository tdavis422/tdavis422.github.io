<!-- Connects the database to the Front-end -->

<?php
//define variables for connecting to database
$db['db_host'] = "localhost";
$db['db_user'] = "tdavis422";
$db['db_name'] = "capstone";
$db['db_pass'] = "test";

foreach($db as $key => $value){
    define(strtoupper($key), $value);
}

//verifies connection to database is active and ready for commands
$connection = mysqli_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME);

if($connection){
    //echo "We are connected";
}
?>