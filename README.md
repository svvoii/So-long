# So-long

MLX:
https://github.com/42Paris/minilibx-linux

After cloning this repo make sure to add mlx library into respective folder: 
```
git clone https://github.com/42Paris/minilibx-linux.git so_long/includes/mlx/
```
and compile it (see the mlx source page)
"Compile MinilibX
run ./configure or make both will make a few tests, create Makefile.gen and then automatically run make on this generated Makefile.gen . libmlx.a and libmlx_$(HOSTTYPE).a are created. test/mlx-test binary is also created."

If any errors (x11, -lbsd etc) appear on the Linux machine outside 42 the following might help:
```
sudo apt install libx11-dev
sudo apt install libssl-dev
sudo apt install libbsd-dev
```
This will show if X11 is installed. 
```
apt search Xlib.h
```

Another error, from the local Makefile might apper (-lmlx not found). For solution check the absolute path to mlx library in the Makefile:
This line links the mlx library which is located in the project folder on the school machine.
```
Lmlx = -L/mnt/nfs/homes/sbocanci/Documents/42cursus/So-long/so_long/includes/mlx/ -lmlx -lXext -lX11

(@gcc -g $(flags) $(src) $(libft) $(Lmlx) -o $(NAME))
```

