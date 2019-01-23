import logging

logfile = "cliplang.log"
#comment this if you don't want to clear the log every time
open(logfile, "w").close()

logging.basicConfig(\
format='[ %(levelname)s ] [%(asctime)s] %(filename)s: %(funcName)s: %(message)s',\
level=logging.INFO,\
filename=logfile)
log = logging.getLogger(__name__)
