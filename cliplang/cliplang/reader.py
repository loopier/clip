""" A class to read cliplang language dictionaries"""
import os
import sys
import cmd
import logging
import yaml

from logger import *
from utils import *


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

    def getCommandList(self):
        """Returns all the keys in the command list"""
        return self.getKeys(self.commands)

    def getKeys(self, dictionary):
        """Returns a recursive array of all the keys in the dictionary"""
        keys = []
        for k, v in dictionary.items():
            keys.append(k)
            if type(v) == dict:
                keys.append(self.getKeys(v))
        return keys
