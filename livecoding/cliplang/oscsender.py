import argparse
import random
import time
import re # regex
import logging

from pythonosc import osc_message_builder
from pythonosc import udp_client

logging.basicConfig(format='%(levelname)s:%(funcName)s: %(message)s', level=logging.DEBUG)
log = logging.getLogger(__name__)

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

    def send(self, address, args):
        """Sends an OSC message"""
        # address = self.checkAddress(address)
        # self.connect()
        log.info("Sending OSC message: %s" % (address + str(args)))
        self.client.send_message(address, args)

    def testConnection(self):
        for x in range(10):
            self.client.send_message("/clip/test", [x, random.random(), ''.join(random.sample("string", len("string")))])
            time.sleep(1)

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
