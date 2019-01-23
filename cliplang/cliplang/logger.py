import logging

logging.basicConfig(\
format='[ %(levelname)s ] %(filename)s: %(funcName)s: %(message)s',\
level=logging.DEBUG,\
filename="cliplang.log")
log = logging.getLogger(__name__)
