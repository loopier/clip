""" A class to read cliplang language dictionaries"""
import os
import sys
import cmd
import logging
import yaml

log = logging.getLogger(__name__)

class Reader():
    language = "default"
    dictionary = {}
    inverseDictionary = {}

    def __init__(self):
        self.load()
        log.info("Loaded dictionary: "+self.language)

    def load(self, name="default"):
        """Loads a dictionary"""
        path = os.getcwd() + "/dictionaries/" + name + ".yml"
        # path = os.getcwd() + "/../bin/data/commands.yml"
        log.debug("loading dictionary '"+name+"' from: " + path)
        dict = yaml.load(open(path))
        log.debug(dict)
        self.dictionary = dict;
        self.inverseDictionary = self.invertDictionary(dict)
        self.language = name
        # return dict

    def invertDictionary(self, dict):
        """Returns the dictionary with keys as values and values as keys"""
        inverted = {v:k for  k, v in dict.items()}
        log.debug(inverted)
        return inverted

    def translate(self, word, language=""):
        """Translates a word from one dictionary to a command"""
        if language != self.language and len(language) != 0:
            self.load(language)
            log.debug("Change language to: "+self.language)
        cmd = None
        try:
            word = word.lower()
            cmd = self.inverseDictionary[word]
            log.debug("'"+word+"' from "+self.language+" => "+cmd)
        except:
            log.error("'"+word+"' not found the dictionary '"+self.language+"'")

        return cmd
