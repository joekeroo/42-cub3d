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
git clone https://github.com/joekeroo/42-cub3d.git cub3d
```

2. `cd` into the root directory and run `make`

```bash
cd cub3d && make
```

### Compilation

- `make` - compiles the program into `cub3d`
- `make clean` - removes all `.o` files
- `make fclean` - clean and removes `cub3d`
- `make re` - fclean and recompiles

### Run the Program

```bash
./cub3d test_maps/small.cub
```

## Contributors

- [`joekeroo`](https://github.com/joekeroo)
- [`hooyunzhe`](https://github.com/hooyunzhe)
