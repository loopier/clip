from cliplang.cliplang import *
boot()
commands()
mamma = Clip("mamma")
mamma.new()
mamma.fliph()
mamma.loop("palindrome")
mamma.color(1,0.5,0)
mamma.scale(1)
mamma.speed(4)

commands('app')
app.shownames()
app.quit()
x = 0
while x < 4:
    mamma.color((x%4)/4, 1, 1)
    time.sleep(1)
    x += 1
