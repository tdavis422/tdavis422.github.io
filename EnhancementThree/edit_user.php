<?php
    require './db.php';
    
    //verifies if user called to go to edit
    if(isset($_GET['edit_user'])){
        $editUserID = $_GET['edit_user'];
        $query = "SELECT * FROM users ";
        $query .= "LEFT JOIN location ON users.userID=location.userID ";
        $query .= "LEFT JOIN userlegalname ON users.userID=userlegalname.userID";
        $select_users_query = mysqli_query($connection, $query);
        $row_cnt = mysqli_num_rows($select_users_query);
        
        //loops through system to find the correct userID
        //I tried to combine this into the query above but 
        //would error due to the joins
        for($i = 0; $i < $row_cnt; $i++){
            $row = mysqli_fetch_assoc($select_users_query);
            if($row['userID'] == $editUserID){
                $userID = $row['userID'];
                $firstName = $row['firstName'];
                $lastName = $row['lastName'];
                $username = $row['username'];
                $password = $row['password'];
                $email = $row['email'];
                $address = $row['address'];
                $city = $row['city'];
                $state = $row['state'];
                $zipCode = $row['zipCode'];
            }
        }
    }

    //if the submit button was pressed, then this is executed
    if(isset($_POST['edit_user'])){
        $firstName = $_POST['firstName'];
        $lastName = $_POST['lastName'];
        $username = $_POST['username'];
        $password = $_POST['password'];
        $email = $_POST['email'];
        $address = $row['address'];
        $city = $row['city'];
        $state = $row['state'];
        $zipCode = $row['zipCode'];

        //queries the database to get the string to encrypt the password
        $query = "SELECT randSalt FROM users";
        $select_randsalt_query = mysqli_query($connection, $query);

        //if the query fails, then the program disregards the rest
        if(!$select_randsalt_query){
            die("QUERY FAILED ".mysqli_error($connection));
        }

        //finds the value for the salt to use for encryption
        $row = mysqli_fetch_array($select_randsalt_query);
        $salt = $row['randSalt'];
        $hashed_password = crypt($password, $salt);

        //Edit user was split into three update queries
        //to ensure each table is updated without errors
        $query = "UPDATE users SET ";
        $query .="username = '{$username}', ";
        $query .="password = '{$hashed_password}', ";
        $query .="email = '{$email}' ";
        $query .="WHERE userID = {$editUserID}";

        $edit_user_query = mysqli_query($connection, $query);
        //confirm_query($edit_user_query);

        $query = "UPDATE location SET ";
        $query .= "address = '{$address}' ";
        $query .= "city = '{$city}' ";
        $query .= "state = '{$state}' ";
        $query .= "zipCode = '{$zipCode}' ";
        $query .= "WHERE userID = {$editUserID}";
        $edit_location_query = mysqli_query($connection, $query);

        $query = "UPDATE userlegalname SET ";
        $query .= "firstName = '{$firstName}' ";
        $query .= "lastName = '{$lastName}' ";
        $query .= "WHERE userID = {$editUserID}";
        echo "User was edited", "\n";
    }
?>
<a href='./index.php'>Home</a>
<form class="" action="" method="post" enctype="multipart/form-data">
    <div class="form-group">
        <label for="username">First Name</label>
        <input type="text" class="form-control" value="<?=$firstName?>" name="firstName">
    </div>

    <div class="form-group">
        <label for="lastName">Last Name</label>
        <input type="text" class="form-control" value="<?=$lastName?>" name="lastName">
    </div>

    <div class="form-group">
        <label for="username">Username</label>
        <input type="text" class="form-control" value="<?=$username?>" name="username">
    </div>

    <div class="form-group">
        <label for="password">Password</label>
        <input type="password" class="form-control" value="<?=$password?>" name="password">
    </div>

    <div class="form-group">
        <label for="email">Email</label>
        <input type="email" class="form-control" value="<?=$email?>" name="email">
    </div>

    <div class="form-group">
        <label for="address">Street Address</label>
        <input type="text" class="form-control" value="<?=$address?>" name="address">
    </div>

    <div class="form-group">
        <label for="city">City</label>
        <input type="text" class="form-control" value="<?=$city?>" name="city">
    </div>

    <div class="form-group">
        <label for="state">State</label>
        <input type="text" class="form-control" value="<?=$state?>" name="state">
    </div>

    <div class="form-group">
        <label for="zipCode">ZIP Code</label>
        <input type="text" class="form-control" value="<?=$zipCode?>" name="zipCode">
    </div>

    <div class = "form-group">
        <input class="btn btn-primary" type="submit" name="edit_user" value="Update User">
    </div>
</form>