#
#
#

import socket, sys, select, string, time, subprocess, secrets

def prompt():
    sys.stdout.write('<You> ')
    sys.stdout.flush()

def update_session_key(port):
    client_sectret = secrets.randbelow(9999)
    with open('session_key_' + str(port), 'r') as F:
        session_key, session_modulo = [int(x) for x in next(F).split()]
    F = open('session_key_' + str(port), 'w').close()
    print '\nOld session key:'
    print session_key
    print '\nSession Modulo: '
    print session_modulo
    session_key = (session_key ** client_sectret) % session_modulo
    with open('session_key_' + str(port), 'w') as F:
        F.write(session_key + ' ')
        F.write(session_modulo)
    print '\nNew Session key: '
    print session_key
    
    
def pass_through_des(input):
    F = open('file.txt', 'w').close()
    F = open('file.txt', 'w')
    F.write(input)
    F.close()
    tmp=subprocess.call("./test")
    time.sleep(.1)
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
    update_session_key(port)
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
                        index += 2
                        data = data[index:]
                        sys.stdout.write(pass_through_des(data))

                    prompt()

            else:
                msg = sys.stdin.readline()
                s.send(pass_through_des(msg))
                prompt()
