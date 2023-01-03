# provaPGE

A long time project to see the movements of various celestial pbject in the space

> **DISCLAIMER**: free traveler that in your trip in github came across this repo, this is the work of two free thinkers physics university student, so if you run in some arguable piece of code feel free to notifie us, if you encounter some problem please notifie us.
**you should not expect us to solve your problem in a timely matter**. Also thank you for any positive or negative _constructive_ feedback.

If you want to contribute to this code you can open a pull request, if it will be merged your contribution will be added to the credits.

## How to compile

The project uses c++17 standard. It adheres to the standard in every way.
It uses as game engine the [olcPixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine) made by javidx9 also known as [One Lone Coder](https://github.com/OneLoneCoder) under OLC-3 Licence.
In ```PixelGameEngine.h``` and ```olcPGEX_TransformedView.h``` it is provided a copy of OLC-3 Licence as required by javidx9. I don\'t know if this is enough... but the license it is supplied, so I think I am in the clear. 

### Windows User

It is provided a visual studio 2022 solution, so you will not run in any problem if you use Visual Studio 2022... 
I will not test it in Visual Studio 2019 or 2017, but if you want to do it, please report if all went well.

### Unix Like User

There is a Makefile, please use it, if it doesn't function edit until something happens.
So now we have a CMake that function... but only in linux envinroments (it is not so crossplatform)... so it is a great day to be a linux user :-).

#### Mac OS

I do not have a Mac... so I do not know, CMake couldn't be tested in Mac OS enviroments, so you need to modify it adding the feature requested for compilation
(**I think, but I DO NOT guaratee** that they should be very similar to linux flags exposed [here](https://github.com/OneLoneCoder/olcPixelGameEngine/wiki/Compiling-on-Linux)).

## Functioning

### What Doesn't work

- Panning, but for now it is not a big problem.
- Celestial it is not yet implemented, but it will be in the near future (Before my death, as a physicist I must specify that near future is referenced to the lifetime of a rock)
- We do not have the sprites for every planet... Better we do not have any sprite.
- The certainty that this compiles in MacOS... only a remote idea that it should compile.
- A good CMake... but for me it works.
- Testing... if someone is capable of writing some good test equipment it is gladly accepted... Now it is purely manual.

### What actually there is:

- A zoom, but it doesn't feel right
- A Ball with gravity
- Two types of Integration : Euler and Runge Kutta 4. In the future we will add more.
- A good framerate, at least for now.
- Some heavy OOP.

And remember: "Potato always wins!!"