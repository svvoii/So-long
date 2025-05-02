# So-long

## Overview

So_long is a simple 2D graphical game developed in C using the MiniLibX graphics library. This project is part of the 42 School curriculum, designed to reinforce understanding of low-level graphics programming, file parsing, event handling, and rendering in a minimal windowing environment.

The goal of the game is to guide the player character through a tile-based map, collecting all items and reaching the exit while avoiding obstacles.

## Features

🎮 Simple 2D Game Mechanics: Collect all items (C), reach the exit (E), and avoid walls (1) (See `.ber` files in `/maps/` dir)   
🖼️ Real-Time Rendering: Uses MiniLibX to display graphics in a window   
🎹 Keyboard Controls: Move the player using W/A/S/D keys   
📄 Map Parsing: Loads and validates maps from .ber files   
🧱 Collision Detection: Ensures player can only move on valid tiles   
🧰 Error Handling: Robust checks for invalid maps, file errors, and missing resources   


## Tech Stack

| Category | Technology |
| -------- | ---------- |
| Language | C |
| Graphics | MiniLibX (X11-based) |
| OS | Linux, MacOS |
| Build Tool | Makefile |
| External Libraries | libX11, libXext, libbsd |

---

## Lessons Learned

•	Working with low-level graphics using the X11-based MiniLibX library   
•	Real-time rendering, image buffering, and event handling   
•	File I/O and custom map parsing   
•	Managing complex state using structs and modular C code   
•	Debugging runtime issues and linking external libraries   

---

## File Structure

```
so_long/
│
├── includes/           # Header files and MLX library ..(includes compiled libmlx.a and mlx.h files)
├── src/                # Game logic and rendering
├── maps/               # Sample .ber map files
├── assets/             # Game textures and sprites (if applicable)
├── Makefile            # Build instructions
└── README.md           # Documentation
```

*NOTE: The `so_long/includes/` folder contains the compiled MiniLibX library file `libmlx.a` and its header file `mlx.h`. No need to have the source repo here. The library is linked during compilation using the Makefile.*  
If source repo is needed you can use this :  
`git clone https://github.com/42Paris/minilibx-linux.git so_long/includes/mlx/`  

---

## Try it out!

1. Clone the repo: 

```bash
git clone https://github.com/svvoii/So-long.git
cd so_long
```

2. Make sure you have the compiled MiniLibX library file `libmlx.a` in the `so_long/includes/` directory and there is a correct path to it in the Makefile (line 32 and 36).

for MACOS:

```bash
..
flags = -Wall -Wextra -Werror -I/PATH/TO/THIS/REPOSITORY/So-long/so_long/includes -I/opt/X11/include # MACOS (change path to your `libmlx.a` and X11 !!!) X11 must be installed

Lmlx = -L/PATH/TO/THIS/REPO/So-long/so_long/includes -L/opt/X11/lib -lmlx -lXext -lX11 -lm
# make sure to have the correct path to X11 library `-L/opt/X11/lib` ..)
..
```

for LINUX:

```bash
Lmlx = -L/usr/local/lib -lmlx -L/usr/X11/lib -lXext -lX11 -lm # LINUX
# or: 
Lmlx = -L/mnt/nfs/homes/sbocanci/Documents/42cursus/So-long/so_long/includes -lmlx -lXext -lX11 # LINUX (42 dump)
```

*NOTE: The `X11` library must be installed on the system. Go to [XQuartz](https://www.xquartz.org) to download.*  

3. Compile the project:

Once you have the correct path to the `libmlx.a` library and `X11`, you can compile the project from `/So-long/so_long/` directory : 

```bash
make
```

to compile the bonus version use:

```bash
make bonus
```

4. Run the game:

Example of running the game with a map file from the `maps/` directory : 

```bash
./so_long_bonus maps/map1.ber
```

### Map Format (.ber)

•	1 – Wall   
•	0 – Empty space   
•	P – Player start position   
•	C – Collectible   
•	E – Exit   

All maps must be rectangular, closed (surrounded by walls), and contain exactly one player and one exit.


5. Controls:

| Key | Action |
| --- | ------ |
| UP   | Move Up |
| LEFT   | Move Left |
| DOWN   | Move Down |
| RIGHT   | Move Right |
| ESC | Exit Game |

---


## Troubleshooting

- Issue: `-lmlx` not found

Make sure the MLX library path is correct in your Makefile:

```bash
Lmlx = -L$(PWD)/includes -lmlx -lXext -lX11 -lbsd
```

- Check if X11 is installed on your system :

```bash
apt search Xlib.h
```

- If any errors (x11, -lbsd etc) appear on the Linux machine outside 42 the following might help:
```
sudo apt install libx11-dev
sudo apt install libssl-dev
sudo apt install libbsd-dev
```

---


## Author

[My GitHub](https://github.com/svvoii)  
[My LinkedIn](https://www.linkedin.com/in/bocancia/)  
[My Portfolio](https://sbocanci.me/)  

---