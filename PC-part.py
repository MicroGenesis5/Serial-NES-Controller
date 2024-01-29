# Python 2

# PC part of Serial NES Controller project: https://falconreach.net/_txt/nes.html
# Arduino Mega must be connected 

import time
import serial

serialcomm = serial.Serial('COM5', 9600) # Arduino Mega's COM number
serialcomm.timeout = 1

print ''
print ''
print '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
print ' #######                            #####'
print '    #      #    #   ######         #     #   #    #   ######    ####     ####    #    #     ##      ####    #####   ######   #####'
print '    #      #    #   #              #         #    #   #        #        #        ##  ##    #  #    #          #     #        #    #'
print '    #      ######   #####          #         ######   #####     ####     ####    # ## #   #    #    ####      #     #####    #    #'
print '    #      #    #   #              #         #    #   #             #        #   #    #   ######        #     #     #        #####'
print '    #      #    #   #              #     #   #    #   #        #    #   #    #   #    #   #    #   #    #     #     #        #   #'
print '    #      #    #   ######          #####    #    #   ######    ####     ####    #    #   #    #    ####      #     ######   #    #'
print '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
print ''
print ''

startGameCount = 0



while 1:
    command = raw_input('[type \'h\' for options] - Command?: ').lower().strip()
    if command == 'h':
        print ''
        print 'Commands:'
        print '---------'
        print '  h                       show these options'
        print '  ms                      starts game by going past intro screens - can only be done once'
        print '  mn                      begins a new game (if the game has just been powered on, use \'ms\' instead)'
        print '  mp                      begins a new game as Black'
        print '  mi                      acknowledge an illegal move'
        print '  mj                      force CPU to move'
        print ''
        print '  m[letter][number]       picks up or drops a chess piece on the specifed chessboard coordinate'
        print '                          letter = horizontal coordinate , number = vertical coordinate'
        print ''
        print '                          IMPORTANT: wait until \'game hand\' is off the chessboard before sending coordinate'
        print ''
        print '                          valid examples: ma4, MG1, MD8, mc5'
        print ''
        print '  mL[number/letter]       changes the CPU\'s skill level - this will start a new game'
        print '                          valid input: numbers 1-9 and letters a-f'
        print '                          skill level: 1 < 9 < a < f'
        print ''
        print '  Notes:'
        print '    * Commands are not case sensitive'
        print '    * Commands are valid as long as there is no 2P controller attached to the NES'
        print '    * Ideally, commands must be sent while \'game hand\' is off the chessboard; for picking up'
        print '      and dropping chess pieces, this is a requirement!'
        print ''
    else:
        if command == 'ms':
            startGameCount += 1
            if startGameCount > 1:
                print ''
                print 'Game has already started! If you reset The Chessmaster game, restart this program.'
                print ''
                continue
        serialcomm.write(command.encode())
        time.sleep(1)
        print ''
    
serialcomm.close()


