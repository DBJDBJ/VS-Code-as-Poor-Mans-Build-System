
# VS Code as Poor Mans Build System (PMBS)

&copy; 2020-2021 by dbj@dbj.org, https://dbj.org/license_dbj

## Why would anybody do this?

You want to use same code to build (a lot) of different targets. But you have decided CMake is an overkill. Just like I was.

Thus this is the outcome. Usig VSCode and one windows script cmd file for non trivial multi target building.

Largely, time was spent in finding workarounds in the labyrinth of VSCode bugs, in the area of using it's own [json config files](https://github.com/microsoft/vscode/issues/47985). Together with VSCode C++ extension. 

And yes, please never forget this: developing bat scripts is lake balancing on the very high rope, with no safety net bellow. Just don't do it. So why was I using windows scripting? Because it is inbuilt into the OS. 

It would be much easier to use WSH. WSH is also inbuilt in Windows, but it seems, it is in this peculiar state of "support or no support". And nobody knows for how long.

We are using clang-cl part of the VStudio 2019. Obviously your clang-cl.exe compilers locations might be different.

And same as ever you must start the lot from `vcvarsall.bat` and cmd window, "black staring" at you, after running vcvarsall.bat from your Windows 10 Start Menu.

## &quot; or not to &quot; (double quotes that is)

Basically most of the hacks left inside, have blossomed because of adding or removing double quotes for values taken from setting.json, then massaged in tasks.json and then passed to and yet another time massaged inside driver.cmd

In the same time trying to keep driver.cmd number of arguments constant. Files inside .vscode in here are extensively commented. Just go ahead and use. 

## Usage

This is Windows only project. You need VStudio 2019 with C++ and clang included in the installation. And the you need VSCode and C++ addon for it.

C++ code used is not mine and is kind-of-a choosen so it will provoke loads of warnings with /Wall.

### libs and dll's

Using cl.exe and link.exe for building static libraries is not trivial. But [building simple DLL](https://docs.microsoft.com/en-us/windows/win32/dlls/creating-a-simple-dynamic-link-library) is quite easy. Study the `/DLL` switch and make sure you have used dllexport attribute properly.

## But why not just using Visual Studio?

Very valid question. Building this way is on the edge of "reasonable". Visual Studio 2019 Community is free and still the best IDE out there.

VSCode is much faster and lighter way to quickly build single file C/C++ solutions. It has no solutions and projects getting in the way for this kind of single file use-cases.

Jut open it from the Visual Studio cmd prompt, open your folder and that single c or cpp and hit F5. And that's it. Provided you have installed and configured C++ VS Code extension before that. That should be enough.

> But seldom it is enough. 

And this is a solution for that situation before you decide to go back to the safety of Visual Studio. But still you need some "slightly beyond trivial" command line building. 

And if you use my work from here, that "just a litle bit more" requirement will be easy to fulfill. Like having two or more single file solutions in the same folder. Or wishing to build exe and/or dll from the same file. Or comparing clang-cl to cl or MINGW gcc. And more...

Also. It is much easier managing the build properties using the VS Code text files v.s. hopping back and forth through Visual Studio project properties dialogues. That  is one "thing" where VStudio usability really suffers.

And wishing to do all of that "quickly". 

ps: Possible support as ever, might come through the GitHub issues section.

---


| Contact | &nbsp;
|---------|----------
|[Email](mailto:info@dbj.systems) | [![dbj();](https://dbj.org/wp-content/uploads/2015/12/cropped-dbj-icon-e1486129719897.jpg)](http://www.dbj.org "dbj")
|[Skype](skype:live:dbj.systems?chat) | 
