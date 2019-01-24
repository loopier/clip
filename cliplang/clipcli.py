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
from reader import *
from logger import *
from utils import *

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
    reader = Reader()
    bAutoServer = False # boots server on startup and shuts it down on exit

    def preloop(self):
        self.do_shell("clear")
        log.info("Booting...")
        global osc
        # osc.setIp("localhost")
        osc.setPort(12345)
        osc.connect()
        log.info("sending OSC test message...")
        osc.send("/loopier/clip/test", [0, 0.1, "alo"])

        if "-d" in sys.argv:
            print("Running DEBUG mode.  See log file for output.")
            self.do_loglevel("debug")
        if not("-b" in sys.argv):
            self.bAutoServer = True
            self.bootServer()
        else:
            print("Server not booted.  Type 'server boot' or run the app\n\
without the '-b' flag.")


    def parseCmd(self, arg):
        """Parses the arguments to convert them to clip commands"""
        args = arg.split()
        log.debug(str(len(args))+" arguments: "+str(args))

        # Skip one-word commands.
        # They would be commands for this app and they should've been
        # already handled.
        if len(args) <= 1:
            return

        action = args[0]
        target = "clip"

        if self.reader.isGroupCommand(args[1]):
            target = args[1]
            args.pop(1)

        # translate the words to commands
        # first argument is the command
        cmd = self.reader.getCommand(action, target)
        if cmd == None:
            return
        # the rest are parameters
        args.pop(0)
        args = " ".join(args)

        osc.send(cmd, args)

        # execute translation as if it had been typed
        # self.onecmd(str(cmd))

    def do_server(self, arg):
        """Control the server.
        'server boot': boots the server
        'server quit': stops the server
        'server reboot': reboots the server"""
        exec("self."+arg+"Server()")

    def do_s(self, arg):
        """Control the server.  See 'server'"""
        self.do_server(arg)

    def bootServer(self):
        """Boots Clip server.
        Currently only for OSX"""
        log.info("Boot server")
        self.do_shell("open -a Terminal '../bin/clipServer.command'")

    def quitServer(self):
        """Quits Clip server"""
        log.info("Quit server")
        self.parseCmd("quit")

    def rebootServer(self):
        """Reboots the server"""
        self.quitServer()
        self.bootServer()

    # def do_print(self, arg):
    #     """Usage: print <msg>"""
    #     print(str(type(arg))+" "+arg)

    def do_shell(self, arg):
        """Execute any shell command.  You may use ! instead.
Usage: (shell | !) <command>"""
        os.system(arg)

    def do_exit(self, arg):
        """Quits out of Interactive Mode."""
        if self.bAutoServer:
            self.quitServer()
        print('Good Bye!')
        exit()

    def do_quit(self, arg):
        """Quits out of Interactive Mode."""
        self.do_exit(arg)

    def do_q(self, arg):
        """Quits out of Interactive Mode.  Same as 'quit'"""
        self.do_exit(arg)

    def do_clear(self, arg):
        """Clears the screen"""
        self.do_shell("clear")

    def do_c(self, arg):
        """Clears the screen. Same as 'clear'"""
        self.do_clear(arg)

    def do_reset(self, arg):
        """Clears the screen and prints the intro"""
        self.do_clear(arg)
        print(self.intro)

    de_EOF = do_exit # exit with Ctl-D

    def do_osc(self, arg):
        """Send an OSC message"""
        args = arg.split()
        addr = args[0]
        args.pop(0)
        osc.send(addr, args)

    def do_log(self, arg):
        """Print log to screen"""
        self.do_clear(arg)
        self.do_shell("cat *.log")

    def do_loglevel(self, arg):
        """Sets the log level.
Usage: loglevel <critical | error | warning | info | debug | none>"""
        log.debug(arg)
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
        log.debug(log.getEffectiveLevel())

    def do_commands(self, arg):
        """Prints the list of all server commands"""
        print(printableList(self.reader.getCommandList()))

    def do_h(self, arg):
        """Show help.  See 'help help'"""
        self.do_help(arg)

    # called every time a command is entered that does not correspond to
    # any of the do_* methods
    def default(self, arg):
        if arg == '!':
            return self.do_shell(arg)

        self.parseCmd(arg)
        # print("Default: {}".format(arg))

ClipCli().cmdloop()

print(opt)
