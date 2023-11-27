
# Method to find a password, goes through the whole file and checks if the password is found in a specific line. 
# Inefficient for large files.
def findPassword(inputedUser, inputedPass, passFileName):
    
    passFile = open(passFileName)

    for line in passFile:
        
        lineData = line.split(",")

        # Skip to next line if usernames do not match
        username = lineData[0]
        if username != inputedUser: 
            continue

        # Check if password is among the sweetwords.
        # If it is, get the index in which it was found.
        sweetwords = lineData[1:]

        for index in range(len(sweetwords)):
            if sweetwords[index] == inputedPass:
                return index

    return -1 # If username and/or password was not found
    
def main():
    passFile = open('PasswordFile.txt')
    username = input("Enter Username: ")
    password = input("Enter Password: ")
    
    passwordIndex = findPassword(username, password, 'PasswordFile.txt')
    print(passwordIndex)
    
    if passwordIndex == -1:
        print("Access denied")

    else:
        print("Access granted")
    
if __name__ == "__main__":
    main()