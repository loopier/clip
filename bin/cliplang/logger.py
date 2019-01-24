import logging
import os
import time

logpath = os.path.dirname(__file__)+"/logs"
logfile = "cliplang-"+(time.strftime("%Y%m%dT%H%M%S", time.gmtime()))

logFormatter = logging.Formatter('[ %(levelname)s ] [%(asctime)s] %(filename)s: line %(lineno)s: %(message)s')
log = logging.getLogger()

logFileHandler = logging.FileHandler("{0}/{1}.log".format(os.path.dirname(__file__)+"/logs", logfile))
logFileHandler.setFormatter(logFormatter)
log.addHandler(logFileHandler)

logConsoleHandler = logging.StreamHandler()
logConsoleHandler.setFormatter(logFormatter)
# log.addHandler(logConsoleHandler)

def logToConsole(b=True):
    """Choose whether to print logs to console or not"""
    if b:
        log.addHandler(logConsoleHandler)
    else:
        log.removeHandler(logConsoleHandler)
