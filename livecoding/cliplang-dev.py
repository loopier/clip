%load_ext autoreload
%autoreload 2
from cliplang.cliplang import *

app
listcommands('app')
app.shownames()
mamma.deselect("mamma")
app = ClipApp()
commands('app')

mamma = Clip("mamma")
mamma.new("edd")

hat = Clip("hat")
hat.new("barret")
hat.background()
hat.scale(1.9)
hat.color(1,0,0)
hat.fullscreen(0)

x = 0
while x < 101:
    mamma.moveto(((x%4)+1)/4, 0.5)
    time.sleep(0.1)
    x += 1

1%4
