def findPassword(inputedPass, passFile):
    # Method to find a password, goes through the whole file and checks if the password is found in a specific line. Inefficient for large files.
    # passFile = 'PasswordFile.txt'
    found = False
    for line in passFile:
        # print(line)
        if inputedPass in line:
            found = True
            break
            # return True
    return found

def checkHoneyWords(password): 
    honeyWords = ["electricity", "phonograph", "camera"]
    if password in honeyWords:
        # print("Access denied")
        return True
    
def main():
    passFile = open('PasswordFile.txt')
    password = input("Enter Password: ")
    
    honeyWord = checkHoneyWords(password)
    found = False 
    
    if not honeyWord:
        found = findPassword(password, passFile)
    
    if not found:
        print("Access denied")
    if found:
        print("Access granted")
    
if __name__ == "__main__":
    main()