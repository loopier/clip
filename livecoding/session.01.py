from cliplang.cliplang import *
boot()

mamma = Clip("mamma")
mamma.new()
mamma.fliph()
mamma.loop("palindrome")
mamma.color(1,0.5,0)
mamma.scale(1)
mamma.speed(4)

commands('app')
app.shownames()
