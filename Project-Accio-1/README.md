Robin Suda, 77528324

The server listens for any clients trying to set up a connection with the server, when the
server establishes a connection. The client will send a file to the server where the server will
save it to a specific folder.

Problems I ran into

1. I had some issues setting up the environment where I had to go into my pc's bios and enable
virtual technology. I used this tutorial to figure out the error and fix the error I had.
https://www.sitepoint.com/getting-started-vagrant-windows/

2. The issue I had next was changing the server port and file directory on command line. I used
the code given to us by Bhavana which wouldn't take arguements from the command line. I changed
both the client and server main function to take parameter int main (int argc, char argv). I then
used int x = atoi(argv[i]) to make the next arguement into an int that would set up the port. So
when you start the server (./server) you will need to pass the arguement of which port to use.
So now the command will be (./server <PORT>), same when running the client. If the client does not
match the server port, it will let you know that it won't connect and stop running.

3. Another issue I had to deal with was sending an actual file instead of just some text. The server
will then save the file at a specific location. (How did I solve this).

4. I had no way of testing if the file I transfered was actually transferred or it was synced with my
original folder so I moved the client to another location. And now that I am typing this out I'm asking
myself why I didn't just put the file I wanted to transfer in one location and save it on the server
side at a different location. Either way it should work, but I will have to change it back so it is in
one location.

5. I finished implimenting the

As of yet I have not used any additional libraries other than the ones that were given for me to use.

Tutorials I have used

        https://www.youtube.com/watch?v=vBreXjkizgo&t=2194s  -This tutorial helped me to set up vagrant

        https://www.youtube.com/watch?v=WDn-htpBlnU  -This tutorial helped me understand the server c++
code and explained that we needed to do these steps in order; Create a socket, Bind the socket to an ip
address and port, set the socket up for listening, wait for a connection, close the socket, while loop
that accepts and echo message back to client, then cleanup.

        https://www.youtube.com/watch?v=dquxuXeZXgo  -This tutorial is by the same guy and explains the
 client side code.