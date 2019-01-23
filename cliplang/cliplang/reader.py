""" A class to read cliplang language dictionaries"""
import os
import sys
import cmd
import logging
import yaml

from logger import *

def printableDictionary(dict, iter=0):
    """Returns a string representing the dictionary in a printable format
    with nested objects tabulated"""
    s = "\n"
    for k in dict:
        i=0
        while i < iter:
            s += "\t"
            i += 1
        if type(dict[k]) == type(dict):
            s += k + ":" + printableDictionary(dict[k], iter+1)
        else:
            s += k + ": " + dict[k] + "\n"
    return s


class Reader():
    commands = {}

    def __init__(self):
        self.commands = self.loadCommands(os.getcwd() + "/../../bin/data/commands.yml")

    def loadCommands(self, path):
        """Loads a dictionary of commands to OSC messages"""
        log.info("Loading commands from: "+path)
        commands = yaml.load(open(path))
        log.debug(printableDictionary(commands))
        return commands

    def getCommandsList(self):
        """Returns a dictionary  of commands"""
        return self.commands

    def getCommand(self, key, target=None):
        """Returns the key corresponding to the value from the given dictionary"""
        cmd = None
        # first check if the target matches any of the  top nodes of
        # the commands tree
        if str(target) in self.commands:
            cmd = self.findValue(key, self.commands[target], target)
            log.debug(cmd)
        elif cmd == None and target != None:
            cmd = self.findValue(key, self.commands["clip"], "clip")
        elif cmd == None:
            cmd = self.findValue(key, self.commands)
        if cmd == None:
            log.error("Command '"+key+"' not found for target '"+str(target)+"'")
        # log.debug(cmd)
        return cmd

    def findValue(self, key, dictionary, parent="root"):
        """Searches iteratively for 'key' in a nested dictionary"""
        # log.debug("Searching '"+key+"' in "+parent)
        value = None
        if key in dictionary:
            log.debug(key + " found in " + parent)
            value = dictionary[key]
        else:
            # log.debug(key + " not found")
            for k in dictionary:
                if type(dictionary[k]) is dict:
                    value = self.findValue(key, dictionary[k], parent+":"+k)
                if value != None:
                    break
        return value
