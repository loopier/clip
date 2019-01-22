# A CLI using de CmdModule https://wiki.python.org/moin/CmdModule
# as shown in https://code-maven.com/interactive-shell-with-cmd-in-python
from cmd import Cmd

class MyPrompt(Cmd):
    prompt = 'pb> '
    # http://patorjk.com/software/taag/#p=display&f=Electronic&t=Clip
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

    def do_exit(self, inp):
        '''Exit the application'''
        print("\nBye")
        return True

    def do_add(self, inp):
        '''Add a new entry to the system.'''
        print("Adding '{}'".format(inp))

    # called every time a command is entered that does not correspond to
    # any of the do_* methods
    def default(self, inp):
        if inp == 'x' or inp == 'q':
            return self.do_exit(inp)

        print("Default: {}".format(inp))

    do_EOF = do_exit # exit with Ctl-D

if __name__ == '__main__':
    MyPrompt().cmdloop()

print("...")
