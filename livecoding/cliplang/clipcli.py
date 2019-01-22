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
import logging
# from cliplang.cliplang import *
from oscsender import OscSender

log = logging.getLogger(__name__)
thismodule = sys.modules[__name__]
osc = OscSender()

class ClipCli (cmd.Cmd):
    intro = " ▄▄▄▄▄▄▄▄▄▄▄  ▄            ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄ \n\
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

    def do_loglevel(self, arg):
        """Sets the log level.
Usage: loglevel <critical | error | warning | info | debug | none>"""
        if arg == 'critical':
            log.setLevel(logging.CRITICAL)
        if arg == 'error':
            log.setLevel(logging.ERROR)
        if arg == 'warning':
            log.setLevel(logging.WARNING)
        if arg == 'info':
            log.setLevel(logging.INFO)
        if arg == 'debug':
            log.setLevel(logging.DEBUG)
        if arg == 'none':
            log.setLevel(logging.NOTSET)


    def preloop(self):
        # self.do_shell("clear")
        log.info("Booting...")
        global osc
        # osc.setIp("localhost")
        osc.setPort(12345)
        osc.connect()
        log.info("sending OSC test message...")
        osc.send("/loopier/clip/test", [0, 0.1, "alo"])

    def parse_cmd(self, arg):
        """Parses the arguments to convert them to clip commands"""
        args = arg.split()
        log.debug(str(len(args))+" arguments: "+str(args))

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

    def do_clear(self, arg):
        """Clears the screen"""
        self.do_shell("clear")

    def do_reset(self, arg):
        """Clears the screen and prints the intro"""
        self.do_clear(arg)
        print(self.intro)

    de_EOF = do_exit # exit with Ctl-D

    # called every time a command is entered that does not correspond to
    # any of the do_* methods
    def default(self, arg):
        if arg == 'q':
            return self.do_exit(arg)
        if arg == '!':
            return self.do_shell(arg)

        self.parse_cmd(arg)
        # print("Default: {}".format(arg))

ClipCli().cmdloop()

print(opt)
