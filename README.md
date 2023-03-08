# grand-theft-crypt
Game developed in Unreal engine 5 mostly for learning purposes. Project showcases base structure implementation.

At this stage project is too big to host it entirely on github. Only the source C++ code has been uploaded here. I'm currently working on a solution that will allow me to host entire project in version control. Some functionalities use Unreal blueprints. If you are interested in these, you can use the link below to download entire project at this moment.

https://share.internxt.com/d/sh/folder/e4b14ad4291a53a95357/8b8e09d7f225c2efe7e763568d3fb8dda53d554fd7016be1054585f1b1b4662c

It's a first-person game that focuses on solving riddles to progress through the levels. At this stage it's mostly a template with basic features to create more sophisticated levels. The game consits of a menu and one playable level. Persistent level is also implemented with level streaming. 

When game starts player is presented with the main menu. It's currently possible to change graphics settings, start new game and quit.

![Alt text](/screenshots/1_menu.jpg?raw=true "Menu")
![Alt text](/screenshots/1_menu_graphic_settings.jpg?raw=true "Menu")

Implemented level serves as a tutorial and introduction to the game mechanics. The Player needs to solve few simple riddles, and popup messages will show instructions how to make basics interactions.

The player is able to grab keys and add them to their inventory and later use them to open locked doors. It's also possible to grab some objects and move them to other locations. When player looks at the interactable object it begins to highlight. If no interaction is made after certain amount of time, a text popup is displayed with instruction.

![Alt text](/screenshots/2_item_interaction.jpg?raw=true "Key to grab")
![Alt text](/screenshots/3_key_grab.jpg?raw=true "Key grabbed")

![Alt text](/screenshots/2_item_interaction_grab.jpg?raw=true "Item to grab")
![Alt text](/screenshots/3_item_grab.jpg?raw=true "Item to grab")

Two types of widget texts have been implemented which are triggered by some actions/events.

![Alt text](/screenshots/4_Main_text_event.jpg?raw=true "Primary text")
![Alt text](/screenshots/4_Secondary_text_event.jpg?raw=true "Primary text")

Player has option to stop a game by pressing M (by default it will be escape key - it was changed for development as it interferes with escape key behavior in editor). 

![Alt text](/screenshots/6_InGame_optionsscreen.jpg?raw=true "Primary text")
![Alt text](/screenshots/6_InGame_pausescreen.jpg?raw=true "Primary text")

Two generic splash screens were created which are shown when player dies or finishes the level. These allow to go back to the main menu, try again or quit the game.

![Alt text](/screenshots/5_splash_screen_death.jpg?raw=true "Primary text")
![Alt text](/screenshots/5_splash_screen_win.jpg?raw=true "Primary text")


Game utilizes newest unreal engine features like lumen/nanites with every light source set to movable. Level is built with usage of free modular Medieval Dungeon pack available in epic store.

![Alt text](/screenshots/7_lumen.jpg?raw=true "Primary text")
![Alt text](/screenshots/7_lumen_2.jpg?raw=true "Primary text")
![Alt text](/screenshots/7_lumen_3.jpg?raw=true "Primary text")

Introduction level walkthrough is available on youtube. Click on the thumbanil below.

[![Grand Theft crypt introduction](/screenshots/8_YT_thumbnail.jpg?raw=true)](https://youtu.be/8IdpVmOaR8g "Grand Theft crypt introduction")