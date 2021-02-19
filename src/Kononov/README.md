# Problems solved by Arseniy Kononov

## Common

It is the directory for `Kononov::Common` library. This code is reused by several tasks. The library contains:

1) Classes for handling user input such as `DirectionInputController` and `MotionInputController`.
2) Classes for organizing object hierarchy `PositionedObject`.
3) And class that represents `Camera` object.

All these classes do simple computations. But some classes like `Camera` and `ShaderProgram` may also change OpenGL
state.

## Task1

This directory contains code for first task. The solution uses OpenGL 3.3.

I decided to make something more interesting than a simple cube. I made rendering of a much more complex model with more
than 20,000 triangles. I also decided to add some simple lighting.

The program allows movement across the scene:

* To rotate camera move mouse while pressing `LMB`.
* To move camera in horizontal directions use `WASD` keys.
* To move camera vertically use `Shift` and `Space` keys.

The prefix `First` in the class name means that I want to extract superclass, but I haven't decided how to do it.

Class `FirstRenderable` represents some mesh stored in `VBO` and `IBO` with some texture and shader.

Class `FirstShader` is responsible for loading shader and linking shader attributes to `VBO`.

Class `SceneObject` represents object placed in the scene. The class inherits from `PositionedObject` and contains
reference to `FirstRenderable` object.
