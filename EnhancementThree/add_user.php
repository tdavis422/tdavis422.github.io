<?php
    include "./db.php";

    //if the submit is pressed, this is set to start
    if(isset($_POST['create_user'])){
        $username = $_POST['username'];
        $password = $_POST['password'];
        $email = $_POST['email'];
        $firstName = $_POST['firstName'];
        $lastName = $_POST['lastName'];
        $address = $_POST['address'];
        $city = $_POST['city'];
        $state = $_POST['state'];
        $zipCode = $_POST['zipCode'];

        //find the salt for encrypting the password
        $query = "SELECT randSalt FROM randSalt";
        $select_randsalt_query = mysqli_query($connection, $query);

        //if the salt is not found, then the program ends
        if(!$select_randsalt_query){
            die("QUERY FAILED ".mysqli_error($connection));
        }

        $row = mysqli_fetch_array($select_randsalt_query);
        $salt = $row['randSalt'];
        $hashed_password = crypt($password, $salt);

        //Adds user, location, and name into each table separately
        $query = "INSERT INTO users(username, password, email) ";
        $query .= "VALUES('{$username}', '{$hashed_password}', '{$email}')";
        $add_user_query = mysqli_query($connection, $query);
        
        $query = "INSERT INTO userlegalname(firstName, lastName) ";
        $query .= "VALUES('{$firstName}', '{$lastName}')";
        $add_userlegalname_query = mysqli_query($connection, $query);

        $query = "INSERT INTO location(address, city, state, zipCode) ";
        $query .= "VALUES('{$address}', '{$city}', '{$state}', '{$zipCode}')";
        $add_user_location_query = mysqli_query($connection, $query);

        echo "User was added", "\n";
    }
?>
<a href='./index.php'>Home</a>
<form class="" action="" method="post" enctype="multipart/form-data">
    <div class="form-group">
        <label for="firstName">First Name</label>
        <input type="text" class="form-control" name="firstName">
    </div>

    <div class="form-group">
        <label for="lastName">Last Name</label>
        <input type="text" class="form-control" name="lastName">
    </div>

    <div class="form-group">
        <label for="username">Username</label>
        <input type="text" class="form-control" name="username">
    </div>

    <div class="form-group">
        <label for="password">Password</label>
        <input type="password" class="form-control" name="password">
    </div>

    <div class="form-group">
        <label for="email">Email</label>
        <input type="email" class="form-control" name="email">
    </div>

    <div class="form-group">
        <label for="address">Street Address</label>
        <input type="text" class="form-control" name="address">
    </div>

    <div class="form-group">
        <label for="city">City</label>
        <input type="text" class="form-control" name="city">
    </div>

    <div class="form-group">
        <label for="state">State</label>
        <input type="text" class="form-control" name="state">
    </div>

    <div class="form-group">
        <label for="zipCode">ZIP Code</label>
        <input type="text" class="form-control" name="zipCode">
    </div>

    <div class = "form-group">
        <input class="btn btn-primary" type="submit" name="create_user" value="Add User">
    </div>
</form>