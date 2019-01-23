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
    language = "default"

    def __init__(self):
        self.load()
        self.commands = self.loadCommands(os.getcwd() + "/../../bin/data/commands.yml")
        log.info("Loaded dictionary: "+self.language)

    def load(self, name="default"):
        """Loads a dictionary and sets the language"""
        path = os.getcwd() + "/dictionaries/" + name + ".yml"
        # path = os.getcwd() + "/../bin/data/commands.yml"
        log.debug("loading dictionary '"+name+"' from: " + path)
        dict = yaml.load(open(path))
        log.debug(dict)
        self.dictionary = dict;
        self.inverseDictionary = self.invertDictionary(dict)
        self.language = name
        # return dict

    def loadCommands(self, path):
        """Loads a dictionary of commands to OSC messages"""
        log.info("Loading commands from: "+path)
        commands = yaml.load(open(path))
        log.debug(printableDictionary(commands))
        return commands

    def getCommandsList(self):
        """Returns a dictionary  of commands"""
        return self.commands

    def getCommand(self, key):
        """Returns the key corresponding to the value from the given dictionary"""
        cmd = self.findValue(key, self.commands)
        if cmd == None:
            log.error("Command not found: '"+key+"'")
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

    def invertDictionary(self, dictionary):
        """Returns the dict with keys as values and values as keys"""
        # inverted = {v:k for  k, v in dictionary.items()}
        inverted = dictionary
        log.debug(inverted)
        return inverted

    def translate(self, words):
        """Translates words from one dictionary to a command"""
        # try different combinations of words to match a key in the dictionary
        # split words into an array
        wordarray = words.split()
        commands = []
        # iterate combinations
        for w in wordarray:
            cmd = self.getCommands(wordarray)
            if cmd != None:
                commands.append(cmd)
            wordarray.remove(w)
        log.debug(commands)

    # def getCommands(self, words):
    #     """Iterates through the words looking for  commands"""
    #     # !!! TODO: Check for  commands in combinations of words
    #     # log.debug(str(len(words))+" - "+str(words))
    #     cmd = self.getCommand(" ".join(words))
    #     if cmd == None:
    #         newwords = words.copy()
    #         newwords.pop()
    #         self.getCommands(newwords)
    #     else:
    #         return cmd

    # def getCommand(self, words):
    #     """Checks if there's an entry for these words. Returns a command if
    #     entry exists.  Returns 'None' otherwise"""
    #     cmd = None
    #     try:
    #         words = words.lower()
    #         cmd = self.inverseDictionary[words]
    #         log.debug("'"+words+"' from "+self.language+" => "+cmd)
    #     except:
    #         log.error("'"+words+"' not found the dictionary '"+self.language+"'")
    #
    #     return cmd

    def removePunctuationMarks(self, words):
        """Removes punctuation marks suhc as commas, periods, ..."""
        words = words.replace(",", " ")
        words = words.replace(".", " ")
        words = words.replace(";", " ")
        return words
