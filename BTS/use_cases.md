## Posting for a property (done by Kirk Parillon)

### Actor (User)
A landlord

### Pre-conditions
A landlord with a verified account is logged into the system. 

### Main Flow
1.	Landlord clicks on add a property button.
2.	The system redirects to a new page that prompts the landlord for information.
3.	The landlord enters valid information into the appropriate GUI elements on the page.
4.	The landlord clicks preview of the rental property page and the system verifies that all mandatory and proper data fields are valid.
5.	System redirects to preview page of the property.
6.	Landlord post rental property on system.


### Alternate Flows
- Duplicate addresses cannot be assigned to more than one landlord when an add is posted. If an add already contains a specific address: 
a)	On the page to enter the information, the location field will reject that location because it has been taken/used.

-	Landlord can click cancel at anytime if he/she changes their mind about the rental property. Will redirect back to home page.
-	If landlord is not satisfied with the information on the preview page, he/she can press the back button to edit the information about the rental property.


### Postconditions
After a landlord clicks post a property onto the website, the system updates the database with the necessary information entered by the landlord. An email gets send to the landlord as confirmation that the ad has been posted and the ad can now be found in search results on the system.



## Searching a new property (done by Noor Ashraf)

### Actor (User)
Students looking for a place to rent

### Pre-conditions
Student has registered for an account, and is logged in to the system.

### Main Flow
1. The student clicks on the search bar and enters keywords on which area (input street name or city, etc.) they would like to find a rental.
2. The system loads a list of available rentals that are in the area of the searched input.
3. The student scrolls through the loaded rentals and clicks on whichever they like.
4. The system loads the full information given for that rental.

### Alternate Flows
- If the student wants to add additional filters (such as view lowest to highest price) for the rentals they want to be shown:
  1. After step 2, the student can click on the sort tab and pick “lowest to highest price” or vice versa.


### Postconditions
After a student has viewed any rentals, these will be available in the user’s viewed history.

---

## Signing up (done by Soodeh Vanaki)

### Actor (User)
Students, landlords, and whoever wants to use the website could be the users.

### Pre-conditions
The user is on the home page or any page on.

### Main Flow
1. User clicks on Sign up button in the header section or below the login box.
2. The system loads the signup form.
3. The user enters the required information to the related fields of the form.
4. The system validates each field of the form. (Step 3 and 4 are happening at the same time.)
5. The user clicks on the submit button.
6. The page refreshed and a confirmation message at the top of the login page is displayed. (login could be a possible use case)


### Alternate Flows
- If the user does not enter the required fields:
	1. After step 4, the error message "This is a required field. Please fill it!" is displayed in red under each empty required field on the page. The system will allow the user to fill the required field, effectively sending him/her back to step 3. 
- If the user enters invalid information:
	1. After step 4, the validation error message related to the invalid field is displayed in red under the invalid field on the page. The system will allow the user to correct the invalid field, effectively sending him/her back to step 3.  
- If the user enters the existing username:
	1. After step 5, the error message "The user already exists." is displayed on the page. The system will allow the user to fill the form with new information, effectively sending him/her back to step 3.    
- If the user enters the existing email address:
	1. After step 5, the error message "The email address already exist." is displayed on the page. The system will allow the user to fill the email address field with a new address, effectively sending him/her back to step 3. 
- If the user clicks on the submit button without filling the form:
	1. After step 5, the error message "Please fill the required fields!" is displayed on the page. The system will allow the user to fill the form, effectively sending him/her back to step 3.

### Postconditions
After a user has successfully submitted the signing-up form, the database gets updated with the user's information. Moreover, the user receives an email with the confirmation message and a link to activate their account. (activating an account could be another possible use case)

---

## A user favoriting a property (done by Hanlin Li)

### Actor (User)
Students who need to rent an apartment

### Pre-conditions
Students need to log in to our system and ensure that they are connected to the Internet to receive the latest information.

### Main Flow

1. The student clicks on the "My favorite" on top near user account for getting in the user    favorite page.
2. The system loads a list of a user favoriting a property.
3. The students click on any property in the lists which he already adds in.
4. The system will load the detailed information about the property in which the student clicked.


### Alternate Flows
- If the student didn't add any property in "My favorite".
  1. After step 3,the system will load a message said"your are not add favorite property now, please go check the down below the link to have some idea" and show two links. one is the main page, another one is the search page. 


### Postconditions
The system will send student email for any update information about the property which is a student already add in their "My favorite".The system will update the user new favorite property list to database.

---

