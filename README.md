# My customized DWM window manager

Mainly as an addition it includes some patches like:

- systray (patched)
- dzen2 status bar (has an update to dwm.c in order to toggle visibility)
- restart with recompilation support while keeping all active windows running

Same as original it may be the fastest WM available, hackable masterpiece from [suckless.org](http://dwm.suckless.org).
The reason why I chose it, is because this is the original implementation of idea, later followed by Xmonad, Awesome, I3
and other wms. And it is the lightest of them all, plus if you are a hacker you are free to see the whole source in
a single file in 2000 lines of code, which is directly using Xorg X11 functions.

## Screenshot

![My image](https://raw.github.com/l3pp4rd/dwm/master/screen.png)

## Requirements

- **Xlib**, **Xft** - X FreeType interface library.
- **Xinerama** lib is optional
- My [dotfiles](https://github.com/l3pp4rd/dotfiles) contains necessary scripts to run dzen2 status and other tools,
which has a bunch of deps too. You can see what is being launched in **xinitrc**

## Installation

Edit **config.mk** to match your local setup

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

A start script (lets name it **dwm-personalized**) for dwm could look like:

``` sh
#!/bin/sh

DZEN2_STATUS="$HOME/.dotfiles/scripts/dwm_status"

setxkbmap -option ctrl:nocaps & # disable caps lock
xsetroot -name "" &             # we have dzen2 status bar, set main WM window title to none

if [ !-f "$DZEN2_STATUS" ]; then
    DZEN2_STATUS="echo 'dzen2 status is unavailable' | dzen2 -x 780 -y 0 -w 710 -h 20 -ta 'r' -p"
fi

while true; do
    (sleep 0.5 && $DZEN2_STATUS) & # run dzen2 status bar, need to make sure wm loads first

    # start dwm
    dwm > ~/.dwm.log
    # read exit status
    if [ $? -eq 0 ]; then
        exit 0 # means exit clean => quit
    elif [ $? -ne 5 ]; then
        mv ~/.dwm.log ~/.dwm.failure.log # a failure occured, save the log, never happened so far
    fi
    # dwm should be recompiled if changes were done
    # kill running processes
    killall dwm_status
done
```

Do not forget to:

    chmod +x dwm-personalized

And in your xinitrc, instead of **exec dwm** use **exec dwm-personalized** script.
If you want to use a login manager like **Slim** you will need to create an xsession, at
**/usr/share/xsession/dwm-personalized.desktop** with contents:

    [Desktop Entry]
    Encoding=UTF-8
    Name=Dwm-personalized
    Comment=Dynamic window manager
    Exec=dwm-personalized
    Icon=dwm
    Type=XSession

Also, your executable **dwm-personalized** should be moved to **/usr/bin** or **/usr/local/bin**.

