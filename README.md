# 42-cub3d

In this project, we created a game inspired by [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D).</br>
The program reads from a map and displays a maze with a dynamic view using an [algorithm](https://lodev.org/cgtutor/raycasting.html) by Lode Vandevenne.</br>
For bonus, we implemented an animated torch with lighting, mouse control, wall collisions, minimap and doors.

![Game demo](https://github.com/joekeroo/42-cub3d/assets/58316168/56b4a96f-60d8-4c7e-8711-726ef24879d3)

## About

## Installation & Usage

- GNU make (v3.81)
- GCC (v4.2.1)
- [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)

### Building the program

1. Download/Clone this repository

```bash
git clone https://github.com/joekeroo/42-so_long.git so_long
```

2. `cd` into the root directory and run `make`

```bash
cd so_long && make
```

### Compilation

- `make` - compiles the program into `so_long`
- `make clean` - removes all `.o` files
- `make fclean` - clean and removes `so_long`
- `make re` - fclean and recompiles

### Run the Program

```bash
./so_long maps/bonus4.ber
```

## Contributors

- [`joekeroo`](https://github.com/joekeroo)
- [`hooyunzhe`](https://github.com/hooyunzhe)
