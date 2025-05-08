# ft_donut

## Overview
A mesmerizing ASCII art donut (torus) animation in the terminal, implemented according to 42 School norms.

![ft_donut animation example](https://i.gifer.com/8Lsl.gif)

## Description
ft_donut renders a rotating 3D torus (donut) using only ASCII characters in the terminal. It implements:
- 3D projection mathematics
- Z-buffering for hidden surface removal
- ASCII character illumination based on surface orientation
- Smooth rotation animation

This project demonstrates fundamental computer graphics concepts while complying with the 42 norm coding standard.

## Features
- Rotating donut in ASCII art
- Depth perception through intelligent character selection
- Proper hidden surface removal
- Clean, modular code structure
- Highly commented for educational purposes

## Installation

```bash
git clone https://github.com/yourusername/ft_donut.git
cd ft_donut
make
```

## Usage
```bash
./ft_donut
```
Press Ctrl+C to exit the animation.

## Project Structure
- `includes/` - Header files directory
  - `ft_donut.h` - Main header file with structures and function declarations
- `sources/` - Source code files
  - `ft_donut_init.c` - Initialization functions
  - `ft_donut_math.c` - Mathematical calculations for 3D projection
  - `ft_donut_render.c` - Rendering functions
  - `ft_donut_utils.c` - Utility functions
- `main.c` - Entry point and animation loop
- `obj/` - Object files directory (generated during compilation)
- `deps/` - Dependency files directory (generated during compilation)

## Build System
The project uses a Makefile with the following features:
- Automatic dependency generation with `.d` files
- Organized build artifacts in dedicated directories
- Verbose feedback during compilation processes
- Standard rules: `all`, `clean`, `fclean`, `re`

## How It Works
The animation uses parametric equations to represent a torus in 3D space. For each frame:
1. The program calculates the 3D coordinates of each point on the torus surface
2. It applies rotation transformations based on the current angles
3. It projects these 3D coordinates onto a 2D plane (your terminal)
4. It calculates lighting for each point based on its orientation
5. It renders the points using ASCII characters, with different characters representing different lighting levels
6. It implements a z-buffer to ensure only the closest point at each screen position is displayed

## License
This project is licensed under the MIT License - see the LICENSE file for details.
