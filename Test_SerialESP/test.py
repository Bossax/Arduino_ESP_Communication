import math

f = 1021.23134
divider = 10
bfd = 1
f_text = ''
precision = 4

while(True):

    if ((int(f/divider) == 0) and (f%divider ==f)):
        break
    divider = divider*10
    bfd +=1

divider = 10**(bfd-1)
for i in range(bfd):
    buffer = int(f/divider)
    f_text += str(buffer)
    f = f-buffer*divider
    divider = divider/10
f_text += "."
for i in range(precision):
    buffer = int(f/divider)
    f_text += str(buffer)
    f = f-buffer*divider
    divider = divider/10

print(f"{type(f_text)} {f_text}")
