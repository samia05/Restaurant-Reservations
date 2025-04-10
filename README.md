# Restaurant-Reservations
A fully functional restaurant reservation system that manages a complex waiting list using an ordered singly-linked list, enhanced with an “auto-save” feature. 

The idea for this program began because I wanted a way to visualize and understand all the various data organization/accessibility skills that we learned in my Advanced Programming class in my Freshman Year. Me being a foodie, I knew this was just the lab project for me! 

# Menu + Function: 
The program allows users to interact with a menu where they may choose to view, search, and remove reservations. They may add/search for reservation details including a name, group size, and meal-specific details while ensuring duplicate names are not entered. 

# Auto-Save + File I/O: 
This feature periodically writes the list to a binary file every 15 seconds, locking the list during the process to prevent multiple branches of the existing file being saved. The system also integrates file I/O to persist reservations between runs – making it extremely functional.

# Self-Adjustion: 
The list remains sorted by group size, adjusting itself with every new entry. pointers, linked-list traversal, data management.

# Recursion: 
I also added some fun functions to practice recursion, such as displaying the reservations in reverse order, or “clearing” and quitting the program.
