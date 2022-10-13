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

## Controls

| Button     | Action   |
| ---------- | -------- |
| Space      | Fly      |
| Left Ctrl  | Fly down |
| W, A, S, D | Move     |

## Implemented features

- Infinite world generation
- Tree generation

## Upcoming features

- Breaking blocks
- Placing blocks
- Biome generation
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

In Minecraft, the terrain must appear random yet feel realistic. To achieve this, I used Perlin noise. Perlin noise works by initializing random values at different points and smoothing the values between those points. The result is a map of seemingly random numbers. We can use these values to determine the height at any given coordinate. To better understand, let's take it down to one dimension.

Generated Perlin values:
\
{ 10, 11, 10, 10, 11, 12, 13, 15, 16, 15, 14, 12, 11, 12, 11, 10 }

<svg width="600" height="390" aria-label="A chart." style="overflow:hidden"><defs id="_ABSTRACT_RENDERER_ID_480"><clipPath id="_ABSTRACT_RENDERER_ID_481"><rect x="115" y="75" width="371" height="241"></rect></clipPath></defs><rect x="0" y="0" width="600" height="390" stroke="none" stroke-width="0" fill="#ffffff"></rect><g><text text-anchor="start" x="115" y="52.05" font-family="Arial" font-size="13" font-weight="bold" stroke="none" stroke-width="0" fill="#000000">Perlin Noise</text><rect x="115" y="41" width="371" height="13" stroke="none" stroke-width="0" fill-opacity="0" fill="#ffffff"></rect></g><g><rect x="499" y="75" width="88" height="13" stroke="none" stroke-width="0" fill-opacity="0" fill="#ffffff"></rect><g><rect x="499" y="75" width="88" height="13" stroke="none" stroke-width="0" fill-opacity="0" fill="#ffffff"></rect><g><text text-anchor="start" x="530" y="86.05" font-family="Arial" font-size="13" stroke="none" stroke-width="0" fill="#222222">Line1</text></g><path d="M499,81.5L525,81.5" stroke="#3366cc" stroke-width="3" fill-opacity="1" fill="none"></path><circle cx="512" cy="81.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle></g></g><g><rect x="115" y="75" width="371" height="241" stroke="none" stroke-width="0" fill-opacity="0" fill="#ffffff"></rect><g clip-path="url(https://www.rapidtables.com/tools/line-graph.html#_ABSTRACT_RENDERER_ID_481)"><g><rect x="115" y="315" width="371" height="1" stroke="none" stroke-width="0" fill="#cccccc"></rect><rect x="115" y="255" width="371" height="1" stroke="none" stroke-width="0" fill="#cccccc"></rect><rect x="115" y="195" width="371" height="1" stroke="none" stroke-width="0" fill="#cccccc"></rect><rect x="115" y="135" width="371" height="1" stroke="none" stroke-width="0" fill="#cccccc"></rect><rect x="115" y="75" width="371" height="1" stroke="none" stroke-width="0" fill="#cccccc"></rect><rect x="115" y="285" width="371" height="1" stroke="none" stroke-width="0" fill="#ebebeb"></rect><rect x="115" y="225" width="371" height="1" stroke="none" stroke-width="0" fill="#ebebeb"></rect><rect x="115" y="165" width="371" height="1" stroke="none" stroke-width="0" fill="#ebebeb"></rect><rect x="115" y="105" width="371" height="1" stroke="none" stroke-width="0" fill="#ebebeb"></rect></g><g><rect x="115" y="315" width="371" height="1" stroke="none" stroke-width="0" fill="#333333"></rect></g><g><path d="M127.0625,195.5L150.1875,183.5L173.3125,195.5L196.4375,195.5L219.5625,183.5L242.6875,171.5L265.8125,159.5L288.9375,135.5L312.0625,123.5L335.1875,135.5L358.3125,147.5L381.4375,171.5L404.5625,183.5L427.6875,171.5L450.8125,183.5L473.9375,195.5" stroke="#3366cc" stroke-width="3" fill-opacity="1" fill="none"></path></g></g><g><circle cx="127.0625" cy="195.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="150.1875" cy="183.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="173.3125" cy="195.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="196.4375" cy="195.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="219.5625" cy="183.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="242.6875" cy="171.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="265.8125" cy="159.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="288.9375" cy="135.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="312.0625" cy="123.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="335.1875" cy="135.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="358.3125" cy="147.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="381.4375" cy="171.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="404.5625" cy="183.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="427.6875" cy="171.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="450.8125" cy="183.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle><circle cx="473.9375" cy="195.5" r="4.5" stroke="none" stroke-width="0" fill="#3366cc"></circle></g><g><g><text text-anchor="middle" x="127.0625" y="335.05" font-family="Arial" font-size="13" stroke="none" stroke-width="0" fill="#222222">Points</text></g><g><text text-anchor="end" x="102" y="320.05" font-family="Arial" font-size="13" stroke="none" stroke-width="0" fill="#444444">0</text></g><g><text text-anchor="end" x="102" y="260.05" font-family="Arial" font-size="13" stroke="none" stroke-width="0" fill="#444444">5</text></g><g><text text-anchor="end" x="102" y="200.05" font-family="Arial" font-size="13" stroke="none" stroke-width="0" fill="#444444">10</text></g><g><text text-anchor="end" x="102" y="140.05" font-family="Arial" font-size="13" stroke="none" stroke-width="0" fill="#444444">15</text></g><g><text text-anchor="end" x="102" y="80.05" font-family="Arial" font-size="13" stroke="none" stroke-width="0" fill="#444444">20</text></g></g></g><g><g><text text-anchor="middle" x="300.5" y="376.55" font-family="Arial" font-size="13" font-style="italic" stroke="none" stroke-width="0" fill="#222222">X Axis</text><rect x="115" y="365.5" width="371" height="13" stroke="none" stroke-width="0" fill-opacity="0" fill="#ffffff"></rect></g><g><text text-anchor="middle" x="48.55" y="195.5" font-family="Arial" font-size="13" font-style="italic" transform="rotate(-90 48.55 195.5)" stroke="none" stroke-width="0" fill="#222222">Terrain Height</text><path d="M37.49999999999999,316L37.50000000000001,75L50.50000000000001,75L50.49999999999999,316Z" stroke="none" stroke-width="0" fill-opacity="0" fill="#ffffff"></path></g></g><g></g></svg>

After plotting these numbers on a line graph, it becomes clear how this can be used in terrain generation. When expanded into the 2nd dimension, this will result in terrain.

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
