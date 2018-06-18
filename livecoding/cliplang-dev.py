%load_ext autoreload
%autoreload 2
from cliplang.cliplang import *

boot()
printcommands()

mamma = Clip("mamma")
mamma.new("edd")

x = 0
while x < 4:
    mamma.new("ed"+str(x))
    x += 1
