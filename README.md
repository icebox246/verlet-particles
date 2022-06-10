# Verlet particles

![screenshot](screenshot.jpg)

This is a basic physics engine written in C.
It supports simulating movement of circle shaped bodies and their collision with lines.

Rendering is facilitated using SDL2.

## Online demo

Online demo is available at:

[ https://verletdemo.netlify.app/ ]( https://verletdemo.netlify.app/ )

## Quick start

Project can be built both for Linux:

```console
make
./out
```

Or for web using [Emscripten](https://emscripten.org/)

```console
make web
```

*(Output files can be served from `web/`)*


