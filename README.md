# 42-cub3d

In this project, we created a game inspired by [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D).</br>
The program reads from a map and displays a maze with a dynamic view using an [algorithm](https://lodev.org/cgtutor/raycasting.html) by Lode Vandevenne.</br>
For bonus, we implemented an animated torch with lighting, mouse control, wall collisions, minimap and doors.

![Game demo](https://github.com/joekeroo/42-cub3d/assets/58316168/56b4a96f-60d8-4c7e-8711-726ef24879d3)

## About

- You must use [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html). Either the version available on the school machines, or installing it using its sources.
- The program will take a map as an argument.
- Map file extension must end with `.cub`.
- Display different wall textures that vary depending on which side the wall is facing.
- Must be able to set floor and ceiling colors to 2 different colors.
- `W`, `A`, `S`, `D` keys must control the player movement.
- `ESC` key will exit the game.
- The use of images of the [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html) is mandatory.

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

### Map Requirements

- The map can be composed of only these 6 characters:

| Characters |                 Description                 |
| :--------: | :-----------------------------------------: |
|    `0`     |               an empty space                |
|    `1`     |                   a wall                    |
|    `N`     | the player’s starting position facing North |
|    `S`     | the player’s starting position facing South |
|    `E`     | the player’s starting position facing East  |
|    `W`     | the player’s starting position facing West  |

- The map must be closed/surrounded by walls. If it’s not, the program must return `error`.
- Except for the map content, each type of element can be separated by one or more empty line(s).
- Except for the map content which always has to be the last, each type of element can be set in any order in the file
- Except for the map, each type of information from an element can be separate by one or more space(s).
- Any kind of maps will be accepted as long as it respects the above rules.
- Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict order such as:

|     Type      | Identifier |          Map Syntax          |
| :-----------: | :--------: | :--------------------------: |
| North Texture |    `NO`    | `NO ./path_to_north_texture` |
| South Texture |    `SO`    | `SO ./path_to_south_texture` |
| West Texture  |    `WE`    | `WE ./path_to_west_texture`  |
| East Texture  |    `EA`    | `EA ./path_to_east_texture`  |
|  Floor Color  |    `F`     |        `F 220,100,0`         |
| Ceiling Color |    `C`     |         `C 225,30,0`         |

- Example of a valid map:

## Contributors

- [`joekeroo`](https://github.com/joekeroo)
- [`hooyunzhe`](https://github.com/hooyunzhe)
