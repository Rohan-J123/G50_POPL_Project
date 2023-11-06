use std::io::{self, Write};
use std::net::{IpAddr, Ipv4Addr, SocketAddr, TcpStream};
use std::time::Duration;

fn main() -> io::Result<()> {
    let mut host = String::new();
    print!("Enter host IP: ");
    io::stdout().flush()?;
    io::stdin().read_line(&mut host)?;

    let host = host.trim();

    let start: u16;
    let end: u16;

    print!("Enter start port number: ");
    io::stdout().flush()?;
    let mut start_str = String::new();
    io::stdin().read_line(&mut start_str)?;

    print!("Enter end port number: ");
    io::stdout().flush()?;
    let mut end_str = String::new();
    io::stdin().read_line(&mut end_str)?;

    if let Ok(s) = start_str.trim().parse() {
        start = s;
    } else {
        eprintln!("Invalid start port number");
        return Ok(());
    }

    if let Ok(e) = end_str.trim().parse() {
        end = e;
    } else {
        eprintln!("Invalid end port number");
        return Ok(());
    }

    for port in start..=end {
        let addr = format!("{}:{}", host, port);
        print!("Scanning port {}... ", port);
        io::stdout().flush()?;

        if is_port_open(addr) {
            println!("Port {} is open", port);
        } else {
            println!("Port {} is closed", port);
        }
    }

    Ok(())
}

fn is_port_open(addr: String) -> bool {
    if let Ok(_) = TcpStream::connect_timeout(&addr.parse().unwrap(), Duration::from_secs(3)) {
        true
    } else {
        false
    }
}