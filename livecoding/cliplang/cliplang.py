import inspect
import sys
import logging
import os
import types
import yaml
import time
from cliplang.oscsender import OscSender

# logging.basicConfig(format='[%(levelname)s] %(funcName)s: %(message)s', level=logging.DEBUG)
# log = logging.getLogger(__name__)

thismodule = sys.modules[__name__]
osc = OscSender()

class Clip:
    def __init__(self, name):
        self.name = name
        setattributes(self, commands['clip'], name)
        self.new()

class ClipApp:
    def __init__(self):
        setattributes(self, commands['app'], "app")
    pass

# cliptemplate = Clip("")
# app = ClipApp()

# def boot():
#     log.info("Booting...")
#     global osc
#     # osc.setIp("localhost")
#     osc.setPort(12345)
#     osc.connect()
#     log.info("sending OSC test message...")
#     osc.send("/loopier/clip/test", [0, 0.1, "alo"])
#     global commands
#     commands = loadcommands()
#     global app
#     app = ClipApp()

def loadcommands():
    path = os.getcwd() + "/../bin/data/commands.yml"
    log.debug("loading commands from: " + path)
    return yaml.load(open(path))

def functionbuilder(list, command, name):
    def function(*args):
        oscargs = [name]
        for i in args:
            oscargs.append(i)
        osc.send(list[command], oscargs)
        # print(command, name, oscargs)
    return function

def setattributes(obj, list, instancename):
    for item in list:
        setattr(obj, item, functionbuilder(list, item, instancename))

def printcommands(name=""):
    global commands
    if name == "":
        for i in commands.keys():
            print(i + " commands:")
            printcommands(i)
        return

    for key in commands[name]:
        print ("- " + key)

def listcommands(name=""):
    printcommands(name)

def commands(name=""):
    printcommands(name)

def getListAsString(header, list):
        items = header
        for i in list:
            items += "\n- " + i
        return items

# def newclip(clipname):
#     globals()[clipname] = Clip(clipname)

log.info("Booting...")
global osc
# osc.setIp("localhost")
osc.setPort(12345)
osc.connect()
log.info("sending OSC test message...")
osc.send("/loopier/clip/test", [0, 0.1, "alo"])
commands = loadcommands()
app = ClipApp()
