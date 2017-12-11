#
#
#

import socket, sys, select, string, time, subprocess

def prompt():
    sys.stdout.write('<You> ')
    sys.stdout.flush()

if __name__ == "__main__":

    if(len(sys.argv) < 3):
        print 'Usage : python telnet.py hostname port'
        sys.exit()

    host = sys.argv[1]
    port = int(sys.argv[2])

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(2)

    try:
        s.connect((host, port))
    except:
        print 'Connection error'
        sys.exit()

    print 'Connected to host'
    prompt()

    while True:
        socket_list = [sys.stdin, s]

        read_sockets, write_sockets, error_sockets = select.select(socket_list, [], [])

        for sock in read_sockets:
            #incoming messages
            if sock == s:
                data = sock.recv(4096)
                if not data:
                    print '\nConnection error'
                    sys.exit()
                else:

                    F = open('file.txt', 'w').close()
                    F = open('file.txt', 'w')
                    F.write(data)
                    F.close()
                    tmp=subprocess.call("./test")
                    time.sleep(.3)
                    F = open('file.txt', 'r')
                    data=F.read()
                    F.close()

                    sys.stdout.write(data)
                    prompt()

            else:
                msg = sys.stdin.readline()
                # transfer to C-code
                F = open('file.txt', 'w').close()
                F = open('file.txt', 'w')
                F.write(msg)
                F.close()
                tmp=subprocess.call("./test")
                time.sleep(.3)
                F = open('file.txt', 'r')
                msg=F.read()
                F.close()

                s.send(msg)
                prompt()
