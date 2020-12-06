
# Poor mans build system

(c) dbj@dbj.org

## Why would anybody do this?

You want to use same code to build (a lot) of different targets. But you decide CMake is an overkill.
Just like I was.

Thus this is the outcome. Usig VSCode and one windows script cmd file for non trivial multi target building.

Largely time was spent in finding workarounds in the labyrinth of VSCode bugs in the area of using it's own json config files. Together with VSCode C++ extension. 

And yes never forget: developing bat scripts is lake balancing on the very high rope, with no safety net. Just don't do it. So why was I using windows scripting? Because it is inbuilt into the OS. 

WSH is also inbuilt but it seems, it is in this peculiar state of support or no support.

Files inside .vscode are extensively commented. Just go ahead and use.

## &quot; or not to &quot; (double quotes that is)

Basically most of the hacks inside are blossomed because of adding or removing double quotes for values taken from setting.json, then massaged in tasks.json and then passed to and yet another time massaged inside driver.cmd

In the same time trying to keep driver.cmd number of arguments constant.

## Usage

This is Windows only project. You need VStudio 2019 with C++ and clang included in the installation. And the you need VSCode and C++ addon for it.

C++ code used is not mine and is kind-of-a choosen so it will provoke loads of warnings with /Wall.

## To do

building and using static libraries in this one app.

---
(C) 2020 by dbj@dbj.org  https://dbj.org/license_dbj 
