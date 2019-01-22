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
# from docopt import docopt, DocoptExit
#
#
# def docopt_cmd(func):
#     """
#     This decorator is used to simplify the try/except block and pass the result
#     of the docopt parsing to the called action.
#     """
#     def fn(self, arg):
#         try:
#             opt = docopt(fn.__doc__, arg)
#
#         except DocoptExit as e:
#             # The DocoptExit is thrown when the args do not match.
#             # We print a message to the user and the usage block.
#
#             print('Invalid Command!')
#             print(e)
#             return
#
#         except SystemExit:
#             # The SystemExit exception prints the usage for --help
#             # We do not need to do the print here.
#
#             return
#
#         return func(self, opt)
#
#     fn.__name__ = func.__name__
#     fn.__doc__ = func.__doc__
#     fn.__dict__.update(func.__dict__)
#     return fn


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

    # @docopt_cmd
    def do_print(self, arg):
        """Usage: print <msg>"""
        print(str(type(arg))+" "+arg)

#     @docopt_cmd
#     def do_tcp(self, arg):
#         """Usage: tcp <host> <port> [--timeout=<seconds>]"""
#
#         print(arg)
#
#     @docopt_cmd
#     def do_serial(self, arg):
#         """Usage: serial <port> [--baud=<n>] [--timeout=<seconds>]
# Options:
#     --baud=<n>  Baudrate [default: 9600]
#         """
#
#         print(arg)

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

# opt = docopt(__doc__, sys.argv[1:])

# if opt['--interactive']:
    # ClipCli().cmdloop()
ClipCli().cmdloop()

print(opt)
