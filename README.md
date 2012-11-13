# My customized DWM window manager

Mainly as an addition it includes some patches like:

- systray
- dzen2 status bar

Same as original it may be the fastest WM available, hackable masterpiece from [suckless.org](http://dwm.suckless.org).
The reason why I chose it, is because this is the original implementation of idea, later followed by Xmonad, Awesome, I3
and other wms. And it is the lightest of them all, plus if you are a hacker you are free to see the whole source in
a single file in 2000 lines of code, which is directly using Xorg.

## Screenshot of my terminal

![My image](https://raw.github.com/l3pp4rd/dwm/master/screen.png)

## Requirements

- **Xlib**, **Xft** - X FreeType interface library.
- **Xinerama** lib is optional
- My [dotfiles](https://github.com/l3pp4rd/dotfiles) contains necessary scripts to run dzen2 status and other tools,
which has a bunch of deps too. You can see what is launched in **xinitrc**

## Installation

Edit config.mk to match your local setup

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

