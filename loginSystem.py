import tkinter
import customtkinter
from PIL import ImageTk,Image

customtkinter.set_appearance_mode("System")
customtkinter.set_default_color_theme("dark-blue")

# Destroys login window and creates home window
def button_login(app):

    # POSSIBLE SPACE FOR AUTHENTICATION
        #
        #
        #

    app.destroy()            # Removes login window and creates new window
    create_home_interface()


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

# Handles the creation of the login window
def create_login_interface():

    # Initializes login window
    app = customtkinter.CTk()

    # Sets login window size
    app.geometry("600x440")
    app.resizable(False, False) # Height, Width
    app.title('Login Screen')
    
    # Loads and sets background image for the login window
    loadBackgroundImage = Image.open("./assets/backImage.png")
    loadBackgroundImage = loadBackgroundImage.resize((600, 440))

    backImage = ImageTk.PhotoImage(loadBackgroundImage)
    backLabel=customtkinter.CTkLabel(master=app,image=backImage)
    backLabel.pack()

    # Sets the frame for login buttons and labels
    frame=customtkinter.CTkFrame(master=backLabel, width=320, height=360, corner_radius=5)
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

    # Sets the login button
    loginButton = customtkinter.CTkButton(master=frame, width=220, text="Login", command=lambda: button_login(app), corner_radius=6)
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