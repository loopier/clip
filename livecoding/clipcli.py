#!/usr/bin/env python
# """
# Needs description.
#
# Usage:
#     clipcli print <msg>
#     clipcli tcp <host> <port> [--timeout=<seconds>]
#     clipcli serial <port> [--baud=<n>] [--timeout=<seconds>]
#     clipcli (-i | --interactive)
#     clipcli (-h | --help | --version)
# Options:
#     -i, --interactive  Interactive Mode
#     -h, --help  Show this screen and exit.
#     --baud=<n>  Baudrate [default: 9600]
# """
#
import os
import sys
import cmd
from cliplang.cliplang import *


class ClipCli (cmd.Cmd):
    intro = intro = " ▄▄▄▄▄▄▄▄▄▄▄  ▄            ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄ \n\
▐░░░░░░░░░░░▌▐░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌\n\
▐░█▀▀▀▀▀▀▀▀▀ ▐░▌           ▀▀▀▀█░█▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌\n\
▐░▌          ▐░▌               ▐░▌     ▐░▌       ▐░▌\n\
▐░▌          ▐░▌               ▐░▌     ▐░█▄▄▄▄▄▄▄█░▌\n\
▐░▌          ▐░▌               ▐░▌     ▐░░░░░░░░░░░▌\n\
▐░▌          ▐░▌               ▐░▌     ▐░█▀▀▀▀▀▀▀▀▀\n\
▐░▌          ▐░▌               ▐░▌     ▐░▌\n\
▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄  ▄▄▄▄█░█▄▄▄▄ ▐░▌\n\
▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌\n\
 ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀\n\
                                                    "
    prompt = '. '
    file = None

    def preloop(self):
        self.do_shell("clear")

    def parse_cmd(self, arg):
        """Parses the arguments to convert them to clip commands"""
        print(arg)

    def do_print(self, arg):
        """Usage: print <msg>"""
        print(str(type(arg))+" "+arg)

    def do_shell(self, arg):
        """Execute any shell command.  You may use ! instead.
Usage: (shell | !) <command>"""
        os.system(arg)

    def do_exit(self, arg):
        """Quits out of Interactive Mode."""

        print('Good Bye!')
        exit()

    def do_quit(self, arg):
        """Quits out of Interactive Mode."""
        self.do_exit(arg)

    de_EOF = do_exit # exit with Ctl-D

    # called every time a command is entered that does not correspond to
    # any of the do_* methods
    def default(self, arg):
        if arg == 'q':
            return self.do_exit(arg)
        if arg == '!':
            return self.do_shell(arg)

        self.parse_cmd(arg)
        print("Default: {}".format(arg))

ClipCli().cmdloop()

print(opt)
