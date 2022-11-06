package main

import "fmt"
import "net"
import "log"
import "bufio"

// 单向的通道
type client chan<- string

var (
    entering = make(chan client)
    leaving = make(chan client)
    messages = make(chan string)
)

func main() {
    listener, err := net.Listen("tcp", ":8000")
    if err != nil {
        log.Fatal(err)
    }

    go broadcaster()

    for {
        conn, err := listener.Accept()
        if err != nil {
            log.Print(err)
            continue
        }
        go handleConn(conn)
    }
}

func broadcaster() {
    // all connected clients
    clients := make(map[client]bool)
    for {
        select {
        case msg := <- messages:
            for cli := range clients {
                cli <- msg
            }

        case cli := <- entering:
            clients[cli] = true

        case cli := <- leaving:
            delete(clients, cli)
            close(cli)
        }
    }
}

func handleConn(conn net.Conn) {
    ch := make(chan string)
    go clientWriter(conn, ch)

    who := conn.RemoteAddr().String()
    ch <- "You are " + who + "\n"
    messages <- who + " has arrived" + "\n"
    entering <- ch

    input := bufio.NewScanner(conn)
    for input.Scan() {
        messages <- who + ": " + input.Text() + "\n"
    }

    leaving <- ch
    messages <- who + " has left" + "\n"
    conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
    for msg := range ch {
        fmt.Fprintf(conn, msg)
    }
}
