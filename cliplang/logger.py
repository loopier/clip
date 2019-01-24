import logging
import os

logfile = "cliplang.log"
#comment this if you don't want to clear the log every time
open(logfile, "w").close()

# logging.basicConfig(\
# format='[ %(levelname)s ] [%(asctime)s] %(filename)s: %(funcName)s: %(message)s',\
# level=logging.INFO,\
# filename=logfile)
# log = logging.getLogger(__name__)
logFormatter = logging.Formatter('[ %(levelname)s ] [%(asctime)s] %(filename)s: %(funcName)s: %(message)s')
log = logging.getLogger()

logFileHandler = logging.FileHandler("{0}/{1}.log".format(os.getcwd(), logfile))
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
