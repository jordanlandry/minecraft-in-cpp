# Minecraft in C++

## Overview

This project is my own take on the popular game Minecraft.

## Table of contents

- [Build Process](#build-process)
- [Controls](#controls)
- [Implemented Features](#implemented-features)
- [Upcoming Features](#upcoming-features)
- [How it works](#how-it-works)

## Build process

Watch me design, create and debug this project on [YouTube](https://www.youtube.com/channel/UCO8fo_fxQgSGLkdEmyVJcFA) (Video is not currently up, will be updated when the video becomes available)

TODO Write description for each step in the build process

Textures on screen
![Textured grass square on an OpenGL window](/readme_images/build_process/texture_on_screen.png)

3 Dimensional blocks
![Dirt and grass blocks rendered in 3d](/readme_images/build_process/3d_texture.png)

Chunk Rendering
![16x16x16 flat Minecraft world with grass and dirt](/readme_images/build_process/chunk_rendering.png)

Terrain Generation
![16x16x16 Minecraft world with small hills](/readme_images/build_process/terrain_generation.png)

## Controls

| Button     | Action           |
| ---------- | ---------------- |
| Space      | Fly              |
| Left Ctrl  | Fly down         |
| W, A, S, D | Move             |
| Enter      | Toggle Wireframe |

## Implemented features

- Infinite world generation
- Biome generation
- Tree generation

## Upcoming features

- Breaking blocks
- Placing blocks
- Water
- Entities including
  - Cows
  - Chickens
  - Pigs
  - Zombies
- Crafting
- Inventory
- Survival mode
- Tools including
  - Pickaxe
  - Axe
  - Shovel
  - Sword
- Ore generation
- Lava
- Cave generation
- Texture packs
- Doors
- Weather
- Day & Night cycle
- Natural structures

## How it works

- [Terrain Generation](#terrain-generation)
- [Rendering](#rendering)
- [Textures](#textures)
- [Optimizations](#optimizations)

## Terrain generation

Check out the library I used from [Reputeless (Ryo Suzuki)](https://github.com/Reputeless/PerlinNoise)

In Minecraft, the terrain must appear random yet feel realistic. To achieve this, I used Perlin noise. Perlin noise works by initializing random values at different points and smoothing the values between those points. The result is a map of seemingly random numbers. We can use these values to determine the height at any given coordinate. To better understand, let's take it down to one dimension.

Generated Perlin values:
\
{ 10, 11, 10, 10, 11, 12, 13, 15, 16, 15, 14, 12, 11, 12, 11, 10 }

![1D Perlin Noise Graph](/readme_images/1d_perlin_graph.png)

After plotting these numbers on a line graph, it becomes clear how this can be used in terrain generation. When expanded into the 2nd dimension, this will result in terrain.

Creating biomes done the same way, although instead of a map to determine the height of the blocks, each generated Perlin value has a corresponding biome.

Example:
\
A value between 0.5 and 0.6 = desert biome.
\
A value between 0.6 and 0.7 = grasslands biome.
\
etc.

If we use the same values from the height map, we will end up with each biome generated at specific heights. For example, every desert biome will range from y level 50 - 60 and grasslands 61 - 70. To avoid this, a biome offset value is used. The biome offset tells the game to use the Perlin map several hundred thousand blocks away. This way, the biomes can have the same seed as the terrain making it repeatable, and there will be no correlation to the current terrain and biome.

The same is done for trees, cave generation, ore generation, lakes, etc.

Here are some excellent resources for understanding Perlin Noise.

[Video by Fataho](https://www.youtube.com/watch?v=MJ3bvCkHJtE&ab_channel=Fataho)
\
[Video by Blake Gillman](https://www.youtube.com/watch?v=9x6NvGkxXhU&ab_channel=BlakeGillman)
\
[Wikipedia Article](https://en.wikipedia.org/wiki/Perlin_noise)

## Rendering

TODO Write this

## Textures

TODO Write this

## Optimizations

TODO Write this
