# ArcAim
An arcade aim based game, made in **SFML** with C++.

Try to reach the highest score, but remember, every miss is a penalty (-10 HP), so be careful ;)

# Functionality
Press 
+ **[ESC]** for menu (it will restart the game too).
+ **[R]** for a fast restart during the gameplay.
+ **[F5]** to activate/deactivate holes when missing the target.

## Options
Choose between:
+ 3 different difficulties
+ 3 crosshair styles

## Difficulty

**Easy** (*Default*)
+ Target spawn time: 1 second
+ Health: 110
+ Countdown: 20 seconds

**Medium**
+ Target spawn time: 0.65 seconds
+ Health: 80
+ Countdown: 20 seconds

**Hard** (*if you want a serious challenge*)
+ Target spawn time: 0.5 seconds
+ Health: 70
+ Countdown: 20 seconds

## Modes
Choose between 3 modes!
+ Reflex: Test your reflexes.
+ Precision: [BOOM!!! Headshot!](https://www.youtube.com/watch?v=5_Xdi4T8mgI), shoot these small targets faster than a sniper.
+ Falling: Be ready, they are falling from the sky.

## Framerate

Normally the game is capped at 240 fps, if you want something else: 

Press 
+ **[ F1 ]** for vsync (I don't know if it actually works)
+ **[ F2 ]** for 60 fps cap
+ **[ F3 ]** for 144 fps cap.

To avoid weird input lag just cap the fps accordingly to your monitor refresh rate.

# Build and compile
**IMPORTANT!** You have 2 options:

1) Build and compile with Visual studio community (MSVC v143) by opening the .sln file

    (if you have older versions just change the Platform toolset in project properties)

2) Build by opening the console in the main folder, write mingw32-make  and then open the .exe in the Exec folder.

    (MinGW 64 bit compiler required: https://www.msys2.org/ )

# Socials
Enjoy and let me know (with a DM on Twitter: @graffioh or Discord: Graffioh#2823) anything useful to get better coding wise :)


## Early prototype gameplay

![gameplayGIF](https://i.imgur.com/yf4gMYa.gif)

