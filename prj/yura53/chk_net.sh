check_ip() {


	[ -z "$(ping -c 1 $1 | grep Unreachable)" ] &&  echo Reachable $1
}

# check_ip 192.168.1.22
check_ip 192.168.1.15
check_ip 192.168.1.16
check_ip 192.168.1.17
check_ip 192.168.1.18
check_ip 192.168.1.19
check_ip 192.168.1.20
check_ip 192.168.1.21
check_ip 192.168.1.22
check_ip 192.168.1.23
