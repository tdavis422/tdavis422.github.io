<?php 
	//ensures connection to database
	include "./db.php";
?>
<a href='./add_user.php'>Add User</a>
<table>
	<thead>
		<tr>
			<th>User ID</th>
			<th>First Name</th>
			<th>Last Name</th>
			<th>Username</th>
			<th>Password</th>
			<th>Email</th>
			<th>Address</th>
			<th>City</th>
			<th>State</th>
			<th>ZIP Code</th>
			<th>Edit</th>
			<th>Delete</th>
		</tr>
	</thead>
	<tbody>
		<?php
		//Query the database to display all users and combine tables to ensure all data is shown
			$query = "SELECT * FROM users ";
			$query .= "LEFT JOIN location ON users.userID = location.userID ";
			$query .= "LEFT JOIN userlegalname ON users.userID = userlegalname.userID";
			$select_users = mysqli_query($connection, $query);
			while($row = mysqli_fetch_assoc($select_users)){
				$user_id = $row['userID'];
				$firstName = $row['firstName'];
				$lastName = $row['lastName'];
				$username = $row['username'];
				$password = $row['password'];
				$email = $row['email'];
				$address = $row['address'];
				$city = $row['city'];
				$state = $row['state'];
				$zipCode = $row['zipCode'];
		?>
				<tr>
					<td><?=$user_id?></td>
					<td><?=$firstName?></td>
					<td><?=$lastName?></td>
					<td><?=$username?></td>
					<td><?=$password?></td>
					<td><?=$email?></td>
					<td><?=$address?></td>
					<td><?=$city?></td>
					<td><?=$state?></td>
					<td><?=$zipCode?></td>
					<td><a href='edit_user.php?edit_user=<?=$user_id?>'>Edit</td>
					<td><a href='index.php?delete=<?=$user_id?>'>Delete</td>
				</tr>
		<?php
			}
		?>
	</tbody>
</table>

<?php
/*If delete appears in the address bar,
  then delete that user from the
  database*/
if(isset($_GET['delete'])){
	$deleteUserID = $_GET['delete'];
	$query = "DELETE FROM users WHERE userID = {$deleteUserID}";
	$deleteUserQuery = mysqli_query($connection, $query);
}


?>