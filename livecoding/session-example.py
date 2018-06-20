from cliplang.cliplang import *

listcommands()
app.listresources()
mamma = Clip("mamma")
mamma.new("glen")
mamma.fliph()
mamma.loop("palindrome")
mamma.color(1,0,0)
mamma.scale(8)
mamma.speed(1)
mamma.moveto(0.25, 0.5)
glen.fliph()
glen.loop("palindrome")
glen.color(1,1,0)
glen.scale(8)
glen.alpha(0.5)
glen.speed(1)
glen.moveto(0.25, 0.5)

glen = Clip("glen")

app.clearallclips()

commands('app')
app.shownames()
app.quit()
x = 0
while x < 4:
    name = 'glen' + str(x)
    globals()[name].new('glen')
    globals()[name].moveto(0.5 - x/1, 0.5)
    globals()[name].scale(0.5)
    time.sleep(1)
    x += 1

glen0.moveto(0.25, 0.25)
glen1.moveto(0.25, 0.5)
glen2.moveto(0.5, 0.5)
glen3.moveto(0.75, 0.5)
glen3.scale(1)
glen3.speed(0.1)
app.listclips()
app.clearallclips()
newclip("mamma")
mamma.loop('palindrome')
mamma
globals()['mamma']
globals()['mamma'] = Clip('mamma')

app.shownames()
app.quit()
