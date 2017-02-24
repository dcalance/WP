
### Laboratory work #1: 
 * Create a Windows application  
	Windows application is intialized with functions WinMain and WinProc.
	WinMain initializes the window and loops the messages as long as the program is running. 
	WinProc handles all the messages passed by interactions of user with window.
 * In the middle of the window should be present the following text: "Done with Pride and Prejudice by student name". Replace student name with your name.  
	Text was created using DrawText function. We draw the text by handling WM_PAINT that window passes message when window is created.
 * On windows resize, text should reflow and be in window's middle (vertically and horizontally)  
	The text is always centered because when we create or resize the window we pass the messages WM_PAINT that paints the text centered in the client zone, when we resize the window the client becomes bigger/smaller and it calculates new coordinates.
 * Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family/size)  
	We add buttons in WM_CREATE handle since it is accessed by program when we create the window. We create a standard button with style BS_DEFPUSHBUTTON that is one of the standard styles, and the second with BS_OWNERDRAW witch is a custom button.
	The custom button is drawn in WM_DRAWITEM handle, where we change it's color to green and black and we also add 2 states that change (button pressed/ button not pressed).
 * Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family/size)  
	Added 2 edit controls. First one is standard with default value a string from a variable, the second one is initialized the same hovewer after that we add a custom font and we edit its appearance in WM_CTLCOLOREDIT where we handle it by its id.  
 * Make elements to interact or change other elements (2 different interactions)  _(ex. on button click, change text element color or position)_  
	We create handle for our buttons that we created earlier. The button with name "Change window name" is handled in WM_COMMAND and by his id we program it to change the window name.
	The second button with name "Change Message" is also handle in WM_COMMAND by its id, and it's function is to change a variable that is printed in our previous exercise in the center of the screen.
 * Change behavior of different window actions (at least 3). For ex.: on clicking close button, move window to a random location on display working space  
	We changed the behavior of all 3 buttons on top of the window.
	Minimize button now has custom handle in WM_SYSCOMMAND, and instead of standard minimizing now it moves and resizes the window to a random location/size from 0 to 500.
	Maximize button is also handled in WM_SYSCOMMAND and now when we press it it promps a messageBox that asks us if we want to close the program, by pressing ok the program will close and window will be destroyed.
	Close button now insead of closing the window generates asynchonous sound of "Device connected" from windows. To make this possible we also linked the library winmm.lib to our project.
