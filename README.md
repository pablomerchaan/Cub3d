# cub3D — Raycasting 3D Engine

*Project developed as part of the 42 curriculum by **almarti3** and **paperez-**.*

---

## Description

**cub3D** is a 3D graphical engine written in C, inspired by the classic Wolfenstein 3D. It implements the **Raycasting** algorithm to render a dynamic first-person perspective inside a maze in real time.

Key features:

- Real-time environment rendering using the **DDA (Digital Differential Analyzer)** algorithm
- **Texture mapping** for walls based on cardinal orientation (N/S/E/W)
- Configurable floor and ceiling colors
- Smooth window management and event handling via the **MLX42** library

---


## Build

Compile the mandatory version:

```bash
make
```

---


## Usage

Run the executable followed by a valid `.cub` scene description file:

```bash
./cub3D maps/subject.cub
```

## Norminette
Run this command to avoid MLX42 errors:

```bash
find . \( -name "*.c" -o -name "*.h" \) -not -path "./minilibx/*" -exec norminette {} +
```

### Controls

| Action | Input |
|--------|-------|
| Move | `W` `A` `S` `D` |
| Rotate camera | `←` `→` Arrow keys |
| Rotate camera (Bonus) | Mouse |
| Exit | `ESC` or window close button |

--


## Scene File Format (`.cub`)

The scene description file defines textures, colors, and the map layout.

| Identifier | Description | Format |
|------------|-------------|--------|
| `NO` | North wall texture | `./path/to/file.png` |
| `SO` | South wall texture | `./path/to/file.png` |
| `WE` | West wall texture | `./path/to/file.png` |
| `EA` | East wall texture | `./path/to/file.png` |
| `F` | Floor color | `R,G,B` — values in `[0–255]` |
| `C` | Ceiling color | `R,G,B` — values in `[0–255]` |

> **Important:** The map must be enclosed by walls on all sides. Any gap or misconfiguration will trigger `Error\n` and terminate the program.

---


## Resources

### References

- [Lode's Raycasting Guide](https://lodev.org/cgtutor/raycasting.html) — Primary mathematical reference for the DDA algorithm
- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42) — Technical documentation for the graphics library


### Technical Consultation (AI)

As per the subject requirements, an AI assistant was used as a supportive tool during development. Its involvement was limited to:

- **Logic Validation:** Reviewing the mathematical consistency of the DDA implementation and collision detection
- **Refactoring Assistance:** Identifying opportunities to modularize functions in line with 42 Norminette requirements
- **Edge Case Analysis:** Assisting in the design of robust error handling for the `.cub` parser to ensure `Error\n` is triggered under varied misconfigurations
