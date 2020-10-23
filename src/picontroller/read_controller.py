import pygame
from arduino_comm import blink

pygame.init()
pygame.joystick.init()

joystick = pygame.joystick.Joystick(0)
joystick.init()


screen = pygame.display.set_mode((100,100))

# get count of joysticks=1, axes=27, buttons=19 for DualShock 3

joystick_count = pygame.joystick.get_count()
print("joystick_count")
print(joystick_count)
print("--------------")

numaxes = joystick.get_numaxes()
print("numaxes")
print(numaxes)
print("--------------")

numbuttons = joystick.get_numbuttons()
print("numbuttons")
print(numbuttons)
print("--------------")

loopQuit = False
old_axis = None
old_press = None
l_axis = None
r_axis = None
while loopQuit == False:

# test joystick axes
        
        for i in range(0,4):
                pygame.event.pump()
                axis = joystick.get_axis(i)
                if i == 1:
                        l_axis = axis
                if i == 3:
                        r_axis = axis
        

# test controller buttons
        
        pygame.event.pump()
        blink(l_axis,r_axis, joystick.get_button(0), joystick.get_button(1), joystick.get_button(2), joystick.get_button(3))