import argparse
import random
import time
import re # regex

from pythonosc import osc_message_builder
from pythonosc import udp_client
from logger import *

class OscSender(object):

    def __init__(self):
        self.ip = "127.0.0.1" # localhost
        self.port = 12345
        self.address = "/clip" # base OSC address for messages

    def setIp(self, ip):
        """Set the OSC server IP address"""
        self.ip = ip

    def setPort(self, port):
        """Set the OSC server port number"""
        self.port = port

    def connect(self):
        """Sets a connection to an OSC server"""
        log.info("Connecting to %s:%i" % (self.ip, self.port))
        # parser = argparse.ArgumentParser()
        # parser.add_argument("--ip", default=self.ip, help="OSC server IP")
        # parser.add_argument("--port", type=int, default=self.port, help="OSC server port")
        # args = parser.parse_args()
        # self.client = udp_client.SimpleUDPClient(args.ip, args.port)
        self.client = udp_client.SimpleUDPClient(self.ip, self.port)

    def printMsg(self, address, args):
        """Print osc message in a readble format"""
        argsstr = "" # for logging
        for a in args:
            if type(a) == int:
                argsstr += " i:"
            elif type(a) == float:
                argsstr += " f:"
            else:
                argsstr += " s:"
            argsstr += str(a)
        log.info("Sending OSC message: %s %s" % (address, argsstr))

    def send(self, address, args):
        """Sends an OSC message"""
        # address = self.checkAddress(address)
        # self.connect()
        # make sure args is list
        # if isinstance(args, str):
        #     args = args.split()
        args = self.parseArgs(args)
        self.printMsg(address, args)
        self.client.send_message(address, args)

    def parseArgs(self, args):
        """Takes a string or a list and returns a list of different types"""
        if isinstance(args, str):
            args = args.split()
        newargs = []
        for a in args:
            try:
                newargs.append(float(a))
            except:
                newargs.append(a)

        return newargs

    def testConnection(self):
        # for x in range(10):
        #     self.client.send_message("/clip/test", [x, random.random(), ''.join(random.sample("string", len("string")))])
        #     time.sleep(1)
        self.client.send_message("/clip/test",[1])


    # ------- HELPERS -----------
    def checkAddress(self, address):
        """Prepends base address if not already in the given address"""
        log.debug(address)
        splitaddress = address.split('/')
        if splitaddress[1] == self.address[1:]:
            return address
        else:
            log.info("Prepending %s to address %s" % (self.address, address))
            return self.address+address
