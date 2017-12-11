#
#
#

import socket, sys, select, string, time, subprocess

def prompt():
    sys.stdout.write('<You> ')
    sys.stdout.flush()

def pass_through_des(input):
    F = open('file.txt', 'w').close()
    F = open('file.txt', 'w')
    F.write(input)
    F.close()
    tmp=subprocess.call("./test")
    time.sleep(.3)
    F = open('file.txt', 'r')
    input=F.read()
    F.close()
    return input


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
                    if data[0] == '[':
                        sys.stdout.write((data))
                    else:
                        index = data.find('>')
                        index += 1
                        data = data[index:]
                        sys.stdout.write(pass_through_des(data))

                    prompt()

            else:
                msg = sys.stdin.readline()
                s.send(pass_through_des(msg))
                prompt()
