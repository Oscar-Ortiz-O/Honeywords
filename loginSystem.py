import tkinter
import customtkinter
from PIL import ImageTk,Image
import clientSocket

customtkinter.set_appearance_mode("System")
customtkinter.set_default_color_theme("dark-blue")

# Destroys login window and creates home window
def button_login(app, username, password):

    # POSSIBLE SPACE FOR AUTHENTICATION
        #
        #
        #
    response = clientSocket.client_socket("login|" + username + "|" + password)

    if (response == "true"):
        app.destroy()            # Removes window and creates new window
        create_home_interface()


# Destroys login window and creates registration window
def button_signUp(app):
    app.destroy()            # Removes window and creates new window
    create_register_interface()


# Destroys login window and creates login window
def button_signIn(app, username, password):
    clientSocket.client_socket("register|" + username + "|" + password)
    app.destroy()            # Removes window and creates new window
    create_login_interface()


# Handles the creation of the home window
def create_home_interface():

    # Initializes home window
    homeWindow = customtkinter.CTk()

    # Sets home window size
    homeWindow.geometry("1280x720")
    homeWindow.title('Home Screen')

    # Creating labels
    homeLabel=customtkinter.CTkLabel(master=homeWindow, text="Successful Login",font=('Century Gothic',65))
    homeLabel.place(relx=0.5, rely=0.5,  anchor=tkinter.CENTER)

    # Home window event looper
    homeWindow.mainloop()



# Handles the creation of the registration window
def create_register_interface():

    # Initializes registration window
    registerWindow = customtkinter.CTk()

    # Sets registration window size
    registerWindow.geometry("600x500")
    registerWindow.resizable(False, False) # Height, Width
    registerWindow.title('Registration Screen')

    # Loads and sets background image for the login window
    loadBackgroundImage = Image.open("./assets/backImage2.png")
    loadBackgroundImage = loadBackgroundImage.resize((600, 500))

    backImage = ImageTk.PhotoImage(loadBackgroundImage)
    backLabel=customtkinter.CTkLabel(master=registerWindow,image=backImage)
    backLabel.pack()

    # Sets the frame for login buttons and labels
    frame=customtkinter.CTkFrame(master=backLabel, width=320, height=400, corner_radius=5)
    frame.place(relx=0.5, rely=0.5, anchor=tkinter.CENTER)

    # Sets labels and textboxes for username and password
    loginLabel = customtkinter.CTkLabel(master=frame, text="Create a New Account",font=('Montserrat',23))
    loginLabel.place(x=50, y=45)

    usernameEntry = customtkinter.CTkEntry(master=frame, width=220, placeholder_text='Username')
    usernameEntry.place(x=50, y=110)

    passwordEntry = customtkinter.CTkEntry(master=frame, width=220, placeholder_text='Password', show="*")
    passwordEntry.place(x=50, y=165)

    passwordEntry = customtkinter.CTkEntry(master=frame, width=220, placeholder_text='Confirm your Password', show="*")
    passwordEntry.place(x=50, y=220)

    # Sets the Create button
    loginButton = customtkinter.CTkButton(master=frame, width=100, text="Create", command=lambda: button_signIn(registerWindow, usernameEntry.get(), passwordEntry.get()), corner_radius=6)
    loginButton.place(x=110, y=280)

    signUpLabel = customtkinter.CTkButton(master=frame, command=lambda: button_signIn(registerWindow), border_width=0, fg_color="transparent", text="Already have an account? Login Here!",font=('Century Gothic', 12, 'bold'))
    signUpLabel.place(x=50, y=340)

    registerWindow.mainloop()


# Handles the creation of the login window
def create_login_interface():

    # Initializes login window
    app = customtkinter.CTk()

    # Sets login window size
    app.geometry("600x500")
    app.resizable(False, False) # Height, Width
    app.title('Login Screen')
    
    # Loads and sets background image for the login window
    loadBackgroundImage = Image.open("./assets/backImage2.png")
    loadBackgroundImage = loadBackgroundImage.resize((600, 500))

    backImage = ImageTk.PhotoImage(loadBackgroundImage)
    backLabel=customtkinter.CTkLabel(master=app,image=backImage)
    backLabel.pack()

    # Sets the frame for login buttons and labels
    frame=customtkinter.CTkFrame(master=backLabel, width=320, height=400, corner_radius=5)
    frame.place(relx=0.5, rely=0.5, anchor=tkinter.CENTER)

    # Sets labels and textboxes for username and password
    loginLabel = customtkinter.CTkLabel(master=frame, text="Log into your Account",font=('Montserrat',23))
    loginLabel.place(x=50, y=45)

    usernameEntry = customtkinter.CTkEntry(master=frame, width=220, placeholder_text='Username')
    usernameEntry.place(x=50, y=110)

    passwordEntry = customtkinter.CTkEntry(master=frame, width=220, placeholder_text='Password', show="*")
    passwordEntry.place(x=50, y=165)

    forgetPasswordLabel = customtkinter.CTkLabel(master=frame, text="Forget password?",font=('Century Gothic',12))
    forgetPasswordLabel.place(x=155,y=195)

    signUpLabel = customtkinter.CTkButton(master=frame, command=lambda: button_signUp(app), fg_color="transparent", border_width=0, text="Don't have an account? Register Now!",font=('Century Gothic', 12, 'bold'))
    signUpLabel.place(x=50, y=340)

    # Sets the login button
    loginButton = customtkinter.CTkButton(master=frame, width=220, text="Login", command=lambda: button_login(app, usernameEntry.get(), passwordEntry.get()), corner_radius=6)
    loginButton.place(x=50, y=240)

    # Sets the Google and Facebook buttons
    googleImg = customtkinter.CTkImage(Image.open("./assets/google.webp").resize((20,20)))
    facebookImg = customtkinter.CTkImage(Image.open("./assets/facebook.png").resize((20,20)))

    googleButton = customtkinter.CTkButton(master=frame, image=googleImg, text="Google", width=100, height=20, compound="left", fg_color='white', text_color='black', hover_color='#AFAFAF')
    googleButton.place(x=50, y=290)

    facebookButton = customtkinter.CTkButton(master=frame, image=facebookImg, text="Facebook", width=100, height=20, compound="left", fg_color='white', text_color='black', hover_color='#AFAFAF')
    facebookButton.place(x=170, y=290)

    # Login window event looper
    app.mainloop()

create_login_interface()