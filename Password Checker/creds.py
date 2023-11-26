# File that takes input from the user for a username and password
# Creates a file for the passwords and writes "Username" and "Password" in the file but not the passwords inputed by the user. 
import re
import sys

class Credentials():
    def __init__(self):
        self.__username = ''
        self.__password = ''
        
    def username(self):
        return self.__username
    def password(self):
        return self.password
    
        
    def create_file(self):
        # cred_file =  'PasswordFile.ini'
        cred_file = 'PasswordFile.txt'
        
        with open(cred_file, 'w') as file_in:
            file_in.write("#Password file: \nUsername={}\nPassword={}\n"
                          .format(self.__username, self.__password))
    
def main():
    cred = Credentials()
    
    cred.__username = input("Enter Username: ")
    cred.__password = input("Enter Password: ")
    
    cred.create_file()
    
if __name__ == "__main__":
    main()