# Shutup


Absolutely positively mute your Mac when sending it to sleep.

## What it does

It uses a very small program that is always running and listens for sleep events. When a sleep event occurs (the computer is going into sleep mode), it sets the volume to 0 via `osascript`. That's it.

This is useful when you often open your MacBook in quiet places and want to be absolutely sure that audio is muted.

There are other ways to achieve this, but this program has served me well for years.


## Installation

Simply run `make`, install the binary and launch agent.

```shell
$ make
$ mkdir ~/bin/
$ cp shutup ~/bin/
```

Now copy the `.plist` into your user's LaunchAgent directory and replace `SHUTUPPATH` with the path to your `shutup` binary:

```shell
$ sed s%SHUTUPPATH%$HOME/bin/shutup% com.pascalj.shutup.plist > ~/Library/LaunchAgents/com.pascalj.shutup.plist
launchctl load ~/Library/LaunchAgents/com.pascalj.shutup.plist

```

This is necessary because LaunchAgents cannot use globbing any more without invoking a shell.

## Uninstall

Unload and remove the LaunchAgent and remove the binary:

```shell
launchctl unload ~/Library/LaunchAgents/com.pascalj.shutup.plist
rm ~/Library/LaunchAgents/com.pascalj.shutup.plist
rm ~/bin/shutup
```